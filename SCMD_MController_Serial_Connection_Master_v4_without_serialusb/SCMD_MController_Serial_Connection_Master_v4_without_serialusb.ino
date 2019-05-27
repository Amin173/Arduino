
//#include <Arduino.h>
#include <stdint.h>
#include "SCMD.h"
#include "SCMD_config.h" //Contains #defines for common SCMD register names and values
#include "Wire.h"
#include <math.h>


//#defines
#define MOTOR_MAX_RPM 73        // motor's maximum rpm
#define WHEEL_DIAMETER 0.03      // robot's wheel diameter expressed in meters
#define WHEEL_DISTANCE 0.1   // distance between front wheel and rear wheel
#define PWM_BITS 32              // microcontroller's PWM pin resolution. Arduino Uno/Mega Teensy is using 8 bits(0-255)

struct motor {
  int drive1;
  int drive2;
  int inv1;
  int inv2;
} pwm;


int n=9;
int initial_angle[9];
int angle[9];
int c[9];

//Variables
//***** Create the Motor Driver object*****//
SCMD myMotorDriver1;
SCMD myMotorDriver2;
SCMD myMotorDriver3;
SCMD myMotorDriver4;
SCMD myMotorDriver5;
SCMD myMotorDriver6;
SCMD myMotorDriver7;
SCMD myMotorDriver8;
SCMD myMotorDriver9;
//SCMD myMotorDriver10;


void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  
  Serial.begin(9600); // Initialize Serial Monitor USB
//  Serial1.begin(9600); // Initialize hardware serial port, pins 0/1

//  while (!Serial) ; // Wait for Serial monitor to open

//  Send a welcome message to the serial monitor:
//  Serial.println("Starting sketch.");
  pinMode(8, INPUT_PULLUP);
  //***** Configure the Motor Driver's Settings *****//

  //  .commInter face can be I2C_MODE or SPI_MODE
  myMotorDriver1.settings.commInterface = I2C_MODE;
  myMotorDriver2.settings.commInterface = I2C_MODE;
  myMotorDriver3.settings.commInterface = I2C_MODE;
  myMotorDriver4.settings.commInterface = I2C_MODE;
  myMotorDriver5.settings.commInterface = I2C_MODE;
  myMotorDriver6.settings.commInterface = I2C_MODE;
  myMotorDriver7.settings.commInterface = I2C_MODE;
  myMotorDriver8.settings.commInterface = I2C_MODE;
  myMotorDriver9.settings.commInterface = I2C_MODE;
//  myMotorDriver10.settings.commInterface = I2C_MODE;

  //  set address if I2C configuration selected with the config jumpers
  myMotorDriver1.settings.I2CAddress = 0x5A; //config pattern "0011" on board for address 0x5A
  myMotorDriver2.settings.I2CAddress = 0x58; //config pattern "0101" on board for address 0x5A
  myMotorDriver3.settings.I2CAddress = 0x5C; //config pattern "0111" on board for address 0x5A
  myMotorDriver4.settings.I2CAddress = 0x59; //config pattern "0100" on board for address 0x5A
  myMotorDriver5.settings.I2CAddress = 0x5E; //config pattern "0111" on board for address 0x5A
  myMotorDriver6.settings.I2CAddress = 0x5D; //config pattern "0111" on board for address 0x5A
  myMotorDriver7.settings.I2CAddress = 0x61; //config pattern "0111" on board for address 0x5A
  myMotorDriver8.settings.I2CAddress = 0x5F; //config pattern "0111" on board for address 0x5A
  myMotorDriver9.settings.I2CAddress = 0x60; //config pattern "0111" on board for address 0x5A
//  myMotorDriver10.settings.I2CAddress = 0x5C; //config pattern "0111" on board for address 0x5A
  //  set chip select if SPI selected with the config jumpers
//  myMotorDriver1.settings.chipSelectPin = 10;
//  myMotorDriver2.settings.chipSelectPin = 10;
//  delay(2500); //Give the serial driver time to check for slaves

  //  initialize the driver and enable the motor outputs
  uint8_t tempReturnValue1 = myMotorDriver1.begin();
  uint8_t tempReturnValue2 = myMotorDriver2.begin();
  uint8_t tempReturnValue3 = myMotorDriver3.begin();
  uint8_t tempReturnValue4 = myMotorDriver4.begin();
  uint8_t tempReturnValue5 = myMotorDriver5.begin();
  uint8_t tempReturnValue6 = myMotorDriver6.begin();
  uint8_t tempReturnValue7 = myMotorDriver7.begin();
  uint8_t tempReturnValue8 = myMotorDriver8.begin();
  uint8_t tempReturnValue9 = myMotorDriver9.begin();
//  uint8_t tempReturnValue10 = myMotorDriver10.begin();
 while ( tempReturnValue1 != 0xA9){
//  {    SerialUSB.print( "ID1 mismatch, read as 0x" );
//    SerialUSB.println( tempReturnValue1, HEX );
  tempReturnValue1 = myMotorDriver1.begin();}
//
   while ( tempReturnValue2 != 0xA9){
//          SerialUSB.print( "\n ID2 mismatch, read as 0x" );
//    SerialUSB.println( tempReturnValue2, HEX );
  tempReturnValue2 = myMotorDriver2.begin();}

   while ( tempReturnValue3 != 0xA9){
//           SerialUSB.print( "\n ID3 mismatch, read as 0x" );
//    SerialUSB.println( tempReturnValue3, HEX );
  tempReturnValue3 = myMotorDriver3.begin();}
  
   while ( tempReturnValue4 != 0xA9){
//       SerialUSB.print( "\n ID4 mismatch, read as 0x" );
//   SerialUSB.println( tempReturnValue4, HEX );
   tempReturnValue4 = myMotorDriver4.begin();}

   while ( tempReturnValue5 != 0xA9){
//        SerialUSB.print( "\n ID5 mismatch, read as 0x" );
//    SerialUSB.println( tempReturnValue5, HEX );
   tempReturnValue5 = myMotorDriver5.begin();}

      while ( tempReturnValue6 != 0xA9){
//         SerialUSB.print( "\n ID6 mismatch, read as 0x" );
//    SerialUSB.println( tempReturnValue6, HEX );
   tempReturnValue6 = myMotorDriver6.begin();}

      while ( tempReturnValue7 != 0xA9){
//    SerialUSB.print( "\n ID7 mismatch, read as 0x" );
//    SerialUSB.println( tempReturnValue7, HEX );
   tempReturnValue7 = myMotorDriver7.begin();}

      while ( tempReturnValue8 != 0xA9){
//    SerialUSB.print( "\n ID8 mismatch, read as 0x" );
//    SerialUSB.println( tempReturnValue8, HEX );
   tempReturnValue8 = myMotorDriver8.begin();}

      while ( tempReturnValue9 != 0xA9){
//    SerialUSB.print( "\n ID9 mismatch, read as 0x" );
//    SerialUSB.println( tempReturnValue9, HEX );
   tempReturnValue9 = myMotorDriver9.begin();}


//      while ( tempReturnValue3 != 0xA9)
//  {      SerialUSB.print( "\n ID10 mismatch, read as 0x" );
//    SerialUSB.println( tempReturnValue10, HEX );
//  uint8_t tempReturnValue10 = myMotorDriver10.begin();}



  delay(500);
  
//  SerialUSB.println( "\n IDs matche 0xA9" );

//  SerialUSB.print("Waiting for enumeration...");
//  while ( myMotorDriver1.ready() == false );
//  while ( myMotorDriver2.ready() == false );
//  SerialUSB.println("Done.");

//  //  Report number of slaves found
//  uint8_t tempAddr1 = myMotorDriver1.readRegister(SCMD_SLV_TOP_ADDR);
//  uint8_t tempAddr2 = myMotorDriver2.readRegister(SCMD_SLV_TOP_ADDR);

//  if ( tempAddr >= START_SLAVE_ADDR )
//  {
//    SerialUSB.print("Detected ");
//    SerialUSB.print(tempAddr - START_SLAVE_ADDR + 1); //Top address minus bottom address + 1 = number of slaves
//    SerialUSB.println(" slaves.");
//  }
//  else
//  {
//    SerialUSB.println("No slaves detected");
//  }

//   SerialUSB.print("\n Waiting for driver 1...");
  while ( myMotorDriver1.busy() ); //Waits until the SCMD is available.
  myMotorDriver1.inversionMode(1, 1); //invert motor 1
  
//  SerialUSB.print("\n Waiting for driver 2...");
  while ( myMotorDriver2.busy() ); //Waits until the SCMD is available.
  myMotorDriver2.inversionMode(1,1); //invert motor 1
  myMotorDriver2.inversionMode(0,1); //invert motor 1
//  
//    SerialUSB.print("\n Waiting for driver 3...");
  while ( myMotorDriver3.busy() ); //Waits until the SCMD is available.
  myMotorDriver3.inversionMode(1, 1); //invert motor 1

//    SerialUSB.print("\n Waiting for driver 4...");
  while ( myMotorDriver4.busy() ); //Waits until the SCMD is available.
  myMotorDriver4.inversionMode(0,1); //invert motor 1
  myMotorDriver4.inversionMode(1, 0); //invert motor 1
//    SerialUSB.print("\n Waiting for driver 5...");
  while ( myMotorDriver5.busy() ); //Waits until the SCMD is available.
  myMotorDriver5.inversionMode(0, 1); //invert motor 1
//    SerialUSB.print("\n Waiting for driver 6...");
  while ( myMotorDriver6.busy() ); //Waits until the SCMD is available.
  myMotorDriver6.inversionMode(1, 1); //invert motor 1
//    SerialUSB.print("\n Waiting for driver 7...");
  while ( myMotorDriver7.busy() ); //Waits until the SCMD is available.
  myMotorDriver7.inversionMode(1,0); //invert motor 1
  myMotorDriver7.inversionMode(0,0); //invert motor 1
//    SerialUSB.print("\n Waiting for driver 8...");
  while ( myMotorDriver8.busy() ); //Waits until the SCMD is available.
  myMotorDriver8.inversionMode(1, 1); //invert motor 1
//    SerialUSB.print("\n Waiting for driver 9...");
  while (myMotorDriver9.busy()); //Waits until the SCMD is available.
  myMotorDriver9.inversionMode(1, 1); //invert motor 1
    myMotorDriver9.inversionMode(0, 1); //invert motor 1
//     SerialUSB.print("\n Waiting for driver 10...");
//  while ( myMotorDriver10.busy() ); //Waits until the SCMD is available.
//  myMotorDriver10.inversionMode(1, 1); //invert motor 1

//  SerialUSB.print("\n Done");
  myMotorDriver1.enable();  //Enable the motors.}
  myMotorDriver2.enable();  
  myMotorDriver3.enable();  
  myMotorDriver4.enable();  
  myMotorDriver5.enable();  
  myMotorDriver6.enable();  
  myMotorDriver7.enable();  
  myMotorDriver8.enable();  
  myMotorDriver9.enable();  
//  myMotorDriver10.enable();  

//saving the initial configuration as the refference
for (int i=1;i<(n+1);i++){
  initial_angle[i]=pot(i);
}
  }





void loop()
{

  
  }
//        delay(500);
//for (int i=1;i<n+1;i++){
//    drive(i,0,1,0,1);
//}
}





int pot(int i) {
  int sensorvalue; 
  if (i==1){
  sensorvalue = analogRead(A0);
  delay(10);
//  SerialUSB.print("\n Robot # ");
//  SerialUSB.print(i);
//  SerialUSB.print("\n Encoder value is: ");
//  SerialUSB.print(sensorvalue);
  return sensorvalue;
  }
  else{
   // Request data from slave.
  Wire.beginTransmission(i);
  int available = Wire.requestFrom(i,1);
    if(available == 1)
  {
  byte MasterReceive = Wire.read();                // receive a byte from the slave arduino and store in MasterReceive
  sensorvalue=map(MasterReceive,0,127,0,1023);
  delay(50);
//  SerialUSB.print("\n Robot # ");
//  SerialUSB.print(i);
//  SerialUSB.print("\n Encoder value is: ");
//  SerialUSB.print(sensorvalue);
  int result = Wire.endTransmission();
  if(result)
  {
//    SerialUSB.print("Unexpected endTransmission result: ");
//    SerialUSB.println(result);
  }
  return sensorvalue;
  }
  else
  {
//    SerialUSB.print("Unexpected number of bytes received: ");
//    SerialUSB.println(available);
    int sensorvalue=512;
//    delay(50);
      int result = Wire.endTransmission();
  if(result)
  {
//    SerialUSB.print("Unexpected endTransmission result: ");
//    SerialUSB.println(result);
  }
    return sensorvalue;
  }
  }
}


void drive(int i,int m1_pwm,int m1_inv,int m2_pwm,int m2_inv){
//  int MotorNumber;
  switch(i) {
      case 1 :
      myMotorDriver1.setDrive( 0, m1_inv, m1_pwm);
      myMotorDriver1.setDrive( 1, m2_inv, m2_pwm);
         break;
      case 2 :
      myMotorDriver2.setDrive( 0, m1_inv, m1_pwm);
      myMotorDriver2.setDrive( 1, m2_inv, m2_pwm);
         break;
               case 3:
      myMotorDriver3.setDrive( 0, m1_inv, m1_pwm);
      myMotorDriver3.setDrive( 1, m2_inv, m2_pwm);
         break;
               case 4 :
      myMotorDriver4.setDrive( 0, m1_inv, m1_pwm);
      myMotorDriver4.setDrive( 1, m2_inv, m2_pwm);
         break;
               case 5 :
      myMotorDriver5.setDrive( 0, m1_inv, m1_pwm);
      myMotorDriver5.setDrive( 1, m2_inv, m2_pwm);
         break;
               case 6 :
      myMotorDriver6.setDrive( 0, m1_inv, m1_pwm);
      myMotorDriver6.setDrive( 1, m2_inv, m2_pwm);
         break;
               case 7 :
      myMotorDriver7.setDrive( 0, m1_inv, m1_pwm);
      myMotorDriver7.setDrive( 1, m2_inv, m2_pwm);
         break;
               case 8 :
      myMotorDriver8.setDrive( 0, m1_inv, m1_pwm);
      myMotorDriver8.setDrive( 1, m2_inv, m2_pwm);
         break;
               case 9 :
      myMotorDriver9.setDrive( 0, m1_inv, m1_pwm);
      myMotorDriver9.setDrive( 1, m2_inv, m2_pwm);
         break;
//               case 10 :
//      myMotorDriver10.setDrive( 0, m1_inv, m1_pwm);
//      myMotorDriver10.setDrive( 1, m2_inv, m2_pwm);
//         break;

   } 
}

void getPWM2(int sensorvalue)
{
int angle=sensorvalue-500;
if (abs(angle)>50){
  //front-left motor
  pwm.drive1 = 100;
  //rear-left motor
  pwm.drive2 = 100;
  if (angle>0){
  pwm.inv1= 0;
  pwm.inv2= 1;
    
  }
  if (angle<0){
  pwm.inv1= 1;
  pwm.inv2= 0;
  }
}
else {
  
  pwm.drive1= 0;
  pwm.drive2= 1;
  pwm.inv1= 1;
  pwm.inv2= 0;
}
//return pwm;
}


void handleSerial() {
 while (Serial.available() > 0) {
   char incomingCharacter = serial.read();
   switch (incomingCharacter) {
     case ‘j’:
     while(Serial.available()==0){
      pwmValue = pwmValue + 5;
      If (pwmValue >= pwmMax)
         pwmValue = pwmMax;
     }
      break;
 
     case ‘d’:
      while(Serial.available()==0){
      pwmValue = pwmValue + 5;
      If (pwmValue >= pwmMax)
         pwmValue = pwmMax;
     }
      break;
    }
 }
}
