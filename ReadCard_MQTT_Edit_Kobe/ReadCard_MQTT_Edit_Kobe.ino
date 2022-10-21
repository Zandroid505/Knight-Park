// Kobe Conomon
// Zakaria Antifit
// Last modified: 5/31/2022
// Program that reads data from a PICC (an RFID tag or card) using a MFRC522-based RFID reader on the Arduino SPI interface

#include <SPI.h>
#include <MFRC522.h>
#include <PubSubClient.h> // Connect and publish to the MQTT broker
#include <WiFi.h> // Enables the ESP32 to connect to the local network (via WiFi)

// WiFi variables
const char* ssid = "CenturyLink9364";
const char* wifi_password = "a7k3fdaaef8caa";

// MQTT variables
const char* broker_IP = "192.168.0.50";
const char* RFID_topic = "home/bedroom/id";
const char* MQTT_username = "kconomon";
const char* MQTT_passwd = "Baseball.,/251";
const char* client_ID = "client_bedroom";

// Current state of connections
int wifi_flag = 0;
int MQTT_flag = 0;

WiFiClient wifiClient; // Creates client object that can connect to a specified IP and port
PubSubClient client(broker_IP, 1883, wifiClient); // Creates client object that allows you to use MQTT

//SPI Setup
#define SS_PIN  5  // ESP32 pin GIOP5  (SDA)
#define RST_PIN 27 // ESP32 pin GIOP27 (RST)

String uid;

MFRC522 rfid(SS_PIN, RST_PIN);

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
  Serial.begin(9600); // ESP32 baud rate
  SPI.begin(); // initialize SPI bus
  rfid.PCD_Init(); // initialize MFRC522
}

void loop() {
  // Connect to wifi and MQTT broker
  while(!(wifi_flag && MQTT_flag))
  {
    connect_MQTT();
    Serial.setTimeout(10000);
  }
  
  if (rfid.PICC_IsNewCardPresent()) 
  { 
    // new tag is available
    if (rfid.PICC_ReadCardSerial()) 
    { 
      Serial.println(uid);
      convertCardID(rfid.uid.uidByte, rfid.uid.size); // function to read card UID
      
      Serial.println("UID: " + uid); // prints uid with newline
      rfid.PICC_HaltA(); // halt PICC

      PublishID();
    }
  }
}

// Send data from the publisher to the broker
void PublishID()
{
  // PUBLISH to the MQTT Broker 
  if (client.publish(RFID_topic, uid.c_str())) {
    Serial.println("ID sent!");
  }
  // Again, client.publish will return a boolean value depending on whether it succeded or not.
  // If the message failed to send, we will try again, as the connection may have broken.
  else {
    Serial.println("ID failed to send. Reconnecting to MQTT Broker and trying again");
    if(client.connect(client_ID, MQTT_username, MQTT_passwd)) 
      Serial.println("Reconnected");
    delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
    client.publish(RFID_topic, uid.c_str());
  }
  // client.disconnect();  // disconnect from the MQTT broker
  delay(1000*2);       // Ready for new card every 2 seconds
}

// Converts uid from hex to a string
void convertCardID(byte * buffer, byte bufferSize)
{
  uid = ""; // increment uid with buffer
  for (int i = 0; i < bufferSize; i++) 
    uid = uid + String(buffer[i], HEX);
}
