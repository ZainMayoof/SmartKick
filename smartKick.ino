#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>
#include <Stepper.h>

Adafruit_MPU6050 mpu;

// Pins on driver
const int motorXPins[] = {8, 9, 10, 11}; 
const int motorYPins[] = {4, 5, 6, 7};

// Stepper motors objects
Stepper motorX(180, motorXPins[0], motorXPins[1], motorXPins[2], motorXPins[3]);
Stepper motorY(180, motorYPins[0], motorYPins[1], motorYPins[2], motorYPins[3]);

const int threshold = 400;
const int hysteresis = 100; 

void setup() {
  Serial.begin(9600);
  while (!Serial)
    delay(10);

  Serial.println("Adafruit MPU6050 test!");

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  Serial.println("");
  delay(100);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  int accelX = (int)(a.acceleration.x * 100); // Multiply by 100 for two decimal places
  int accelY = (int)(a.acceleration.y * 100); // Multiply by 100 for two decimal places

  // Check if x exceeds the threshold with hysteresis
  if (accelX > threshold && accelX > (threshold + hysteresis)) {
    Serial.print("Action Detected for X! X: ");
    Serial.println(accelX);

    // Move the X motor in the appropriate direction
    motorX.setSpeed(320);
    motorX.step(180); // Clockwise rotation (180 steps)
    delay(10); // delay between motor movements //100
  } else if (accelX < -threshold && accelX < (-threshold - hysteresis)) {
    Serial.print("Action Detected for X! X: ");
    Serial.println(accelX);

    // Move the X motor in the appropriate direction
    motorX.setSpeed(320);
    motorX.step(-180); // Anti-clockwise rotation (180 steps)
    delay(0); // delay between motor movements
  }

  // Check if y exceeds the threshold with hysteresis
  if (accelY > threshold && accelY > (threshold + hysteresis)) {
    Serial.print("Action Detected for Y! Y: ");
    Serial.println(accelY);

    // Move the Y motor in the appropriate direction
    motorY.setSpeed(320);
    motorY.step(180); // Clockwise rotation (180 steps)
    delay(0); // delay between motor movements
  } else if (accelY < -threshold && accelY < (-threshold - hysteresis)) {
    Serial.print("Action Detected for Y! Y: ");
    Serial.println(accelY);

    // Move the Y motor in the appropriate direction
    motorY.setSpeed(320);
    motorY.step(-180); // Anti-clockwise rotation (180 steps)
    delay(0); // delay between motor movements
  }

  // Check if neither x nor y exceeds the threshold
  if (abs(accelX) <= threshold && abs(accelY) <= threshold) {
    Serial.println("NO ACTION");
  }

  Serial.println("");
  delay(1);
}