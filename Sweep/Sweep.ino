/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int isTurned = 0;
void setup() {
    Serial.begin(9600);
  //myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(9, OUTPUT);
}
void loop() {
if (isTurned==0){
turn();
isTurned=1;
  }  
else {
    Serial.println("already turned");// goes from 0 degrees to 180 degrees  
     delay(2000); 
  }
  
}



void turn(){
  int i =0;
  int j= 0;
  int pos = 0;    // variable to store the servo position
  
   digitalWrite(9, HIGH); 
   for (i ;i <= 1; i += 1) { 
    Serial.println(i);// goes from 0 degrees to 180 degrees
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
    }
  }
   digitalWrite(9, LOW); 
   for (j ;j <= 4; j += 1) { 
     delay(1000); 
    }
}
