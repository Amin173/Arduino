

#include <Wire.h>


int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int servopin=4;        //use digital pin 4


void setup() {
  pinMode(servopin,OUTPUT);
  Wire.begin(2);                // join i2c bus with address #1
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveEvent); // register event  
//  SerialUSB.begin(9600); // Initialize Serial Monitor USB
  Serial.begin(9600); // Initialize hardware serial port, pins 0/1

//  while (!SerialUSB) ; // Wait for Serial monitor to open

  // Send a welcome message to the serial monitor:
//  SerialUSB.println("Slave01");
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
  byte SlaveSend = map(sensorValue,0,1023,0,127);    // Convert potvalue digital value (0 to 1023) to (0 to 127)
  Wire.write(SlaveSend);                          // sends one byte converted POT value to master
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()

void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
      if (c=='rs'){       //run the servo
        digitalWrite(servopin, HIGH);}
      if (c=='ss'){      //stop the servo
        digitalWrite(servopin, LOW);}
}
  }

