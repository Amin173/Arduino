
//#include <Arduino.h>
#include <stdint.h>
#include "SCMD.h"
#include "SCMD_config.h" //Contains #defines for common SCMD register names and values
#include "Wire.h"
#include <Servo.h>

Servo myservo;  // create servo object to control a servo


struct motor {
  int drive1;
  int drive2;
  int inv1;
  int inv2;
} pwm;

int initial_angle;
int angle;
int c;

//Variables
//***** Create the Motor Driver object*****//
SCMD myMotorDriver1;    //config pattern "0101" on board for address 0x5A
//SCMD myMotorDriver2;  //config pattern "0011" on board for address 0x58
//SCMD myMotorDriver3;  //config pattern "0111" on board for address 0x5C
//SCMD myMotorDriver4;    //config pattern "0100" on board for address 0x59
//SCMD myMotorDriver5;  //config pattern "1001" on board for address 0x5E
//SCMD myMotorDriver6;    //config pattern "1000" on board for address 0x5D
//SCMD myMotorDriver7;    //config pattern "1100" on board for address 0x61
//SCMD myMotorDriver8;    //config pattern "1010" on board for address 0x5F
//SCMD myMotorDriver9;    //config pattern "1011" on board for address 0x60
//SCMD myMotorDriver10; //config pattern "0110" on board for address 0x5B

int led1=10;
int led2=11;



void setup()
{
Wire.begin(); // join i2c bus (address optional for master)
  
//Serial.begin(9600); // Initialize Serial Monitor USB
SerialUSB.begin(9600); // Initialize hardware serial port, pins 0/1

while (!SerialUSB) ; // Wait for Serial monitor to open

//  Send a welcome message to the serial monitor:
  SerialUSB.println("Starting sketch.");
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  myservo.attach(9); 

  //***** Configure the Motor Driver's Settings *****//

  //  .commInter face can be I2C_MODE or SPI_MODE
digitalWrite(led1,HIGH);

  
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
 delay(200);

//
//  myMotorDriver2.settings.commInterface = I2C_MODE;
//  myMotorDriver2.settings.I2CAddress = 0x58; //config pattern "0011" on board for address 0x58
//  uint8_t tempReturnValue2 = myMotorDriver2.begin();
//    SerialUSB.print("\n 2");
//   while ( tempReturnValue2 != 0xA9){
//          SerialUSB.print( "\n ID2 mismatch, read as 0x" );
//    SerialUSB.println( tempReturnValue2, HEX );
//  tempReturnValue2 = myMotorDriver2.begin();}
//  delay(100);
//  SerialUSB.print("\n Waiting for driver 2...");
//  while ( myMotorDriver2.busy() ); //Waits until the SCMD is available.
//  myMotorDriver2.inversionMode(1,1); //invert motor 1
//  myMotorDriver2.inversionMode(0,1); //invert motor 1
//  myMotorDriver2.enable();  //Enable the motors.}
//delay(200);

//    myMotorDriver3.settings.commInterface = I2C_MODE;
//  myMotorDriver3.settings.I2CAddress = 0x5B; //config pattern "0111" on board for address 0x5C
//  uint8_t tempReturnValue3 = myMotorDriver3.begin();
//    SerialUSB.print("\n 3");
//   while ( tempReturnValue3 != 0xA9){
//           SerialUSB.print( "\n ID3 mismatch, read as 0x" );
//    SerialUSB.println( tempReturnValue3, HEX );
//  tempReturnValue3 = myMotorDriver3.begin();}
//  delay(100);
//    SerialUSB.print("\n Waiting for driver 3...");
//  while ( myMotorDriver3.busy() ); //Waits until the SCMD is available.
//  myMotorDriver3.inversionMode(1, 0); //invert motor 1
//  myMotorDriver3.inversionMode(0, 1); //invert motor 1
//  myMotorDriver3.enable();  //Enable the motors.}
//delay(200);

//    myMotorDriver4.settings.commInterface = I2C_MODE;
//  myMotorDriver4.settings.I2CAddress = 0x59; //config pattern "0100" on board for address 0x59
//  uint8_t tempReturnValue4 = myMotorDriver4.begin();
//    SerialUSB.print("\n 4");
//   while ( tempReturnValue4 != 0xA9){
//       SerialUSB.print( "\n ID4 mismatch, read as 0x" );
//   SerialUSB.println( tempReturnValue4, HEX );
//   tempReturnValue4 = myMotorDriver4.begin();}
//  delay(100);
//    SerialUSB.print("\n Waiting for driver 4...");
//  while ( myMotorDriver4.busy() ); //Waits until the SCMD is available.
//  myMotorDriver4.inversionMode(0,1); //invert motor 1
//  myMotorDriver4.inversionMode(1, 0); //invert motor 1
//  myMotorDriver4.enable();  //Enable the motors.}
//delay(200);
//
//    myMotorDriver5.settings.commInterface = I2C_MODE;
//  myMotorDriver5.settings.I2CAddress = 0x5E; //config pattern "1001" on board for address 0x5E
//  uint8_t tempReturnValue5 = myMotorDriver5.begin();
//    SerialUSB.print("\n 5");
//   while ( tempReturnValue5 != 0xA9){
//        SerialUSB.print( "\n ID5 mismatch, read as 0x" );
//    SerialUSB.println( tempReturnValue5, HEX );
//   tempReturnValue5 = myMotorDriver5.begin();}
//  delay(100);
//    SerialUSB.print("\n Waiting for driver 5...");
//  while ( myMotorDriver5.busy() ); //Waits until the SCMD is available.
//  myMotorDriver5.inversionMode(0, 0); //invert motor 1
//  myMotorDriver5.inversionMode(1, 1); //invert motor 1
//  myMotorDriver5.enable();  //Enable the motors.}
//delay(200);
//
//    myMotorDriver6.settings.commInterface = I2C_MODE;
//  myMotorDriver6.settings.I2CAddress = 0x5D; //config pattern "1000" on board for address 0x5D
//  uint8_t tempReturnValue6 = myMotorDriver6.begin();
//    SerialUSB.print("\n 6");
//      while ( tempReturnValue6 != 0xA9){
//         SerialUSB.print( "\n ID6 mismatch, read as 0x" );
//    SerialUSB.println( tempReturnValue6, HEX );
//   tempReturnValue6 = myMotorDriver6.begin();}
//  delay(100);
//    SerialUSB.print("\n Waiting for driver 6...");
//  while ( myMotorDriver6.busy() ); //Waits until the SCMD is available.
//  myMotorDriver6.inversionMode(1, 1); //invert motor 1
//  myMotorDriver6.enable();  //Enable the motors.}
//delay(200);

//    myMotorDriver7.settings.commInterface = I2C_MODE;
//  myMotorDriver7.settings.I2CAddress = 0x60; //config pattern "1011" on board for address 0x61
//  uint8_t tempReturnValue7 = myMotorDriver7.begin();
//    SerialUSB.print("\n 7");
//     while ( tempReturnValue7 != 0xA9){
//    SerialUSB.print( "\n ID7 mismatch, read as 0x" );
//    SerialUSB.println( tempReturnValue7, HEX );
//   tempReturnValue7 = myMotorDriver7.begin();}
//  delay(100);
//  SerialUSB.print("\n Waiting for driver 7...");
//  while ( myMotorDriver7.busy() ); //Waits until the SCMD is available.
//  myMotorDriver7.inversionMode(1,0); //invert motor 1
//  myMotorDriver7.inversionMode(0,0); //invert motor 2
//  myMotorDriver7.enable();  //Enable the motors.}
//delay(200);


//    myMotorDriver8.settings.commInterface = I2C_MODE;
//  myMotorDriver8.settings.I2CAddress = 0x5F; //config pattern "1010" on board for address 0x5F
//  uint8_t tempReturnValue8 = myMotorDriver8.begin();
//    SerialUSB.print("\n 8");
//      while ( tempReturnValue8 != 0xA9){
//    SerialUSB.print( "\n ID8 mismatch, read as 0x" );
//    SerialUSB.println( tempReturnValue8, HEX );
//   tempReturnValue8 = myMotorDriver8.begin();}
//  delay(100);
//    SerialUSB.print("\n Waiting for driver 8...");
//  while ( myMotorDriver8.busy() ); //Waits until the SCMD is available.
//  myMotorDriver8.inversionMode(1, 1); //invert motor 1
//  myMotorDriver8.enable();  //Enable the motors.}
//delay(200);


//  myMotorDriver9.settings.commInterface = I2C_MODE;
//  myMotorDriver9.settings.I2CAddress = 0x60; //config pattern "1011" on board for address 0x60
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
//delay(200);


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
//delay(200);


//saving the initial configuration as the refference
initial_angle=pot();

delay(500);
SerialUSB.print("\n Ready");
digitalWrite(led1,LOW);
digitalWrite(led2,HIGH);

  }





void loop()
{

  handleSerial();

}





int pot() {
  int sensorvalue; 
  sensorvalue = analogRead(A0);
  delay(10);
  return sensorvalue;
}



void drive(int m1_pwm,int m1_inv,int m2_pwm,int m2_inv){
    
      myMotorDriver1.setDrive( 0, m1_inv, m1_pwm);
      myMotorDriver1.setDrive( 1, m2_inv, m2_pwm);

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
  int a=0;
 if (SerialUSB.available() > 0) {
   a = SerialUSB.read()-48;
   delay(100);}
 if (a==1||a==2||a==3||a==4||a==5||a==6||a==7){
   switch(a) {
     case 1:
     SerialUSB.println("\n Jamming..");
           jam();
      break;

 
     case 2:
          SerialUSB.println("\n Demo");
          demo();

      break;
      
           case 3:
     SerialUSB.println("\n Setting robots' rotation to 180 [deg]");
set2middle();
      break;
      
     case 4:
     SerialUSB.println("\n Break");
ceas();
delay(200);
ceas_jam();
      break;
      
      case 5:
      SerialUSB.println("\n Unjaming");
      unjam();
      break;
      
      case 6:{
      SerialUSB.println("\n Jaming with motion");
      jaming_motion();
      delay(2000);
      jam();
break;}

      case 7:{
      SerialUSB.println("\n Unjaming with motion");
      unjaming_motion();
      delay(2000);
unjam();

break;}

      case 8:
      SerialUSB.println("\n Stoped jaming");
ceas_jam();
          break;
   }
 }
 
 else
 {
 }
 
}




 void demo(){
  for (int i=1;i<3;i++){
drive(100,1,100,1);
delay(1000);
drive(100,0,100,0);
delay(1000);
  }
  drive(0,0,0,0);

 }



void ceas(){
    drive(0,1,0,1);
}


void set2middle (){

angle=pot()-512;

    drive(0,1,0,1);
    while (abs(angle)>10){
digitalWrite(led2,LOW);
delay(100);
digitalWrite(led2,HIGH);
delay(100);
    SerialUSB.print(angle+512);
    SerialUSB.print("\n");

  getPWM2(angle+512);
  drive(pwm.drive1,pwm.inv1,pwm.drive2,pwm.inv2);
    angle=pot()-512;
    }
    SerialUSB.print("Sensor Value is: ");
    SerialUSB.print(angle+512);


  }


 void jaming_motion(){

angle=pot()-initial_angle;
  
  

    drive(100,1,100,1);
    if (abs(angle)>50){
  getPWM2(angle);
  drive(pwm.drive1,pwm.inv1,pwm.drive2,pwm.inv2);
    }
  }

 void unjaming_motion(){

angle=pot()-initial_angle;

    drive(100,0,100,0);
    if (abs(angle)>50){
  getPWM2(angle);
  drive(pwm.drive1,pwm.inv1,pwm.drive2,pwm.inv2);
    }
  }





void unjam(){
myservo.write(0); 
}


void jam(){
myservo.write(150); 
}

void ceas_jam(){
myservo.write(84); 
}




//void jam_with_motion(){
// jaming_motion();
// delay(500);
// jam();
// delay(200);
// set2int();
//
//}
//
//void unjam_with_motion(){
//  set2int();
// unjaming_motion();
// delay(500);
// unjam();
// delay(100);
//}
