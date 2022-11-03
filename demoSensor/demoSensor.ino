// Kobe Conomon
// Last edited: 9/25 - edit time delay in loop; add distTrigger variable

// Reads Ultrasonic Sensor (HC-SR04) distance, and sends flag to Python script
// when someone is within appropriate distance

#include <Ultrasonic.h>

// creating echo & trigger variables for each sensor

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
Ultrasonic A_01_01(trig_A_01_01, echo_A_01_01);
Ultrasonic A_01_02(trig_A_01_02, echo_A_01_02);
Ultrasonic A_02_01(trig_A_02_01, echo_A_02_01);
Ultrasonic A_02_02(trig_A_02_02, echo_A_02_02);
Ultrasonic B_01_01(trig_B_01_01, echo_B_01_01);
Ultrasonic B_02_01(trig_B_01_01, echo_B_01_01);


void setup() {
  Serial.begin(115200);
}

void loop() {
  distance_A_01_01 = A_01_01.read();
  distance_A_01_02 = A_01_02.read();
  distance_A_02_01 = B_01_01.read();
  distance_A_02_02 = A_02_02.read();
  distance_B_01_01 = B_01_01.read();
  distance_B_02_01 = B_02_01.read();

  if (distance_A_01_01 < distTrigger)
  {
    Serial.println(distance_A_01_01);

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
  
}
