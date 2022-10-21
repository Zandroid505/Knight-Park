// Kobe Conomon
// Zakaria Antifit
// Last modified: 10/21/2022
// Program that reads data from a HC-SR04 Ultrasonic Sensor to an ESP 32, and sends it to an MQTT broker (in this case, a 
// Raspberry Pi 4 running Ubuntu Server OS)

#include <String.h>

#include <Ultrasonic.h>
#include <PubSubClient.h> // Connect and publish to the MQTT broker
#include <WiFi.h> // Enables the ESP32 to connect to the local network (via WiFi)

// WiFi variables
// const char* ssid = "CenturyLink9364";
// const char* wifi_password = "a7k3fdaaef8caa";

// const char* ssid = "UCF_WPA2";
// const char* wifi_password = "BaSEbAll.,/251111";

// const char* ssid = "UCF_Guest";
// const char* wifi_password;

// We might need to use my mobile hotspot if UCF wifi is going to be finnicky (spoiler: it will be)
const char* ssid = "Hacker";
const char* wifi_password = "yEa b011";

// MQTT variables
const char* broker_IP = "192.168.0.51";
const char* RFID_topic = "home/bedroom/id";
const char* MQTT_username = "kconomon";
const char* MQTT_passwd = "Baseball.,/251";
const char* client_ID = "client_bedroom";

// Current state of connections
int wifi_flag = 0;
int MQTT_flag = 0;

// trigger and echo pins - read data from sensor to ESP (will need a lot more of these)
int trig = 15; // ESP32 pin GIOP15
int echo = 2; // ESP32 pin GIOP2

int distTrigger = 200;

WiFiClient wifiClient; // Creates client object that can connect to a specified IP and port
PubSubClient client(broker_IP, 1883, wifiClient); // Creates client object that allows you to use MQTT

Ultrasonic ultrasonic(trig, echo); // ultrasonic sensor object

// Function taken from article: https://diyi0t.com/microcontroller-to-raspberry-pi-wifi-mqtt-communication/
// Custom function to connet to the MQTT broker via WiFi
void connect_MQTT(){
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect to the WiFi
  WiFi.begin(ssid, wifi_password);

  // Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Debugging - Output the IP Address of the ESP32
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  wifi_flag = 1;

  // Connect to MQTT Broker
  if (client.connect(client_ID, MQTT_username, MQTT_passwd)) {
    Serial.println("Connected to MQTT Broker!");
    MQTT_flag = 1;
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
    MQTT_flag = 0;
  }
}

void setup() {
  int distance;
  Serial.begin(115200); // ESP32 baud rate
}

void loop() {
  // Connect to wifi and MQTT broker
  while(!(wifi_flag && MQTT_flag))
  {
    connect_MQTT();
    Serial.setTimeout(10000);
  }

  distance = ultrasonic.read();

  if (distance < distTrigger)
  {
    Serial.println(distance);
    String(distance)
    PublishSensorInfo();
  }
  delay(10);
}

void PublishSensorInfo()
{
  // PUBLISH to the MQTT Broker 
  if (client.publish(RFID_topic, distance)) {
    Serial.println("ID sent!");
  }
  // Again, client.publish will return a boolean value depending on whether it succeded or not.
  // If the message failed to send, we will try again, as the connection may have broken.
  else {
    Serial.println("ID failed to send. Reconnecting to MQTT Broker and trying again");
    if(client.connect(client_ID, MQTT_username, MQTT_passwd)) 
      Serial.println("Reconnected");
    delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
    client.publish(RFID_topic, distance);
  }
  // client.disconnect();  // disconnect from the MQTT broker
  delay(1000*2);       // Ready for new card every 2 seconds
}
