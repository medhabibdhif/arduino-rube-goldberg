// rf95_mesh_address1.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple addressed, routed reliable messaging client
// with the RHMesh class.
// It is designed to work with the other examples rf95_mesh_address*
// Hint: you can simulate other network topologies by setting the 
// RH_TEST_NETWORK define in RHRouter.h
#include <SoftwareSerial.h>
#include <RH_RF95.h>
#include <RHMesh.h>
#include <Servo.h>


// Mesh has much greater memory requirements, and you may need to limit the
// max message length to prevent wierd crashes
#define RH_MESH_MAX_MESSAGE_LEN 50

// In this small artifical network of 4 nodes,

#define MESH1_ADDRESS 1
#define MESH2_ADDRESS 2
#define MESH3_ADDRESS 3
#define MESH4_ADDRESS 4
#define MESH5_ADDRESS 5
#define MESH6_ADDRESS 6
#define MESH7_ADDRESS 7
#define MESH8_ADDRESS 8
#define MESH9_ADDRESS 9

#define ctsPin 3 // Pin for capactitive touch sensor

// Singleton instance of the radio driver
SoftwareSerial ss(A5, A4);
RH_RF95 driver(ss);

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

// Class to manage message delivery and receipt, using the driver declared above
RHMesh manager(driver, MESH8_ADDRESS);
int isTurned = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(9, OUTPUT); //Sweep
  pinMode(ctsPin, INPUT); //Touch

  if (!manager.init())
    Serial.println("init failed");
  // Defaults after init are 434.0MHz, 0.05MHz AFC pull-in, modulation FSK_Rb2_4Fd36
}

uint8_t data[] = "we are 8";
uint8_t back[] = "And hello back to you from mesh 8";
// Dont put this on the stack:
uint8_t buf[RH_MESH_MAX_MESSAGE_LEN];

void loop()
{
    uint8_t len = sizeof(buf);
    uint8_t from;
      memset(buf, 0, len);
      if((manager.recvfromAck(buf, &len, &from)))
      {
          Serial.print("got message from : 0x");
          Serial.print(from, HEX);
          Serial.print(": ");
          if (strcmp("we are 7",(char*)buf)==0){
          Serial.println("we are recieving");           
            }
          Serial.println((char*)buf);
          
          // Send a reply back to the originator router
          if(manager.sendtoWait(back, sizeof(back), from) != RH_ROUTER_ERROR_NONE)
          Serial.println("sendtoWait failed");
          if (isTurned==0){
          turn();
          isTurned=1;
            }  
          else {
              Serial.println("already turned");// goes from 0 degrees to 180 degrees  
            }
            
          }
   /* if (isTouch()==1) {
    Serial.println("TOUCHED");    
    sendMessage('1',len,from);
    }
    else {
    Serial.println("not touched");  
    delay (500);  
    }*/  

          

}

    
/*    if(Serial.available())
    {
        addr = Serial.read();
    }
    
    if(addr > '0' && addr <= '9')
    {
        // Send a message to a mesh
        // It will be routed by the intermediate
        // nodes to the destination node, accorinding to the
        // routing tables in each node
        Serial.print("Send message to mesh ");
        Serial.println(addr - '0');
        if(manager.sendtoWait(data, sizeof(data), addr - '0') == RH_ROUTER_ERROR_NONE)
        {
            // It has been reliably delivered to the next node.
            // Now wait for a reply from the ultimate router
            memset(buf, 0, len);
            if(manager.recvfromAckTimeout(buf, &len, 3000, &from))
            {
                Serial.print("got reply from : 0x");
                Serial.print(from, HEX);
                Serial.print(": ");
                Serial.println((char*)buf);
            }
            else
            {
                Serial.println("No reply, are meshes running?");
            }
        }
        else Serial.println("sendtoWait failed. Are the intermediate meshes running?");

        addr = 0;     
    }*/

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

void sendMessage (char addr,uint8_t len,uint8_t from) {
  
        // Send a message to a mesh
        // It will be routed by the intermediate
        // nodes to the destination node, accorinding to the
        // routing tables in each node
        Serial.print("Send message to mesh ");
        Serial.println(addr - '0');
        if(manager.sendtoWait(data, sizeof(data), addr - '0') == RH_ROUTER_ERROR_NONE)
        {
            // It has been reliably delivered to the next node.
            // Now wait for a reply from the ultimate router
            memset(buf, 0, len);
            if(manager.recvfromAckTimeout(buf, &len, 3000, &from))
            {
                Serial.print("got reply from : 0x");
                Serial.print(from, HEX);
                Serial.print(": ");
                Serial.println((char*)buf);
            }
            else
            {
                Serial.println("No reply, are meshes running?");
            }
        }
        else Serial.println("sendtoWait failed. Are the intermediate meshes running?");
        addr = 0;     

    
}

void turn() {
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
