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


#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT); 
  
  Serial.begin(115200); 
  Serial.println();

  WiFi.mode(WIFI_STA); 

  WiFi.begin("ssd", "pass");
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("connected, IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
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
    

    /* 
    //Post Request Send
    http.begin("http://192.168.2.18:3000/get"); s
    int httpCode = http.GET();
    String payload = http.getString(); 

    if (httpCode < 1) {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    } else {
      Serial.println(httpCode); 
      Serial.println(payload); 
    }
    */

    http.end(); 

  }
}
