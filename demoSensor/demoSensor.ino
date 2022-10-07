// Kobe Conomon
// Last edited: 9/25 - edit time delay in loop; add distTrigger variable

// Reads Ultrasonic Sensor (HC-SR04) distance, and sends flag to Python script
// when someone is within appropriate distance

#include <Ultrasonic.h>

int trig = 15;
int echo = 2;

// Distance (in cm) that sends a signal to start the jumpscare video
int distTrigger = 150;
int distance;

Ultrasonic ultrasonic(trig, echo);


void setup() {
  Serial.begin(115200);
}

void loop() {
  distance = ultrasonic.read();

  if (distance < distTrigger)
  {
    Serial.println(distance);

    // Only sends 1 flag to RasPi; gives video time to play and people to move
    // delay(8000);
  }
  delay(10);
}
