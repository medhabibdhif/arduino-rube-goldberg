#define ctsPin 3 // Pin for capactitive touch sensor
 
//int ledPin = 5; // pin for the LED
 
void setup() {
  Serial.begin(9600);
  //pinMode(ledPin, OUTPUT);  
  pinMode(ctsPin, INPUT);
}
 
void loop() {
  if (isTouch()==1) {
    Serial.println("TOUCHED");    
    }
  else {
    Serial.println("not touched");    
    }  
  delay(500);

  
}



int isTouch(){  
  int ctsValue = digitalRead(ctsPin);
  if (ctsValue == HIGH){
    //digitalWrite(ledPin, HIGH);
    return 1 ;
  }
  else{
    //digitalWrite(ledPin,LOW);
    return 0;
  } 
  
  }
