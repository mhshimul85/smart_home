#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>


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

// WiFi Parameters
const char* ssid = "hasan";         //Your Wifi name
const char* password = "12345678";  //Your Wifi password

void setup() {
  Serial.begin(9600);
  delay(1000);
  
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  
  //digitalWrite(D0, 0);
  //digitalWrite(D1, 0);
  //digitalWrite(D2, 0);
  //digitalWrite(D3, 0);
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  Serial.println(" ");
}

void loop() {
  // Check WiFi Status
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;  //Object of class HTTPClient
     http.begin("http://besmart2020.000webhostapp.com/one/val.php");  // Your json value url
    int httpCode = http.GET();
    //Check the returning code                                                                  
    if (httpCode > 0) {
      // Parsing
      const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
      DynamicJsonBuffer jsonBuffer(bufferSize);
      JsonObject& root = jsonBuffer.parseObject(http.getString());
      // Parameters
      int relay_one = root["relay_one"];
      int relay_two = root["relay_two"];
      int relay_three = root["relay_three"];
      int relay_four = root["relay_four"];
      // const char* name = root["name"];     // "Hasan"
      // Output to serial monitor
      Serial.print(relay_one);
      Serial.print(" ");
      Serial.print(relay_two);
      Serial.print(" ");
      Serial.print(relay_three);
      Serial.print(" ");
      Serial.print(relay_four);
      Serial.println(" ");
      //Serial.println(http.getString());
      if(relay_one == 1){
        digitalWrite(D0, HIGH);
      }else{
        digitalWrite(D0, LOW);
      }

      if(relay_two == 1){
        digitalWrite(D1, HIGH);
      }else{
        digitalWrite(D1, LOW);
      }

      if(relay_three == 1){
        digitalWrite(D2, HIGH);
      }else{
        digitalWrite(D2, LOW);
      }

      if(relay_four == 1){
        digitalWrite(D3, HIGH);
      }else{
        digitalWrite(D3, LOW);
      }
    }
    http.end();   //Close connection
  }
  // Delay
  delay(5000);
}
