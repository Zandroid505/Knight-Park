// Kobe Conomon
// Last edited: 11/3 - added multiple sensor objects

// Creates a bridge between Serial and Classical Bluetooth (SPP)
// and also demonstrate that SerialBT have the same functionalities of a normal Serial.
// Reads Ultrasonic Sensor (HC-SR04) distance, and sends flag to Python script
// when someone is within appropriate distance.

#include "BluetoothSerial.h"
#include <Ultrasonic.h>

// creating echo & trigger variables for each sensor
// Format: Garage_floor_spot

int trig_A_01_01 = 34;
int echo_A_01_01 = 35;

int trig_A_01_02 = 32;
int echo_A_01_02 = 33;

int trig_A_02_01 = 25;
int echo_A_02_01 = 26;

int trig_A_02_02 = 27;
int echo_A_02_02 = 14;

int trig_B_01_01 = 19;
int echo_B_01_01 = 18;

int trig_B_02_01 = 17;
int echo_B_02_01 = 16;

// Distance (in cm) that determines the minimum distance a car must be within the sensor in order to fill a parking spot
int distTrigger = 150;

// Distance variables 
int distance_A_01_01;
int distance_A_01_02;
int distance_A_02_01;
int distance_A_02_02;
int distance_B_01_01;
int distance_B_02_01;

// variables for green lights
int light_A_01_01 = 23;
int light_A_01_02 = 22;
int light_A_02_01 = 21;
int light_A_02_02 = 5;
int light_B_01_01 = 4;
int light_B_02_01 = 0;

// Creating objects for each sensor
BluetoothSerial SerialBT;

Ultrasonic A_01_01(trig_A_01_01, echo_A_01_01);
Ultrasonic A_01_02(trig_A_01_02, echo_A_01_02);
Ultrasonic A_02_01(trig_A_02_01, echo_A_02_01);
Ultrasonic A_02_02(trig_A_02_02, echo_A_02_02);
Ultrasonic B_01_01(trig_B_01_01, echo_B_01_01);
Ultrasonic B_02_01(trig_B_01_01, echo_B_01_01);

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }

  // 4 spots garage A first floor
  distance_A_01_01 = A_01_01.read();
  distance_A_01_02 = A_01_02.read();
  distance_A_02_01 = A_02_01.read();
  distance_A_02_02 = A_02_02.read();
  distance_B_01_01 = B_01_01.read();
  distance_B_02_01 = B_02_01.read();

  // pass these to a single function
  if (distance_A_01_01 < distTrigger)
  {
    SerialBT.write("1");
    // notify broker that spot is filled
    // turn spot light red
  }

  if (distance_A_01_02 < distTrigger)
  {
    Serial.println(distance_A_01_02);

    // notify broker that spot is filled
    // turn spot light red
  }

  if (distance_A_02_01 < distTrigger)
  {
    Serial.println(distance_A_02_01);

    // notify broker that spot is filled
    // turn spot light red
  }

  if (distance_A_02_02 < distTrigger)
  {
    Serial.println(distance_A_02_02);

    // notify broker that spot is filled
    // turn spot light red
  }

  if (distance_B_01_01 < distTrigger)
  {
    Serial.println(distance_B_01_01);

    // notify broker that spot is filled
    // turn spot light red
  }

  if (distance_B_02_01 < distTrigger)
  {
    Serial.println(distance_B_02_01);

    // notify broker that spot is filled
    // turn spot light red
  }

  // not sure if arduino clock is too fast for the sensor, or broker, and/or vice versa, so this (hopefully)
  // gives a chance for everything to catch up to one another
  delay(20);
}
