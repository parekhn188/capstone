
#define STDRESTPOS 450 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

int userRestPos = 0; 
int switchStatus = 0; 

String strumStatus = "";  

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT); 
  pinMode(D5, INPUT); 

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
  
  Serial.println();
  Serial.print("connected, IP Address: ");
  Serial.println(WiFi.localIP());

}

void loop() {

  int rawYData = analogRead(A0); 
  int trigger = digitalRead(D3); 
  int switchChord = digitalRead(D5); 
  Serial.println(switchChord);

  DynamicJsonDocument sendData(1024); 

  // With external trigger
    if(!trigger && rawYData != userRestPos) {
      strumStatus = "Is Strumming"; 
    } else {
      strumStatus = "Idle"; 
    }

    if(switchChord){
      switchStatus = 1; 
    } else {
      switchStatus = 0; 
    }
  
  //Serial.println(strumStatus); 

  sendData["Strum Status"] = strumStatus;
  sendData["Switch Chord"] = switchStatus; 

  String postData = sendData.as<String>(); 
  //Serial.println(postData); 

  if(WiFi.status() == WL_CONNECTED) {

    HTTPClient http; 
    //Get request send 
    http.begin("http://192.168.2.18:3000/sendData"); 
    http.addHeader("Content-Type", "application/json"); 

    //int httpCode = http.POST ("{\"Strum Status\":\"Strumming\"}");
    int httpCode = http.POST (postData);

    String payload = http.getString(); 
    Serial.print(payload); 

    if (httpCode < 1) {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    } else {
      Serial.println(httpCode); 
      Serial.println(payload); 
    }
    
    http.end(); 

    delay(500); 

  }
  
}
