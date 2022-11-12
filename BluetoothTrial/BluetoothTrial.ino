// Kobe Conomon
// Last edited: 11/11 - added lights & made most variables local to loop()

// Creates a bridge between Serial and Classical Bluetooth (SPP)
// and also demonstrate that SerialBT have the same functionalities of a normal Serial.
// Reads Ultrasonic Sensor (HC-SR04) distance, and sends flag to Python script
// when someone is within appropriate distance.

#include "BluetoothSerial.h"
#include <Ultrasonic.h>

// Creating objects for each sensor
BluetoothSerial SerialBT;

  // creating echo & trigger variables for each sensor
  // Format: Garage_floor_spot
  int trig_A_01_01 = 32;
  int echo_A_01_01 = 33;
  
  int trig_A_01_02 = 25;
  int echo_A_01_02 = 26;
  
  int trig_A_02_01 = 27;
  int echo_A_02_01 = 14;
  
  int trig_A_02_02 = 12;
  int echo_A_02_02 = 13;
  
  int trig_B_01_01 = 23;
  int echo_B_01_01 = 22;
  
  int trig_B_02_01 = 21;
  int echo_B_02_01 = 19;
  
  Ultrasonic A_01_01(trig_A_01_01, echo_A_01_01);
  Ultrasonic A_01_02(trig_A_01_02, echo_A_01_02);
  Ultrasonic A_02_01(trig_A_02_01, echo_A_02_01);
  Ultrasonic A_02_02(trig_A_02_02, echo_A_02_02);
  Ultrasonic B_01_01(trig_B_01_01, echo_B_01_01);
  Ultrasonic B_02_01(trig_B_01_01, echo_B_01_01);

  // Distance (in cm) that determines the minimum distance a car must be within the sensor in order to fill a parking spot
  int distTrigger = 15;
  
  // Distance variables 
  int distance_A_01_01;
  int distance_A_01_02;
  int distance_A_02_01;
  int distance_A_02_02;
  int distance_B_01_01;
  int distance_B_02_01;
  
  // variables for green lights
  int light_A_01_01 = 18;
  int light_A_01_02 = 5;
  int light_A_02_01 = 17;
  int light_A_02_02 = 16;
  int light_B_01_01 = 4;
  int light_B_02_01 = 15;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


void setup() {
  // Prepare serial monitor & Bluetooth device
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  pinMode(light_A_01_01, OUTPUT);
  pinMode(light_A_01_02, OUTPUT);
  pinMode(light_A_02_01, OUTPUT);
  pinMode(light_A_02_02, OUTPUT);
  pinMode(light_B_01_01, OUTPUT);
  pinMode(light_B_02_01, OUTPUT);
}

void loop() {
   
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }

  // Read distances
  distance_A_01_01 = A_01_01.read();
  distance_A_01_02 = A_01_02.read();
  // distance_A_02_01 = A_02_01.read();
  // distance_A_02_02 = A_02_02.read();
  // distance_B_01_01 = B_01_01.read();
  // distance_B_02_01 = B_02_01.read();

  distance_A_02_01 = 400;
  distance_A_02_02 = 400;
  distance_B_01_01 = 400;
  distance_B_02_01 = 400;
  
  // pass these to a single function
  if (distance_A_01_01 < distTrigger)
  {
    Serial.println("A_01_01 filled");
    digitalWrite(light_A_01_01, LOW);
  }
  else
    digitalWrite(light_A_01_01, HIGH);

  if (distance_A_01_02 < distTrigger)
  {
    Serial.println("A_01_02 filled");
    digitalWrite(light_A_01_02, LOW);
  }
  else
    digitalWrite(light_A_01_02, HIGH);

  if (distance_A_02_01 < distTrigger)
  {
    Serial.println("A_02_01 filled");
    digitalWrite(light_A_02_01, LOW);
  }
  else
    digitalWrite(light_A_02_01, HIGH);

  if (distance_A_02_02 < distTrigger)
  {
    Serial.println("A_02_02 filled");
    digitalWrite(light_A_02_02, LOW);
  }
  else
    digitalWrite(light_A_02_02, HIGH);

  if (distance_B_01_01 < distTrigger)
  {
    Serial.println("B_01_01 filled");
    digitalWrite(light_B_01_01, LOW);
  }
  else
    digitalWrite(light_B_01_01, HIGH);

  if (distance_B_02_01 < distTrigger)
  {
    Serial.println("B_02_01 filled");
    digitalWrite(light_B_02_01, LOW);
  }
  else
    digitalWrite(light_A_02_01, HIGH);

  // not sure if arduino clock is too fast for the sensor, site, and/or vice versa, so this (hopefully)
  // gives a chance for everything to catch up to one another
  delay(100);
}
