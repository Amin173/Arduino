#include <Wire.h>


int sensorValue = 0;  // variable to store the value coming from the senso

int sensorPin = A0;  // variable to store the value coming from the senso

#include <Servo.h>

Servo myservo;  // create servo object to control a servo



void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Wire.begin(4);                // join i2c bus with address #1
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveEvent); // register event  
//  SerialUSB.begin(9600); // Initialize Serial Monitor USB
  Serial.begin(9600); // Initialize hardware serial port, pins 0/1

//  while (!SerialUSB) ; // Wait for Serial monitor to open

//   Send a welcome message to the serial monitor:
//  SerialUSB.println("Slave04");
}

void loop() {
 
    // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
//  SerialUSB.println(sensorValue);             // debug value
  delay(100);
}


void requestEvent() {
//  uint8_t buffer[2];
//  buffer[0] = sensorValue >> 8;               \\shifting the binary code 8 bits to the right
//  buffer[1] = sensorValue & 0xff;             \\keeping only the first 8 bits of the binary code
//  Wire.write(buffer, 2);
//  int s=buffer[0]*256+buffer[1];
//  SerialUSB.println(s); // or LCD.print(s);
//  delay(100);
  byte SlaveSend = map(sensorValue,0,1023,0,127);    // Convert potvalue from (0 to 1023) to (0 to 127)
  Wire.write(SlaveSend);                          // sends one byte converted POT value to master
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()

void receiveEvent(int howMany) {
//  if (0 < Wire.available()) { 
    int c = Wire.read(); // receive byte as a character
//    SerialUSB.println(c);
      if (c==1){       //run the servo
          myservo.write(150);  }
      else if (c==2){      //stop the servo
        myservo.write(84);}
      else if (c==3){      //stop the servo
        myservo.write(0);}
//  }
  }

