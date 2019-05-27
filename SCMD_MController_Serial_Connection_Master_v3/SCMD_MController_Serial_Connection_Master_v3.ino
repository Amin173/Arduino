//This example demonstrates some of the more advanced usage of the motor driver.
//It uses 3 motor drivers, with the master attached as SPI.  One slave is bridged,
//and the sketch test drives each motor. (There will be a break when the overtaken motor
//channel is activated.)

//This also shows how to count the number of connected slaves and report, as well as
//arbitrary register access.

//#include <Arduino.h>
#include <stdint.h>
#include "SCMD.h"
#include "SCMD_config.h" //Contains #defines for common SCMD register names and values
#include "Wire.h"
#include <math.h>
#include "Kinematics.h"


//#defines
#define MOTOR_MAX_RPM 73        // motor's maximum rpm
#define WHEEL_DIAMETER 0.03      // robot's wheel diameter expressed in meters
#define WHEEL_DISTANCE 0.1   // distance between front wheel and rear wheel
#define PWM_BITS 32              // microcontroller's PWM pin resolution. Arduino Uno/Mega Teensy is using 8 bits(0-255)

Kinematics kinematics(MOTOR_MAX_RPM, WHEEL_DIAMETER, WHEEL_DISTANCE, PWM_BITS);
//Variables
//***** Create the Motor Driver object*****//
SCMD myMotorDriver;




void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  
  SerialUSB.begin(9600); // Initialize Serial Monitor USB
  Serial1.begin(9600); // Initialize hardware serial port, pins 0/1

  while (!SerialUSB) ; // Wait for Serial monitor to open

//  Send a welcome message to the serial monitor:
  SerialUSB.println("Starting sketch.");
  pinMode(8, INPUT_PULLUP);
  //***** Configure the Motor Driver's Settings *****//

  //  .commInter face can be I2C_MODE or SPI_MODE
  myMotorDriver.settings.commInterface = I2C_MODE;
  //myMotorDriver.settings.commInterface = SPI_MODE;
  //  set address if I2C configuration selected with the config jumpers
  myMotorDriver.settings.I2CAddress = 0x5A; //config pattern "0101" on board for address 0x5A
  //  set chip select if SPI selected with the config jumpers
  myMotorDriver.settings.chipSelectPin = 10;
  delay(2500); //Give the serial driver time to check for slaves

  //  initialize the driver and enable the motor outputs
  uint8_t tempReturnValue = myMotorDriver.begin();

  while ( tempReturnValue != 0xA9 )
  {
    SerialUSB.print( "ID mismatch, read as 0x" );
    SerialUSB.println( tempReturnValue, HEX );
    delay(500);
    tempReturnValue = myMotorDriver.begin();
  }
  SerialUSB.println( "ID matches 0xA9" );

  SerialUSB.print("Waiting for enumeration...");
  while ( myMotorDriver.ready() == false );
  SerialUSB.println("Done.");

  //  Report number of slaves found
  uint8_t tempAddr = myMotorDriver.readRegister(SCMD_SLV_TOP_ADDR);
  if ( tempAddr >= START_SLAVE_ADDR )
  {
    SerialUSB.print("Detected ");
    SerialUSB.print(tempAddr - START_SLAVE_ADDR + 1); //Top address minus bottom address + 1 = number of slaves
    SerialUSB.println(" slaves.");
  }
  else
  {
    SerialUSB.println("No slaves detected");
  }

  while ( myMotorDriver.busy() ); //Waits until the SCMD is available.
  myMotorDriver.enable();  //Enable the motors.}

}






void loop()
{

  for (int i = 1; i < 3; i++)
  {

    //  conecting micro-controllers
    //  Wire.beginTransmission(1); // transmit to device #i
    //  Wire.write('rs');        // sends five bytes
    //  delay(10000)           // sends one byte
    //  Wire.write('ss');        // sends five bytes
    //  Wire.endTransmission();// stop transmitting

    

    
    // conecting SCMDs
    SerialUSB.println("\n Now running robot:");
    SerialUSB.println(i);
    int motor_num1 = 2 * (i - 1);
    int motor_num2 = 2 * i - 1;

    int sensorvalue=pot(i);
    int angle=pot(i)-512;
    int j=1;
    while (abs(angle)>50 && j<=10) {
      j++;
      SerialUSB.print("\n angle:");
      SerialUSB.print(abs(angle));
      Kinematics::output pwm;
      pwm = kinematics.getPWM2(sensorvalue);

      SerialUSB.print("\n LEFT MOTOR: ");
      // Assuming you have an encoder for each wheel, you can pass this RPM value to a PID controller
      // as a setpoint and your encoder data as a feedback.
      SerialUSB.print(pwm.motor1);

      SerialUSB.print(" RIGHT MOTOR: ");
      SerialUSB.print(pwm.motor2);

      myMotorDriver.setDrive( motor_num1, pwm.inversion1, pwm.motor1);
      myMotorDriver.setDrive( motor_num2, pwm.inversion2, pwm.motor2);
      delay(100);
      angle=pot(i)-512;
      SerialUSB.print("\n angle:");
      SerialUSB.print(abs(angle));
  }
    myMotorDriver.setDrive( motor_num1, 1, 0);
    myMotorDriver.setDrive( motor_num2, 1, 0);
    
      SerialUSB.print("\n LEFT MOTOR: ");
      // Assuming you have an encoder for each wheel, you can pass this RPM value to a PID controller
      // as a setpoint and your encoder data as a feedback.
      SerialUSB.print(0);

      SerialUSB.print(" RIGHT MOTOR: ");
      SerialUSB.print(0);
      SerialUSB.print("\n Next robot...");
      delay(100);
  
}
}







int pot(int i) {
  if (i==1){
  int sensorvalue = analogRead(A0);
  delay(100);
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
  int sensorvalue=map(MasterReceive,0,127,0,1023);
  delay(100);
  SerialUSB.print("\n Robot # ");
  SerialUSB.print(i);
  SerialUSB.print("\n Encoder value is: ");
  SerialUSB.print(sensorvalue);
  int result = Wire.endTransmission();
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
    delay(100);
      int result = Wire.endTransmission();
  if(result)
  {
    SerialUSB.print("Unexpected endTransmission result: ");
    SerialUSB.println(result);
  }
    return sensorvalue;
  }
  }
  
}

