// Kobe Conomon
// Last edited: 11/11 - added lights & made most variables local to loop()

// Reads Ultrasonic Sensor (HC-SR04) distance, and sends flag to Python script
// when someone is within appropriate distance.

// Format: garage_floor_spot_takenOrNot

#include <Ultrasonic.h>

  // creating echo & trigger variables for each sensor
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

  // Creating objects for each sensor
  Ultrasonic A_01_01(trig_A_01_01, echo_A_01_01);
  Ultrasonic A_01_02(trig_A_01_02, echo_A_01_02);
  Ultrasonic A_02_01(trig_A_02_01, echo_A_02_01);
  Ultrasonic A_02_02(trig_A_02_02, echo_A_02_02);
  Ultrasonic B_01_01(trig_B_01_01, echo_B_01_01);
  Ultrasonic B_02_01(trig_B_02_01, echo_B_02_01);

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
  int light_B_02_01 = 0;

  boolean flag[6] = {0,0,0,0,0,0};


void setup() {
  // Prepare serial monitor & Bluetooth device
  Serial.begin(115200);

  pinMode(light_A_01_01, OUTPUT);
  pinMode(light_A_01_02, OUTPUT);
  pinMode(light_A_02_01, OUTPUT);
  pinMode(light_A_02_02, OUTPUT);
  pinMode(light_B_01_01, OUTPUT);
  pinMode(light_B_02_01, OUTPUT);

  digitalWrite(light_A_01_01, HIGH);
  digitalWrite(light_A_01_02, HIGH);
  digitalWrite(light_A_02_01, HIGH);
  digitalWrite(light_A_02_02, HIGH);
  digitalWrite(light_B_01_01, HIGH);
  digitalWrite(light_B_02_01, HIGH);
}

void loop() {  

  // Read distances
  distance_A_01_01 = A_01_01.read();
  distance_A_01_02 = A_01_02.read();
  distance_A_02_01 = A_02_01.read();
  distance_A_02_02 = A_02_02.read();
  distance_B_01_01 = B_01_01.read();
  distance_B_02_01 = B_02_01.read();
  
  // pass these to a single function
  if (distance_A_01_01 < distTrigger && flag[0] != 1)
  {
    Serial.println("A_01_01_1");
    digitalWrite(light_A_01_01, LOW);
    flag[0] = 1;
  }
  else if(distance_A_01_01 >= distTrigger && flag[0] != 0)
  {
    Serial.println("A_01_01_0");
    digitalWrite(light_A_01_01, HIGH);
    flag[0] = 0;
  }
  if (distance_A_01_02 < distTrigger && flag[1] != 1)
  {
    Serial.println("A_01_02_1");
    digitalWrite(light_A_01_02, LOW);
    flag[1] = 1;
  }
  else if (distance_A_01_02 >= distTrigger && flag[1] != 0)
  {
    Serial.println("A_01_02_0");
    digitalWrite(light_A_01_02, HIGH);
    flag[1] = 0;   
  }

  if (distance_A_02_01 < distTrigger && flag[2] != 1)
  {
    Serial.println("A_02_01_1");
    digitalWrite(light_A_02_01, LOW);
    flag[2] = 1;
  }
  else if(distance_A_02_01 >= distTrigger && flag[2] != 0)
  {
    Serial.println("A_02_01_0");
    digitalWrite(light_A_02_01, HIGH);
    flag[2] = 0;
  }

  if (distance_A_02_02 < distTrigger && flag[3] != 1)
  {
    Serial.println("A_02_02_1");
    digitalWrite(light_A_02_02, LOW);
    flag[3] = 1;
  }
  else if(distance_A_02_02 >= distTrigger && flag[3] != 0)
  {
    Serial.println("A_02_02_0");
    digitalWrite(light_A_02_02, HIGH);
    flag[3] = 0;
  }

  if (distance_B_01_01 < distTrigger && flag[4] != 1)
  {
    Serial.println("B_01_01_1");
    digitalWrite(light_B_01_01, LOW);
    flag[4] = 1;
  }
  else if(distance_B_01_01 >= distTrigger && flag[4] != 0){
    Serial.println("B_01_01_0");
    digitalWrite(light_B_01_01, HIGH);
    flag[4] = 0;
  }

  if (distance_B_02_01 < distTrigger && flag[5] != 1)
  {
    Serial.println("B_02_01_1");
    digitalWrite(light_B_02_01, LOW);
    flag[5] = 1;
  }
  else if(distance_B_02_01 >= distTrigger && flag[5] != 0){
    Serial.println("B_02_01_0");
    digitalWrite(light_B_02_01, HIGH);
    flag[5] = 0;
  }

  // Repeat every 2.5 seconds
  delay(2500);
}
