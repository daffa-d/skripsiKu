#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_VL53L0X.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "arduinoFFT.h"
#include "freertos/queue.h"

#define EARTH_GRAVITY_MS2 9.80665

#define SAMPLES 4096
#define SAMPLING_FREQUENCY 50

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
MPU6050 mpu;

double vReal[SAMPLES];
double vImag[SAMPLES];
ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLES, SAMPLING_FREQUENCY);

int const INTERRUPT_PIN = 2; // Define the interruption #0 pin
bool blinkState;

bool DMPReady = false;
uint8_t MPUIntStatus;
uint8_t devStatus;
uint16_t packetSize;
uint8_t FIFOBuffer[64];
uint32_t nextSampleTime;

Quaternion q;
VectorInt16 aa;
VectorInt16 gy;
VectorInt16 aaWorld;
VectorFloat gravity;
VectorInt16 aaReal;
volatile bool MPUInterrupt = false;

void DMPDataReady()
{
  MPUInterrupt = true;
}
void readIMU(void *pvParameters);

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);

  mpu.initialize();
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
    // mpu.PrintActiveOffsets();
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

  xTaskCreatePinnedToCore(readIMU, "readIMU", 4096, NULL, 1, NULL, 0);

  nextSampleTime = micros();
}

void loop()
{
}

void readIMU(void *pvParameters)
{
  float vibration = 0;
  for (;;)
  {
    if (!DMPReady)
      continue;

    for (int i = 0; i < SAMPLES; i++)
    {

      if (mpu.dmpGetCurrentFIFOPacket(FIFOBuffer))
      {
        mpu.dmpGetQuaternion(&q, FIFOBuffer);
        mpu.dmpGetAccel(&aa, FIFOBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
        
        float X_Accel = aaReal.x * mpu.get_acce_resolution();
        float Y_Accel = aaReal.y * mpu.get_acce_resolution();
        
        vibration = sqrt(X_Accel * X_Accel + Y_Accel * Y_Accel);
        vReal[i] = vibration;
        vImag[i] = 0;
      } else {
        i--;
      }
    }

    FFT.dcRemoval();
    FFT.windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.compute(FFT_FORWARD);
    FFT.complexToMagnitude();

    for (int i = 1; i < (SAMPLES / 2); i++)
    {
      double freq = (i * SAMPLING_FREQUENCY) / SAMPLES;
      Serial.printf("%f\n", vReal[i]);
    }

    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}
