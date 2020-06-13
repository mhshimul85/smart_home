/* This sketch sends data via HTTP GET requests to esp8266-shop.com and returns the website in html format which is printed on the console */
#include <ESP8266WiFi.h> 

// Defining Pin For NodeMcu
#define D0 16
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13
#define D8 15
#define D9 3
#define D10 1


// defines pins numbers
const int trigPin = D1;
const int echoPin = D2;

const char* ssid = ""; //replace with your own wifi ssid 
const char* password = ""; //replace with your own //wifi ssid password 
const char* host = "besmart2020.000webhostapp.com";

long duration;
int distance;
int waterLevel;

void setup() { 
Serial.begin(115200); 
delay(1000); // We start by connecting to a WiFi network Serial.println();

pinMode(trigPin, OUTPUT);              // Sets the trigPin as an Output
pinMode(echoPin, INPUT); 

Serial.println(); Serial.print("Connecting to ");
Serial.println(ssid);
/* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default, would try to act as both a client and an access-point and could cause network-issues with your other WiFi-devices on your WiFi-network. */
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected"); Serial.println("IP address: "); Serial.println(WiFi.localIP()); } int value = 0; 

void loop() { 
delay(5000); 
++value; 

Serial.print("connecting to ");
Serial.println(host); // Use WiFiClient class to create TCP connections
WiFiClient client;
const int httpPort = 80;
if (!client.connect(host, httpPort)) {
Serial.println("connection failed");
return;
}
// We now create a URI for the request
//this url contains the informtation we want to send to the server
//if esp8266 only requests the website, the url is empty

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);                   
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration*0.034/2;

  waterLevel = ((35 - distance)*0.033333333333333)*100;
  if (waterLevel > 100){
      waterLevel = 100;
  } else if (waterLevel < 0){
      waterLevel = 0;
  }
String url = "https://besmart2020.000webhostapp.com/one/update.php?relay=tank&value=";
url += waterLevel;
/* url += "?param1=";
url += param1;
url += "?param2=";
url += param2;
*/
Serial.print("Requesting URL: ");
Serial.println(url); // This will send the request to the server
client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
unsigned long timeout = millis();
while (client.available() == 0) {
if (millis() - timeout > 5000)
{ Serial.println(">>> Client Timeout !");
client.stop(); return; } } // Read all the lines of the reply from server and print them to Serial
while (client.available())
{ String line = client.readStringUntil('\r'); Serial.print(line);
}
Serial.println();
Serial.println("closing connection"); 
}
