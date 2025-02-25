#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_VL53L0X.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#define OUTPUT_READABLE_YAWPITCHROLL

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
MPU6050 mpu;

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
VectorInt16 aaReal;  
VectorInt16 aaWorld; 
VectorFloat gravity; 
float euler[3];      
float ypr[3];        

uint8_t teapotPacket[14] = {'$', 0x02, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, 0x00, '\r', '\n'};

volatile bool MPUInterrupt = false; 
void DMPDataReady()
{
  MPUInterrupt = true;
}

void setup()
{
  Wire.begin();
  Wire.setClock(400000);


  Serial.begin(115200); 
  while (!Serial)
    ;

  mpu.initialize();
  pinMode(INTERRUPT_PIN, INPUT);

  if (mpu.testConnection() == false)
  {
    Serial.println("MPU6050 connection failed");
    while (true);
  }
  else
  {
    Serial.println("MPU6050 connection successful");
  }

  Serial.println(F("\nSend any character to begin: "));
  while (Serial.available() && Serial.read())
    ; // Empty buffer
  while (!Serial.available())
    ; // Wait for data
  while (Serial.available() && Serial.read())
    ; // Empty buffer again

  Serial.println(F("Initializing DMP..."));
  devStatus = mpu.dmpInitialize();

  /* Supply your gyro offsets here, scaled for min sensitivity */
  mpu.setXGyroOffset(0);
  mpu.setYGyroOffset(0);
  mpu.setZGyroOffset(0);
  mpu.setXAccelOffset(0);
  mpu.setYAccelOffset(0);
  mpu.setZAccelOffset(0);

  /* Making sure it worked (returns 0 if so) */
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
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  if (!DMPReady)
    return;

  if (mpu.dmpGetCurrentFIFOPacket(FIFOBuffer))
  {

    mpu.dmpGetQuaternion(&q, FIFOBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    mpu.dmpGetQuaternion(&q, FIFOBuffer);
    mpu.dmpGetAccel(&aa, FIFOBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);

    /* Blink LED to indicate activity */
    blinkState = !blinkState;
    digitalWrite(LED_BUILTIN, blinkState);
  }
}