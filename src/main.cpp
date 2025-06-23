#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_VL53L0X.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "arduinoFFT.h"
#include "freertos/queue.h"
#include "esp_task_wdt.h"
#include "PZEM004Tv30.h"
#include <HardwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "random.h"
#include "image.h"

// I2C
#define Peripheral_Sensor_SDA 38
#define Peripheral_Sensor_SCL 39
// Oled
#define i2c_Address 0x3c
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
// FFT Vibration
#define EARTH_GRAVITY_MS2 9.80665
#define SAMPLES 512            // 512
#define SAMPLING_FREQUENCY 100 // 500
// Pzem
#define PZEM_RX 18
#define PZEM_TX 17
// ToF
#define TOF_Sensor_ADDR 0x29
// MPU6050
#define MPU6050_I2C_ADDR 0x68
// Peripheral
#define SSR 2
#define BUZZER 35

TwoWire Peripheral_Sensor = TwoWire(1);
MPU6050 mpu(MPU6050_I2C_ADDR, &Peripheral_Sensor);
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
PZEM004Tv30 pzem(Serial2, PZEM_RX, PZEM_TX);
Adafruit_VL53L0X tof = Adafruit_VL53L0X();

float vReal[SAMPLES];
float vImag[SAMPLES];
ArduinoFFT<float> FFT = ArduinoFFT<float>(vReal, vImag, SAMPLES, SAMPLING_FREQUENCY);

QueueHandle_t Queue_dataPzem;
QueueHandle_t Queue_dataToF;
QueueHandle_t Queue_dataFFT;
QueueHandle_t Queue_predict;
QueueHandle_t Queue_resultPredict;
SemaphoreHandle_t xSemaphore = NULL;
TaskHandle_t ToF_Task_Handle = NULL;

const int START_BIN = 5;
const int END_BIN = 50;
double feature[END_BIN - START_BIN + 1];
int const INTERRUPT_PIN = 11;
bool blinkState;
char buff[50];
float distance;
int errorRetry = 0;

typedef struct
{
  float voltage;
  float current;
  float frequency;
  float power;
} dataPzem;

typedef struct
{
  char KlasifikasiStatus[16];
  float maxAmplitude;
  float rmsAmplitude;
  float maxFFT;
} dataFFT;

/*---MPU6050 Control/Status Variables---*/
bool DMPReady = false;  // Set true if DMP init was successful
uint8_t MPUIntStatus;   // Holds actual interrupt status byte from MPU
uint8_t devStatus;      // Return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // Expected DMP packet size (default is 42 bytes)
uint8_t FIFOBuffer[64]; // FIFO storage buffer

/*---Orientation/Motion Variables---*/
Quaternion q;        // [w, x, y, z]         Quaternion container
VectorInt16 aa;      // [x, y, z]            Accel sensor measurements
VectorInt16 gy;      // [x, y, z]            Gyro sensor measurements
VectorInt16 aaReal;  // [x, y, z]            Gravity-free accel sensor measurements
VectorInt16 aaWorld; // [x, y, z]            World-frame accel sensor measurements
VectorFloat gravity; // [x, y, z]            Gravity vector

/*---Time Variables ---*/
uint64_t previousMicros = 0;
const long interval = 1000000;

/*------Interrupt detection routine------*/
volatile bool MPUInterrupt = false; // Indicates whether MPU6050 interrupt pin has gone high
void DMPDataReady()
{
  MPUInterrupt = true;
}

void readIMU(void *pvParameter);
void readPZEM(void *pvParameter);
void readToF(void *pvParameter);
void mlPredict(void *pvParameter);
void screenDisplay(void *pvParameter);

void setup()
{
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, HIGH);
  vTaskDelay(100 / portTICK_PERIOD_MS);
  digitalWrite(BUZZER, LOW);

  Wire.begin();
  Wire.setClock(400000);
  Peripheral_Sensor.begin(Peripheral_Sensor_SDA, Peripheral_Sensor_SCL, 400000);
  Serial.begin(115200);
  while (!Serial)
    ;
  display.begin(i2c_Address, true);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.println("Setting up...");
  display.display();
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  mpu.initialize();

  pinMode(INTERRUPT_PIN, INPUT);
  pinMode(SSR, OUTPUT);
  digitalWrite(SSR, LOW);

  if (!tof.begin(TOF_Sensor_ADDR, false, &Peripheral_Sensor))
  {
    Serial.println("ToF not found. Check wiring!");
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 10);
    display.println("ToF ERR....");
    display.display();
  }
  else
  {
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 10);
    display.println("ToF OK....");
    display.display();
  }
  if (mpu.testConnection() == false)
  {
    Serial.println("MPU6050 connection failed");
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 20);
    display.println("IMU ERR....");
    display.display();
    for (uint8_t i = 0; i < 3; i++)
    {
      display.setTextSize(1);
      display.setTextColor(SH110X_WHITE);
      display.setCursor(0, 30);
      display.print("Restarting ESP");
      display.setCursor(85 + (i * 6), 30);
      display.print(".");
      display.display();
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    ESP.restart();
  }
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 20);
  display.println("IMU OK....");
  display.display();

  /* Initialize and configure the DMP*/
  Serial.println(F("Initializing DMP..."));
  devStatus = mpu.dmpInitialize();

  /* Supply your gyro offsets here, scaled for min sensitivity */
  mpu.setXGyroOffset(0);
  mpu.setYGyroOffset(0);
  mpu.setZGyroOffset(0);
  mpu.setXAccelOffset(0);
  mpu.setYAccelOffset(0);
  mpu.setZAccelOffset(0);

  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 30);
  display.println("Setting Offset....");
  display.display();

  /* Making sure it worked (returns 0 if so) */
  if (devStatus == 0)
  {
    mpu.CalibrateAccel(6); // Calibration Time: generate offsets and calibrate our MPU6050
    mpu.CalibrateGyro(6);
    mpu.setDMPEnabled(true);
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), DMPDataReady, RISING);
    MPUIntStatus = mpu.getIntStatus();

    /* Set the DMP Ready flag so the main loop() function knows it is okay to use it */
    Serial.println(F("DMP ready! Waiting for first interrupt..."));
    DMPReady = true;
    packetSize = mpu.dmpGetFIFOPacketSize();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 40);
    display.println("DMP OK....");
    display.display();
  }
  else
  {
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 40);
    display.println("DMP ERR....");
    display.display();
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
  }
  digitalWrite(BUZZER, HIGH);
  vTaskDelay(2000 / portTICK_PERIOD_MS);
  digitalWrite(BUZZER, LOW);
  digitalWrite(SSR, HIGH);
  esp_task_wdt_deinit();
  esp_task_wdt_init(30, true);

  Queue_dataPzem = xQueueCreate(10, sizeof(dataPzem));
  Queue_dataToF = xQueueCreate(10, sizeof(float));
  Queue_dataFFT = xQueueCreate(10, sizeof(dataFFT));
  Queue_predict = xQueueCreate(10, sizeof(char[16]));
  Queue_resultPredict = xQueueCreate(10, sizeof(int));

  xTaskCreate(readPZEM, "readPZEM", 4096, NULL, 1, NULL);
  // xTaskCreate(readToF, "readToF", 4096, NULL, 1, NULL);
  xTaskCreate(screenDisplay, "screenDisplay", 8192 * 2, NULL, 1, NULL);
  xTaskCreate(readIMU, "readIMU", 8192 * 8, NULL, 2, NULL);
  xTaskCreate(mlPredict, "mlPredict", 8192 * 2, NULL, 2, NULL);
}

void loop()
{
  vTaskDelete(NULL);
}

void mlPredict(void *pvParameter)
{
  dataPzem datEnergy;
  dataPzem datEnergyPrev;
  dataFFT datFFT;
  dataFFT datFFTPrev;
  char status[16];
  int countPredict[3];
  int idx;
  bool stateStartEngine = false;
  bool endPredict = false;
  esp_task_wdt_add(NULL);
  for (;;)
  {
    bool isDataAvailable = false;
    if (xQueueReceive(Queue_dataPzem, &datEnergy, 0) == pdTRUE)
      isDataAvailable = true;
    if (xQueueReceive(Queue_dataFFT, &datFFT, 0) == pdTRUE)
      isDataAvailable = true;

    if (datEnergy.current > 1.0 && !stateStartEngine)
    {
      vTaskDelay(5000 / portTICK_PERIOD_MS);
      stateStartEngine = true;
      idx = 0;
      for (int i = 0; i < 3; i++)
      {
        countPredict[i] = 0;
      }
    }
    else if (datEnergy.current <= 1.0 && stateStartEngine)
    {
      vTaskDelay(3000 / portTICK_PERIOD_MS);
      stateStartEngine = false;
      idx = 0;
    }

    esp_task_wdt_reset();
    if (!isDataAvailable || !DMPReady || !stateStartEngine || datEnergyPrev.current == datEnergy.current ||
        datFFTPrev.rmsAmplitude == datFFT.rmsAmplitude || datFFTPrev.maxAmplitude == datFFT.maxAmplitude ||
        datEnergyPrev.power == datEnergy.power || datFFT.maxFFT == datFFTPrev.maxFFT || endPredict)
    {
      vTaskDelay(100 / portTICK_PERIOD_MS);
      continue;
    }
    float X_1[] = {datEnergy.power, datFFT.rmsAmplitude, datFFT.maxAmplitude, datFFT.maxFFT};
    int result = predict(X_1);
    // Serial.printf("%.02f, %.02f, %.02f, %.02f, %.02f, \n", datEnergy.power, datFFT.rmsAmplitude, datEnergy.current, datFFT.maxAmplitude, datFFT.maxFFT);
    Serial.printf("Result: %d Power:%.02f RMS: %.02f Curent: %.02f MaxAmp: %.02f, FFT: %.02f\n", result, datEnergy.power, datFFT.rmsAmplitude, datEnergy.current, datFFT.maxAmplitude, datFFT.maxFFT);
    countPredict[idx++] = result;
    xQueueSend(Queue_resultPredict, &result, 0);

    if (idx >= 3)
    {
      if (countPredict[0] == 0 && countPredict[1] == 0 && countPredict[2] == 0)
      {
        strcpy(status, "Baik");
        xQueueSend(Queue_predict, &status, 0);
        endPredict = true;
        xTaskCreate(readToF, "readToF", 4096, NULL, 1, NULL);
        vTaskDelete(NULL);
      }
      else if (countPredict[0] == 1 && countPredict[1] == 1 && countPredict[2] == 1)
      {
        strcpy(status, "Aus");
        xQueueSend(Queue_predict, &status, 0);
        digitalWrite(SSR, LOW);
        for (int i = 0; i < 3; i++)
        {
          digitalWrite(BUZZER, HIGH);
          vTaskDelay(1000 / portTICK_PERIOD_MS);
          digitalWrite(BUZZER, LOW);
          vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        endPredict = true;
      }
      else
      {
        strcpy(status, "Idle");
      }
      idx = 0;
    }

    datFFTPrev.maxAmplitude = datFFT.maxAmplitude;
    datFFTPrev.rmsAmplitude = datFFT.rmsAmplitude;
    datFFTPrev.maxFFT = datFFT.maxFFT;
    datEnergyPrev.current = datEnergy.current;
    datEnergyPrev.power = datEnergy.power;
    esp_task_wdt_reset();
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void screenDisplay(void *pvParameter)
{
  esp_task_wdt_add(NULL);
  dataPzem datEnergy;
  dataFFT datFFT;
  char buff[50];
  float distance;
  char KlasifikasiStatus[16];
  char prevStatus[16] = "";
  dataPzem prevEnergy = {0, 0, 0, 0};
  dataFFT prevFFT = {"", 0, 0};
  float prevDistance = -1;
  bool stateAus = false;
  int resultPredict = 0;
  int prevResultPredict;
  for (;;)
  {
    bool updated = false;
    if (xQueueReceive(Queue_dataPzem, &datEnergy, 0) == pdTRUE)
      updated = true;
    if (xQueueReceive(Queue_dataToF, &distance, 0) == pdTRUE)
      updated = true;
    if (xQueueReceive(Queue_dataFFT, &datFFT, 0) == pdTRUE)
      updated = true;
    if (xQueueReceive(Queue_predict, &KlasifikasiStatus, 0) == pdTRUE)
      updated = true;
    if (xQueueReceive(Queue_resultPredict, &resultPredict, 0) == pdTRUE)
      updated = true;

    String status = String(KlasifikasiStatus);
    if (status == "Aus")
    {
      stateAus = true;
      display.clearDisplay();
    }

    if (updated &&
        (datEnergy.voltage != prevEnergy.voltage ||
         datEnergy.current != prevEnergy.current ||
         datEnergy.power != prevEnergy.power ||
         datEnergy.frequency != prevEnergy.frequency ||
         distance != prevDistance ||
         datFFT.rmsAmplitude != prevFFT.rmsAmplitude ||
         datFFT.maxAmplitude != prevFFT.maxAmplitude ||
         datFFT.maxFFT != prevFFT.maxFFT ||
        resultPredict != prevResultPredict ||
         KlasifikasiStatus != prevStatus) &&
        !stateAus)
    {
      esp_task_wdt_reset();
      display.clearDisplay();
      display.setTextColor(1);
      display.setTextWrap(false);
      display.setCursor(26, 4);
      display.print("Skripsi 2025");
      display.drawRect(0, 0, 128, 15, 1);
      display.setCursor(1, 26);
      sprintf(buff, "P: %.1fW", datEnergy.power);
      display.print(buff);
      display.setCursor(1, 17);
      sprintf(buff, "V: %.1fV", datEnergy.voltage);
      display.print(buff);
      display.setCursor(66, 26);
      sprintf(buff, "F: %.1fHz", datEnergy.frequency);
      display.print(buff);
      display.drawLine(64, 14, 64, 55, 1);
      display.setCursor(66, 17);
      sprintf(buff, "I: %.1fA", datEnergy.current);
      display.print(buff);
      display.setCursor(1, 35);
      sprintf(buff, "T: %.1fcm", distance / 10);
      display.print(buff);
      display.setCursor(1, 57);
      display.print("Klasifikasi: ");
      display.println(KlasifikasiStatus);
      display.setCursor(66, 35);
      display.print(DMPReady ? "IMU: OK" : "IMU: ERR");
      display.setCursor(1, 45);
      sprintf(buff, "RMS: %.2f", datFFT.rmsAmplitude);
      display.print(buff);
      display.drawLine(0, 55, 127, 55, 1);
      display.setCursor(66, 45);
      sprintf(buff, "FFT: %.2f", datFFT.maxFFT);
      display.print(buff);
      display.drawLine(119, 56, 119, 63, 1);
      display.setCursor(122, 57);
      display.print(resultPredict);
      display.display();

      prevEnergy = datEnergy;
      prevFFT = datFFT;
      prevDistance = distance;
      prevResultPredict = resultPredict;
      strcpy(prevStatus, KlasifikasiStatus);
    }
    else if (stateAus)
    {
      display.drawBitmap(27, 8, image_download_bits, 16, 16, 1);
      display.setTextColor(1);
      display.setTextWrap(false);
      display.setCursor(51, 13);
      display.print("AUS");
      display.setCursor(21, 27);
      display.print("SEGERA LAKUKAN ");
      display.setCursor(13, 39);
      display.print("PENGGANTIAN MATA");
      display.drawBitmap(78, 8, image_download_bits, 16, 16, 1);
      display.setCursor(41, 52);
      display.print("GERINDA");

      display.display();
    }
    esp_task_wdt_reset();
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void readPZEM(void *pvParameter)
{
  dataPzem dat;
  esp_task_wdt_add(NULL);
  for (;;)
  {
    esp_task_wdt_reset();
    dat.voltage = isnan(pzem.voltage()) ? 0 : pzem.voltage();
    dat.current = isnan(pzem.current()) ? 0 : pzem.current();
    dat.power = isnan(pzem.power()) ? 0 : pzem.power();
    dat.frequency = isnan(pzem.frequency()) ? 0 : pzem.frequency();
    if (dat.voltage > 300)
      dat.voltage = 0;
    if (dat.current > 100)
      dat.current = 0;
    if (dat.power > 30000)
      dat.power = 0;
    if (dat.frequency > 60)
      dat.frequency = 60;
    xQueueSend(Queue_dataPzem, &dat, portMAX_DELAY);
    esp_task_wdt_reset();
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void readToF(void *pvParameter)
{
  VL53L0X_RangingMeasurementData_t measure;
  float distance;
  esp_task_wdt_add(NULL);
  for (;;)
  {
    esp_task_wdt_reset();
    tof.rangingTest(&measure, false);
    if (measure.RangeStatus != 4)
      distance = measure.RangeMilliMeter;
    else
      distance = 0;

    if (distance < 0 || distance > 4000)
      distance = 0;
    xQueueSend(Queue_dataToF, &distance, portMAX_DELAY);
    esp_task_wdt_reset();
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void readIMU(void *pvParameter)
{
  dataFFT dat;
  dataPzem datEnergy;
  esp_task_wdt_add(NULL);
  for (;;)
  {
    for (int i = 0; i < SAMPLES; i++)
    {
      previousMicros = esp_timer_get_time();
      if (!DMPReady)
        ESP.restart();

      esp_task_wdt_reset();
      taskYIELD();
      if (mpu.dmpGetCurrentFIFOPacket(FIFOBuffer))
      {
        mpu.dmpGetQuaternion(&q, FIFOBuffer);
        mpu.dmpGetAccel(&aa, FIFOBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
      }
      else
      {
        MPUIntStatus = mpu.getIntStatus();
        if (MPUIntStatus & MPU6050_INTERRUPT_FIFO_OFLOW_BIT)
        {
          mpu.resetFIFO();
        }
      }

      float accelx_ms2 = aaReal.x * mpu.get_acce_resolution() * EARTH_GRAVITY_MS2;
      if (isnan(accelx_ms2))
        errorRetry++;
      else
        errorRetry = 0;
      if (errorRetry > 10)
        ESP.restart();

      vReal[i] = accelx_ms2;
      vImag[i] = 0.0;

      while (esp_timer_get_time() - previousMicros < (interval / SAMPLING_FREQUENCY));
      previousMicros = esp_timer_get_time();
    }

    float rms = 0;
    float maxFFT = 0;

    esp_task_wdt_reset();
    FFT.dcRemoval();
    FFT.windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.compute(FFT_FORWARD);
    FFT.complexToMagnitude();

    for (int i = 0; i < SAMPLES; i++)
    {
      rms += vReal[i] * vReal[i];
    }
    rms = sqrt(rms / SAMPLES);

    esp_task_wdt_reset();
    for (int i = 2; i < SAMPLES / 2; i++)
    {
      if (vReal[i] > maxFFT)
        maxFFT = vReal[i];
    }
    dat.maxAmplitude = maxFFT;
    dat.rmsAmplitude = rms;
    dat.maxFFT = FFT.majorPeak();
    xQueueSend(Queue_dataFFT, &dat, portMAX_DELAY);
    esp_task_wdt_reset();
    vTaskDelay(1 / portTICK_PERIOD_MS);
  }
}