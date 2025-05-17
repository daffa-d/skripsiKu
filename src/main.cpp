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
#define SAMPLES 1024
#define SAMPLING_FREQUENCY 500
// Pzem
#define PZEM_RX 18
#define PZEM_TX 17
// ToF
#define TOF_Sensor_ADDR 0x29
#define SSR 2
// MPU6050
#define MPU6050_I2C_ADDR 0x68

TwoWire Peripheral_Sensor = TwoWire(1);
MPU6050 mpu(MPU6050_I2C_ADDR, &Peripheral_Sensor);
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
PZEM004Tv30 pzem(Serial2, PZEM_RX, PZEM_TX);
Adafruit_VL53L0X tof = Adafruit_VL53L0X();

double vReal[SAMPLES];
double vImag[SAMPLES];
double vRealFFT[SAMPLES];
ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLES, SAMPLING_FREQUENCY);

QueueHandle_t Queue_dataPzem;
QueueHandle_t Queue_dataToF;
QueueHandle_t Queue_dataFFT;
QueueHandle_t Queue_Vreal;

const int START_BIN = 5;
const int END_BIN = 50;
double feature[END_BIN - START_BIN + 1];
int const INTERRUPT_PIN = 10; // Define the interruption #0 pin
bool blinkState;
char buff[50];

typedef struct
{
  float voltage;
  float current;
  float frequency;
  float power;
} dataPzem;

typedef struct
{
  String KlasifikasiStatus;
  double maxAmplitude;
  double rmsAmplitude;
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
unsigned long previousMicros = 0;
const long interval = 1000000;

/*------Interrupt detection routine------*/
volatile bool MPUInterrupt = false; // Indicates whether MPU6050 interrupt pin has gone high
void DMPDataReady()
{
  MPUInterrupt = true;
}

String klasifikasiKeausan(double rms, double maxFFT, float arus, float tof);
void movingAverage(double *input, double *output, int len, int windowSize);
bool isGetaranValid(double *spectrum, int size, double freqResolution);
void readIMU(void *pvParameter);
void readPZEM(void *pvParameter);
void readToF(void *pvParameter);
void screenDisplay(void *pvParameter);

void setup()
{
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
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 10);
  display.println("ToF OK....");
  display.display();

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
      Serial.printf("Restart in %d seconds...\n", 3 - i);
      display.setTextSize(1);
      display.setTextColor(SH110X_WHITE);
      display.setCursor(0, 30);
      display.println("Restart ESP...");
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
  vTaskDelay(2000 / portTICK_PERIOD_MS);
  pinMode(LED_BUILTIN, OUTPUT);
  esp_task_wdt_deinit();
  esp_task_wdt_init(50, true);

  Queue_dataPzem = xQueueCreate(10, sizeof(dataPzem));
  Queue_dataToF = xQueueCreate(2, sizeof(float));
  Queue_dataFFT = xQueueCreate(2, sizeof(dataFFT));
  Queue_Vreal = xQueueCreate(2, sizeof(feature));

  xTaskCreatePinnedToCore(readPZEM, "readPZEM", 4096, NULL, 0, NULL, 1);
  xTaskCreatePinnedToCore(readToF, "readToF", 4096, NULL, 0, NULL, 1);
  xTaskCreatePinnedToCore(readIMU, "readIMU", 8192, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(screenDisplay, "screenDisplay", 8192, NULL, 0, NULL, 0);
}

void loop()
{
  vTaskDelete(NULL);
}

void screenDisplay(void *pvParameter)
{
  dataPzem datEnergy;
  dataFFT datFFT;
  char buff[50];
  float distance;
  esp_task_wdt_add(NULL);
  for (;;)
  {
    xQueueReceive(Queue_dataPzem, &datEnergy, 0);
    xQueueReceive(Queue_dataToF, &distance, 0);
    xQueueReceive(Queue_dataFFT, &datFFT, 0);
    xQueueReceive(Queue_Vreal, &feature, 0);
    esp_task_wdt_reset();
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(25, 0);
    display.print("Skripsi 2025");
    display.setCursor(0, 10);
    sprintf(buff, "V: %.1f V", datEnergy.voltage);
    display.println(buff);
    display.setCursor(60, 10);
    sprintf(buff, "I: %.1f A", datEnergy.current);
    display.println(buff);
    display.setCursor(0, 20);
    sprintf(buff, "P: %.1f W", datEnergy.power);
    display.println(buff);
    display.setCursor(60, 20);
    sprintf(buff, "F: %.1f Hz", datEnergy.frequency);
    display.println(buff);
    display.setCursor(0, 30);
    sprintf(buff, "ToF: %.1f cm", distance / 10);
    display.println(buff);
    display.setCursor(80, 30);
    display.print(DMPReady ? "IMU: OK" : "IMU: ERR");
    display.setCursor(0, 40);
    sprintf(buff, "RMS: %.2f", datFFT.rmsAmplitude);
    display.println(buff);
    display.setCursor(60, 40);
    sprintf(buff, "Amp: %.2f", datFFT.maxAmplitude);
    display.println(buff);
    display.setCursor(0, 50);
    display.print("Klasifikasi: ");
    display.println(datFFT.KlasifikasiStatus);
    display.display();
    // Serial.printf("Tegangan: %.2f | Arus: %.2f |Power: %.2f | ToF: %.2f | RMS: %.2f | Max FFT: %.2f | Status: %s\n", datEnergy.voltage, datEnergy.current, datEnergy.power, distance / 10, datFFT.rmsAmplitude, datFFT.maxAmplitude, datFFT.KlasifikasiStatus.c_str());
    // Serial.printf("%.2f, %.2f, %.2f, %.2f, %.2f, %.2f, ", datEnergy.voltage, datEnergy.current, datEnergy.power, distance / 10, datFFT.rmsAmplitude, datFFT.maxAmplitude);
    // for (int i = START_BIN; i <= END_BIN; i++)
    // {
    //   Serial.printf("%.2f, ", feature[i - START_BIN]);
    // }
    // Serial.printf("\n");
    esp_task_wdt_reset();
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void readPZEM(void *pvParameter)
{
  dataPzem dat;
  digitalWrite(SSR, HIGH);
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
      dat.frequency = 0;
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
    taskYIELD();
    tof.rangingTest(&measure, false);
    if (measure.RangeStatus != 4)
    {
      distance = measure.RangeMilliMeter;
    }
    else
    {
      distance = 0;
    }

    if (distance < 0)
      distance = 0;
    else if (distance > 2000)
      distance = 0;
    else
      distance = measure.RangeMilliMeter;
    xQueueSend(Queue_dataToF, &distance, 0);
    esp_task_wdt_reset();
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void readIMU(void *pvParameter)
{
  int errorRetry = 0;
  dataFFT dat;
  dataPzem datEnergy;
  float distance;
  double smoothed[SAMPLES / 2];
  esp_task_wdt_add(NULL);
  for (;;)
  {
    previousMicros = esp_timer_get_time();
    for (int i = 0; i < SAMPLES; i++)
    {
      if (!DMPReady)
        return; // Stop the program if DMP programming fails.

      /* Read a packet from FIFO */
      taskYIELD();
      if (mpu.dmpGetCurrentFIFOPacket(FIFOBuffer))
      {
        mpu.dmpGetQuaternion(&q, FIFOBuffer);
        mpu.dmpGetAccel(&aa, FIFOBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
      }

      float accelx_ms2 = (float)aaReal.x * mpu.get_acce_resolution() * EARTH_GRAVITY_MS2;
      if (isnan(accelx_ms2))
        errorRetry++;
      else
        errorRetry = 0;
      if (errorRetry > 10)
        ESP.restart();

      vReal[i] = fabs(accelx_ms2);
      vImag[i] = 0.0;

      while (esp_timer_get_time() - previousMicros < (interval / SAMPLING_FREQUENCY))
        ;
      previousMicros = esp_timer_get_time();
    }

    esp_task_wdt_reset();
    FFT.dcRemoval();
    FFT.windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.compute(FFT_FORWARD);
    FFT.complexToMagnitude();

    double rms = 0;
    for (int i = 0; i < SAMPLES; i++)
      rms += vReal[i] * vReal[i];
    rms = sqrt(rms / SAMPLES);

    double freqResolution = (double)SAMPLING_FREQUENCY / SAMPLES;
    if (!isGetaranValid(vReal, SAMPLES / 2, freqResolution))
    {
      // Serial.println("Getaran tidak valid (gerakan tangan)");
      // vTaskDelay(100 / portTICK_PERIOD_MS);
      continue;
    }

    esp_task_wdt_reset();
    int windowSize = (rms < 5) ? 5 : (rms < 15) ? 7
                                                : 9;
    if (windowSize % 2 == 0)
      windowSize++;
    movingAverage(vReal, smoothed, SAMPLES / 2, windowSize);

    double maxFFT = 0;
    for (int i = 0; i < SAMPLES / 2; i++)
    {
      if (smoothed[i] > maxFFT)
        maxFFT = smoothed[i];
    }

    // for (int i = START_BIN; i <= END_BIN; i++)
    // {
    //   feature[i - START_BIN] = smoothed[i];
    // }
    xQueueReceive(Queue_dataPzem, &datEnergy, 0);
    xQueueReceive(Queue_dataToF, &distance, 0);
    // String status = klasifikasiKeausan(rms, maxFFT, datEnergy.current, distance);
    // dat.KlasifikasiStatus = status;
    dat.maxAmplitude = maxFFT;
    dat.rmsAmplitude = rms;

    // int num;
    // if (status == "Idle")
    //   num = 0;
    // else if (status == "Normal")
    //   num = 1;
    // else
    //   num = 2;

    double X_1[] = {static_cast<double>(datEnergy.power), static_cast<double>(rms), static_cast<double>(datEnergy.current), static_cast<double>(maxFFT)};
    int result = predict(X_1);

    Serial.printf("Predicted: %d\n", result);

    xQueueSend(Queue_Vreal, &feature, 0);
    xQueueSend(Queue_dataFFT, &dat, 0);
    esp_task_wdt_reset();
    vTaskDelay(1 / portTICK_PERIOD_MS);
  }
}

String klasifikasiKeausan(double rms, double maxFFT, float arus, float tof)
{
  if (arus < 1.6 && tof > 17)
  {
    return "Idle";
  }
  else if (rms < 30.0 && maxFFT < 800.0)
  {
    return "Normal";
  }
  else
  {
    return "Aus";
  }
}

void movingAverage(double *input, double *output, int len, int windowSize)
{
  int halfWindow = windowSize / 2;
  for (int i = 0; i < len; i++)
  {
    double sum = 0;
    int count = 0;
    for (int j = -halfWindow; j <= halfWindow; j++)
    {
      int idx = i + j;
      if (idx >= 0 && idx < len)
      {
        sum += input[idx];
        count++;
      }
    }
    output[i] = sum / count;
  }
}

bool isGetaranValid(double *spectrum, int size, double freqResolution)
{
  double lowEnergy = 0;
  double highEnergy = 0;
  for (int i = 0; i < size; i++)
  {
    double freq = i * freqResolution;
    if (freq >= 0 && freq < 10)
      lowEnergy += spectrum[i];
    else if (freq >= 20 && freq <= 300)
      highEnergy += spectrum[i];
  }
  return (highEnergy > lowEnergy * 2);
}