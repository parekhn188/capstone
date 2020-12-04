
#define STDRESTPOS 350

int restUserPosition = 0;
boolean isStrumming = 0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //For trigger detection 
  pinMode(8, INPUT); 
  //Store user rest point
  if(digitalRead(8) == HIGH){
   restUserPosition = analogRead(A0); 
  }
  Serial.print(restUserPosition); 
}

void loop() {
  // put your main code here, to run repeatedly:
  int rawY = analogRead(A0); 
  int trigger = digitalRead(8); 
  //Serial.print(rawY);
  if(trigger && rawY != restUserPosition){
    isStrumming = 1; 
  } else {
    isStrumming = 0; 
  }
  //Serial.print(isStrumming);
  //Serial.print("\n");  
  //delay(50);
}
