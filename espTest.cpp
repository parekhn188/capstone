/*Arduino Example 
//#include <Arduino.h>
#include <ESP8266Wifi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

ESP8266WiFiMulti WifiMulti; 

void setup() {
  Serial.begin(115200); 
  pinMode(LED_BUILTIN, OUTPUT); 

  WiFi.mode(WIFI_STA); 
  WifiMulti.addAP("Krishna", "4162893529"); 

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected to ip "); 
  Serial.print(WiFi.localIP());
  Serial.println(); 
}

void loop() {
  if((WifiMulti.run() == WL_CONNECTED)) {
    
    WiFiClient client; 
    HTTPClient http;

    Serial.print("[HTTP] begin ...\n"); 
    if (http.begin(client, "http://192.168.2.18:3000/get")) {
      Serial.print("Sending GET Request\n"); 

      int httpCode = http.GET(); 
      
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();

    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }
  delay(10000);
}

*/

#define STDRESTPOS 450 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

int userRestPos = 0; 
String strumStatus = "";  

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT); 

  Serial.begin(115200); 
  Serial.println();

  WiFi.mode(WIFI_STA); 

  WiFi.begin("Krishna", "4162893529");
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  } 

  //With external trigger
  if (digitalRead(D3) == LOW) {
    userRestPos = analogRead(A0); 
  }
  
  Serial.println(userRestPos); 

  /*
  Serial.println();
  Serial.print("connected, IP Address: ");
  Serial.println(WiFi.localIP());
  */
}

void loop() {

  int rawYData = analogRead(A0); 
  int trigger = digitalRead(D3); 

  //Serial.println(rawYData); 
  //Serial.println(trigger); 

  // With external trigger
    if(!trigger && rawYData != userRestPos) {
      strumStatus = "Is Strumming"; 
    } else {
      strumStatus = "Idle"; 
    }
  

  Serial.println(strumStatus); 
 
  delay(500); 

  /*
  if(WiFi.status() == WL_CONNECTED) {

    HTTPClient http; 
    //Get request send 
    http.begin("http://192.168.2.18:3000/sendData"); 
    http.addHeader("Content-Type", "application/json"); 

    int httpCode = http.POST ("{\"Strum Status\":\"Strumming\"}");
    String payload = http.getString(); 

    if (httpCode < 1) {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    } else {
      Serial.println(httpCode); 
      Serial.println(payload); 
    }
    
    http.end(); 

  }
  */
}
