
//#include <Arduino.h>
#include <stdint.h>
#include "SCMD.h"
#include "SCMD_config.h" //Contains #defines for common SCMD register names and values
#include "Wire.h"
//#include <math.h>


////#defines
//#define MOTOR_MAX_RPM 73        // motor's maximum rpm
//#define WHEEL_DIAMETER 0.03      // robot's wheel diameter expressed in meters
//#define WHEEL_DISTANCE 0.1   // distance between front wheel and rear wheel
//#define PWM_BITS 32              // microcontroller's PWM pin resolution. Arduino Uno/Mega Teensy is using 8 bits(0-255)

 byte s1=1;
 byte s2=2;
 byte s3=3;
 int servos[3]={2,4,5};
 
struct motor {
  int drive1;
  int drive2;
  int inv1;
  int inv2;
} pwm;


int n=8;
int initial_angle[8];
int angle[8];
int c[8];

//Variables
//***** Create the Motor Driver object*****//
SCMD myMotorDriver1;    //config pattern "0101" on board for address 0x5A
SCMD myMotorDriver2;  //config pattern "0011" on board for address 0x58
SCMD myMotorDriver3;  //config pattern "0111" on board for address 0x5C
SCMD myMotorDriver4;    //config pattern "0100" on board for address 0x59
SCMD myMotorDriver5;  //config pattern "1001" on board for address 0x5E
SCMD myMotorDriver6;    //config pattern "1000" on board for address 0x5D
SCMD myMotorDriver7;    //config pattern "1100" on board for address 0x61
SCMD myMotorDriver8;    //config pattern "1010" on board for address 0x5F
//SCMD myMotorDriver9;    //config pattern "1011" on board for address 0x60
//SCMD myMotorDriver10; //config pattern "0110" on board for address 0x5B


void setup()
{
Wire.begin(); // join i2c bus (address optional for master)
  
//Serial.begin(9600); // Initialize Serial Monitor USB
SerialUSB.begin(9600); // Initialize hardware serial port, pins 0/1

while (!SerialUSB) ; // Wait for Serial monitor to open

//  Send a welcome message to the serial monitor:
  SerialUSB.println("Starting sketch.");
  
//  pinMode(8, INPUT_PULLUP);
//  digitalWrite(8, LOW);


  //***** Configure the Motor Driver's Settings *****//

  //  .commInter face can be I2C_MODE or SPI_MODE
  myMotorDriver1.settings.commInterface = I2C_MODE;
  myMotorDriver1.settings.I2CAddress = 0x5A; //config pattern "0101" on board for address 0x5A
  uint8_t tempReturnValue1 = myMotorDriver1.begin();
    SerialUSB.print("\n 1");
 while ( tempReturnValue1 != 0xA9){
      SerialUSB.print( "\n ID1 mismatch, read as 0x" );
    SerialUSB.println( tempReturnValue1, HEX );
  tempReturnValue1 = myMotorDriver1.begin();}
  delay(100);
  SerialUSB.print("\n Waiting for driver 1...");
  while ( myMotorDriver1.busy() ); //Waits until the SCMD is available.
  myMotorDriver1.inversionMode(1, 1); //invert motor 1
  myMotorDriver1.enable();  //Enable the motors.}
 delay(500);

//
  myMotorDriver2.settings.commInterface = I2C_MODE;
  myMotorDriver2.settings.I2CAddress = 0x58; //config pattern "0011" on board for address 0x58
  uint8_t tempReturnValue2 = myMotorDriver2.begin();
    SerialUSB.print("\n 2");
   while ( tempReturnValue2 != 0xA9){
          SerialUSB.print( "\n ID2 mismatch, read as 0x" );
    SerialUSB.println( tempReturnValue2, HEX );
  tempReturnValue2 = myMotorDriver2.begin();}
  delay(100);
  SerialUSB.print("\n Waiting for driver 2...");
  while ( myMotorDriver2.busy() ); //Waits until the SCMD is available.
  myMotorDriver2.inversionMode(1,1); //invert motor 1
  myMotorDriver2.inversionMode(0,1); //invert motor 1
  myMotorDriver2.enable();  //Enable the motors.}
delay(500);

    myMotorDriver3.settings.commInterface = I2C_MODE;
  myMotorDriver3.settings.I2CAddress = 0x5B; //config pattern "0111" on board for address 0x5C
  uint8_t tempReturnValue3 = myMotorDriver3.begin();
    SerialUSB.print("\n 3");
   while ( tempReturnValue3 != 0xA9){
           SerialUSB.print( "\n ID3 mismatch, read as 0x" );
    SerialUSB.println( tempReturnValue3, HEX );
  tempReturnValue3 = myMotorDriver3.begin();}
  delay(100);
    SerialUSB.print("\n Waiting for driver 3...");
  while ( myMotorDriver3.busy() ); //Waits until the SCMD is available.
  myMotorDriver3.inversionMode(1, 0); //invert motor 1
  myMotorDriver3.inversionMode(0, 1); //invert motor 1
  myMotorDriver3.enable();  //Enable the motors.}
delay(500);

    myMotorDriver4.settings.commInterface = I2C_MODE;
  myMotorDriver4.settings.I2CAddress = 0x59; //config pattern "0100" on board for address 0x59
  uint8_t tempReturnValue4 = myMotorDriver4.begin();
    SerialUSB.print("\n 4");
   while ( tempReturnValue4 != 0xA9){
       SerialUSB.print( "\n ID4 mismatch, read as 0x" );
   SerialUSB.println( tempReturnValue4, HEX );
   tempReturnValue4 = myMotorDriver4.begin();}
  delay(100);
    SerialUSB.print("\n Waiting for driver 4...");
  while ( myMotorDriver4.busy() ); //Waits until the SCMD is available.
  myMotorDriver4.inversionMode(0,1); //invert motor 1
  myMotorDriver4.inversionMode(1, 0); //invert motor 1
  myMotorDriver4.enable();  //Enable the motors.}
delay(500);

    myMotorDriver5.settings.commInterface = I2C_MODE;
  myMotorDriver5.settings.I2CAddress = 0x5E; //config pattern "1001" on board for address 0x5E
  uint8_t tempReturnValue5 = myMotorDriver5.begin();
    SerialUSB.print("\n 5");
   while ( tempReturnValue5 != 0xA9){
        SerialUSB.print( "\n ID5 mismatch, read as 0x" );
    SerialUSB.println( tempReturnValue5, HEX );
   tempReturnValue5 = myMotorDriver5.begin();}
  delay(100);
    SerialUSB.print("\n Waiting for driver 5...");
  while ( myMotorDriver5.busy() ); //Waits until the SCMD is available.
  myMotorDriver5.inversionMode(0, 0); //invert motor 1
  myMotorDriver5.inversionMode(1, 1); //invert motor 1
  myMotorDriver5.enable();  //Enable the motors.}
delay(500);

    myMotorDriver6.settings.commInterface = I2C_MODE;
  myMotorDriver6.settings.I2CAddress = 0x5D; //config pattern "1000" on board for address 0x5D
  uint8_t tempReturnValue6 = myMotorDriver6.begin();
    SerialUSB.print("\n 6");
      while ( tempReturnValue6 != 0xA9){
         SerialUSB.print( "\n ID6 mismatch, read as 0x" );
    SerialUSB.println( tempReturnValue6, HEX );
   tempReturnValue6 = myMotorDriver6.begin();}
  delay(100);
    SerialUSB.print("\n Waiting for driver 6...");
  while ( myMotorDriver6.busy() ); //Waits until the SCMD is available.
  myMotorDriver6.inversionMode(1, 1); //invert motor 1
  myMotorDriver6.enable();  //Enable the motors.}
delay(500);

    myMotorDriver7.settings.commInterface = I2C_MODE;
  myMotorDriver7.settings.I2CAddress = 0x60; //config pattern "1100" on board for address 0x61
  uint8_t tempReturnValue7 = myMotorDriver7.begin();
    SerialUSB.print("\n 7");
     while ( tempReturnValue7 != 0xA9){
    SerialUSB.print( "\n ID7 mismatch, read as 0x" );
    SerialUSB.println( tempReturnValue7, HEX );
   tempReturnValue7 = myMotorDriver7.begin();}
  delay(100);
  SerialUSB.print("\n Waiting for driver 7...");
  while ( myMotorDriver7.busy() ); //Waits until the SCMD is available.
  myMotorDriver7.inversionMode(1,0); //invert motor 1
  myMotorDriver7.inversionMode(0,0); //invert motor 2
  myMotorDriver7.enable();  //Enable the motors.}
delay(500);


    myMotorDriver8.settings.commInterface = I2C_MODE;
  myMotorDriver8.settings.I2CAddress = 0x5F; //config pattern "1010" on board for address 0x5F
  uint8_t tempReturnValue8 = myMotorDriver8.begin();
    SerialUSB.print("\n 8");
      while ( tempReturnValue8 != 0xA9){
    SerialUSB.print( "\n ID8 mismatch, read as 0x" );
    SerialUSB.println( tempReturnValue8, HEX );
   tempReturnValue8 = myMotorDriver8.begin();}
  delay(100);
    SerialUSB.print("\n Waiting for driver 8...");
  while ( myMotorDriver8.busy() ); //Waits until the SCMD is available.
  myMotorDriver8.inversionMode(1, 1); //invert motor 1
  myMotorDriver8.enable();  //Enable the motors.}
delay(500);


//    myMotorDriver9.settings.commInterface = I2C_MODE;
//  myMotorDriver9.settings.I2CAddress = 0x61; //config pattern "1011" on board for address 0x60
//  uint8_t tempReturnValue9 = myMotorDriver9.begin();
//    SerialUSB.print("\n 9");
//      while ( tempReturnValue9 != 0xA9){
//    SerialUSB.print( "\n ID9 mismatch, read as 0x" );
//    SerialUSB.println( tempReturnValue9, HEX );
//   tempReturnValue9 = myMotorDriver9.begin();}
//  delay(100);
//       SerialUSB.print("\n Waiting for driver 9...");
//  while (myMotorDriver9.busy()); //Waits until the SCMD is available.
//  myMotorDriver9.inversionMode(1, 1); //invert motor 1
//    myMotorDriver9.inversionMode(0, 1); //invert motor 1
//  myMotorDriver9.enable();  //Enable the motors.}
//delay(500);


//    myMotorDriver10.settings.commInterface = I2C_MODE;
//  myMotorDriver10.settings.I2CAddress = 0x5C; //config pattern "0110" on board for address 0x5B
//  uint8_t tempReturnValue10 = myMotorDriver10.begin();
//    SerialUSB.print("\n 10");
//      while ( tempReturnValue10 != 0xA9)
//  {      SerialUSB.print( "\n ID10 mismatch, read as 0x" );
//    SerialUSB.println( tempReturnValue10, HEX );
//  uint8_t tempReturnValue10 = myMotorDriver10.begin();}
//  delay(100);
//     SerialUSB.print("\n Waiting for driver 10...");
//  while ( myMotorDriver10.busy() ); //Waits until the SCMD is available.
//  myMotorDriver10.inversionMode(1, 1); //invert motor 1
//  myMotorDriver10.enable();  //Enable the motors.}
//delay(500);


//saving the initial configuration as the refference
for (int i=1;i<(n+1);i++){
  initial_angle[i]=pot(i);
}
delay(2000);
SerialUSB.print("\n Ready");
  }





void loop()
{

handleSerial();
//for(int i=1;i<(n+1);i++){
//
//  int sens=pot(i);
//  while(sens>520||sens<502){
//    SerialUSB.println("Robot");
//    SerialUSB.println(i);
//    SerialUSB.println("pot value:");
//    SerialUSB.println(sens);
//    SerialUSB.println("\n");
//    delay(100);
//  }
//}
}





int pot(int i) {
  int sensorvalue; 
  if (i==1){
  sensorvalue = analogRead(A0);
  delay(10);
  SerialUSB.print("\n Robot # ");
  SerialUSB.print(i);
  SerialUSB.print("\n Encoder value is: ");
  SerialUSB.print(sensorvalue);
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
  SerialUSB.print("\n Robot # ");
  SerialUSB.print(i);
  SerialUSB.print("\n Encoder value is: ");
  SerialUSB.print(sensorvalue);
  int result = Wire.endTransmission();
  delay(100);
  if(result)
  {
    SerialUSB.print("Unexpected endTransmission result: ");
    SerialUSB.println(result);
  }
  return sensorvalue;
  }
  else
  {
    SerialUSB.print("Unexpected number of bytes received: ");
    SerialUSB.println(available);
    int sensorvalue=512;
    delay(50);
      int result = Wire.endTransmission();
      delay(100);
  if(result)
  {
    SerialUSB.print("Unexpected endTransmission result: ");
    SerialUSB.println(result);
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
//               case 9 :
//      myMotorDriver9.setDrive( 0, m1_inv, m1_pwm);
//      myMotorDriver9.setDrive( 1, m2_inv, m2_pwm);
//         break;
//               case 10 :
//      myMotorDriver10.setDrive( 0, m1_inv, m1_pwm);
//      myMotorDriver10.setDrive( 1, m2_inv, m2_pwm);
//         break;

   } 
}


void getPWM2(int angle)
{
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
}




void handleSerial() {
  int a;
 if (SerialUSB.available() > 0) {
   a = SerialUSB.read()-48;
   delay(100);
 
   switch(a) {
         case 0:
     SerialUSB.println("\n Break");
ceas();
while(SerialUSB.available()==0)
{
}
      break;
      
     case 1:
     SerialUSB.println("\n Jamming..");
           jam();
while(SerialUSB.available()==0)
{
}
      break;

      case 2:
     SerialUSB.println("\n Unjaming..");
unjam();
while(SerialUSB.available()==0)
{
}
      break;

        case 3:
        SerialUSB.println("\n Jaming with motion..");
      jam();
      while(SerialUSB.available()==0)
{
  jaming_motion();
}
break;    
 
     case 4:
          SerialUSB.println("\n Demo");
          demo();
while(SerialUSB.available()==0){
demo();
  }
ceas();
      break;
      
     case 5:
     SerialUSB.println("\n Setting robots' rotation to 180 [deg]");
set2middle();
while(SerialUSB.available()==0)
{
}
      break;
  
    }
 }
 else
 {
  delay(100);
 }
 }


 
 void jaming_motion(){
set2int();
for (int j=1;j<=n;j++){
drive(j,10,1,10,1);
}
delay(100);
for (int j=1;j<=n;j++){
drive(j,0,1,0,1);
}
 }






 void demo(){
  for (int j = 1; j <=n; j++){
drive(j,100,1,100,1);
}
delay(100);
for (int i = 1; i <=n; i++){
drive(i,100,0,100,0);
}
delay(100);
 }




void ceas(){
           for (int j=1;j<=n;j++){
    drive(j,0,1,0,1);}
for (int i=1;i<4;i++){
      Wire.beginTransmission(servos[i]); // transmit to device #i
      Wire.write(s2);        // sends five bytes
      delay(100);
      Wire.endTransmission();// stop transmitting
      delay(500);
  }

}





void set2middle (){
  for (int i = 1; i < n+1; i++)
  {
angle[i]=pot(i)-512;
  }
  
  for (int j=1;j<=n;j++){
    drive(j,0,1,0,1);
    if (abs(angle[j])>50){
  getPWM2(angle[j]+512);
  drive(j,pwm.drive1,pwm.inv1,pwm.drive2,pwm.inv2);
    }
  }
}






 void set2int(){
  for (int i = 1; i < n+1; i++)
  {
angle[i]=pot(i)-initial_angle[i];
  }
  
  for (int j=1;j<=n;j++){
    drive(j,0,1,0,1);
    if (abs(angle[j])>50){
  getPWM2(angle[j]);
  drive(j,pwm.drive1,pwm.inv1,pwm.drive2,pwm.inv2);
    }
  }
 }





void unjam(){
  for (int i=1;i<4;i++){
      Wire.beginTransmission(servos[i]); // transmit to device #i
      Wire.write(s3);        // sends five bytes
      delay(100);
      Wire.endTransmission();// stop transmitting
      delay(500);
  }
}


void jam(){
  for (int i=1;i<4;i++){
      Wire.beginTransmission(servos[i]); // transmit to device #i
      Wire.write(s1);        // sends five bytes
      delay(100);
      Wire.endTransmission();// stop transmitting
      delay(500);
  }
}

