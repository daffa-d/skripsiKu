#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_VL53L0X.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "arduinoFFT.h"
#include "freertos/queue.h"
#include "esp_task_wdt.h"

#define EARTH_GRAVITY_MS2 9.80665
#define SAMPLES 1024
#define SAMPLING_FREQUENCY 1000

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
MPU6050 mpu;

double vReal[SAMPLES];
double vImag[SAMPLES];
ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, SAMPLES, SAMPLING_FREQUENCY);

int16_t ax, ay, az;
unsigned long lastTime = 0;

void readIMU(void *pvParameters);

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  pinMode(LED_BUILTIN, OUTPUT);

  mpu.initialize();
  if (mpu.testConnection() == false)
  {
    Serial.println("MPU6050 connection failed");
    int i = 0;
    while (i < 5)
    {
      digitalWrite(LED_BUILTIN, HIGH);
      vTaskDelay(2000 / portTICK_PERIOD_MS);
      digitalWrite(LED_BUILTIN, LOW);
      vTaskDelay(2000 / portTICK_PERIOD_MS);
      i++;
    }
    if (i == 5)
      ESP.restart();
  }

  // mpu.setXAccelOffset(0);
  // mpu.setYAccelOffset(0);
  // mpu.setZAccelOffset(0);
  // mpu.setXGyroOffset(0);
  // mpu.setYGyroOffset(0);
  // mpu.setZGyroOffset(0);

  mpu.CalibrateAccel(6);

  xTaskCreatePinnedToCore(readIMU, "readIMU", 4096, NULL, 1, NULL, 0);
}

void loop()
{
}

void readIMU(void *pvParameters)
{
  int retry = 0;
  for (;;)
  {
    lastTime = micros();

    for (int i = 0; i < SAMPLES; i++)
    {
      mpu.getAcceleration(&ax, &ay, &az);

      float accelX_g = ax / 16384.0;
      float accelY_g = ay / 16384.0;
      float accelZ_g = az / 16384.0;

      float accelX_ms2 = accelX_g * 9.80665;
      float accelY_ms2 = accelY_g * 9.80665;
      float accelZ_ms2 = accelZ_g * 9.80665;

      if (isnan(accelX_ms2) || isnan(accelY_ms2) || isnan(accelZ_ms2))
      {
        retry++;
        vTaskDelay(10 / portTICK_PERIOD_MS);
      }
      else if (accelX_ms2 == 0 || accelY_ms2 == 0 || accelZ_ms2 == 0)
      {
        retry++;
        vTaskDelay(10 / portTICK_PERIOD_MS);
      }
      else
      {
        retry = 0;
      }

      if (retry > 5)
      {
        ESP.restart();
      }

      vReal[i] = accelX_ms2;
      vImag[i] = 0;

      while (micros() - lastTime < (1000000 / SAMPLING_FREQUENCY));
      lastTime = micros();
    }

    FFT.dcRemoval();
    FFT.windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.compute(FFT_FORWARD);
    FFT.complexToMagnitude();

    for (int i = 1; i < SAMPLES / 2; i++) {
      double frequency = (i * SAMPLING_FREQUENCY) / SAMPLES;
      Serial.print(frequency);
      Serial.print(",");
      Serial.println(vReal[i]);
  }

    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}