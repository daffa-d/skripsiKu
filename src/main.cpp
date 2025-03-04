#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_VL53L0X.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "arduinoFFT.h"
#include "freertos/queue.h"

#define OUTPUT_READABLE_YAWPITCHROLL
#define EARTH_GRAVITY_MS2 9.80665

#define SAMPLES 64
#define SAMPLING_FREQUENCY 1000

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
MPU6050 mpu;


double vReal[SAMPLES];
double vImag[SAMPLES];
ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLES, SAMPLING_FREQUENCY);

xQueueHandle dataVibration_Queue = NULL;

int const INTERRUPT_PIN = 2; // Define the interruption #0 pin
bool blinkState;

bool DMPReady = false;
uint8_t MPUIntStatus;
uint8_t devStatus;
uint16_t packetSize;
uint8_t FIFOBuffer[64];

Quaternion q;
VectorInt16 aa;
VectorInt16 gy;
VectorInt16 aaWorld;
VectorFloat gravity;
volatile bool MPUInterrupt = false;
float gFactor = 2000.0 / 32767.0;

void DMPDataReady()
{
  MPUInterrupt = true;
}
void readIMU(void *pvParameters);
void FFT_Processing(void *pvParameters);

void setup()
{
  Wire.begin();
  Wire.setClock(400000);
  Serial.begin(115200);

  mpu.initialize();
  Serial.println(mpu.getRate());
  pinMode(INTERRUPT_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  if (mpu.testConnection() == false)
  {
    Serial.println("MPU6050 connection failed");
    while (true)
      ;
  }
  else
  {
    Serial.println("MPU6050 connection successful");
  }

  devStatus = mpu.dmpInitialize();
  mpu.setXGyroOffset(0);
  mpu.setYGyroOffset(0);
  mpu.setZGyroOffset(0);
  mpu.setXAccelOffset(0);
  mpu.setYAccelOffset(0);
  mpu.setZAccelOffset(0);

  if (devStatus == 0)
  {
    mpu.CalibrateAccel(6);
    mpu.CalibrateGyro(6);
    mpu.PrintActiveOffsets();
    mpu.setDMPEnabled(true);
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), DMPDataReady, RISING);
    MPUIntStatus = mpu.getIntStatus();
    DMPReady = true;
    packetSize = mpu.dmpGetFIFOPacketSize();
  }
  else
  {
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F(")"));
  }

  dataVibration_Queue = xQueueCreate(10, sizeof(float));

  xTaskCreatePinnedToCore(readIMU, "readIMU", 4096, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(FFT_Processing, "FFT_Processing", 4096, NULL, 1, NULL, 1);
}

void loop()
{
}

void readIMU(void *pvParameters)
{
  for (;;)
  {
    if (!DMPReady) return;

    
    if (mpu.dmpGetCurrentFIFOPacket(FIFOBuffer)) {
      mpu.dmpGetQuaternion(&q, FIFOBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetAccel(&aa, FIFOBuffer);
      mpu.dmpConvertToWorldFrame(&aaWorld, &aa, &q);

      float X_Accel = aaWorld.x * mpu.get_acce_resolution() * EARTH_GRAVITY_MS2;
      float Y_Accel = aaWorld.y * mpu.get_acce_resolution() * EARTH_GRAVITY_MS2;
      float Z_Accel = aaWorld.z * mpu.get_acce_resolution() * EARTH_GRAVITY_MS2;

      float vibration = sqrt(pow(X_Accel, 2) + pow(Y_Accel, 2) + pow(Z_Accel, 2));
      xQueueSend(dataVibration_Queue, &vibration, 0);
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void FFT_Processing(void *pvParamters){

  float vibration;
  for(;;) {
    if(xQueueReceive(dataVibration_Queue, &vibration, portMAX_DELAY) == pdTRUE) {
      for(int i = 0; i < SAMPLES; i++) {
        vReal[i] = vibration;
        vImag[i] = 0;
        vTaskDelay(10 / portTICK_PERIOD_MS);
      }
    }

    FFT.windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.compute(FFT_FORWARD);
    FFT.complexToMagnitude();
    
    float peak = FFT.majorPeak();
    Serial.println(peak, 6);
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}
