//This example demonstrates some of the more advanced usage of the motor driver.
//It uses 3 motor drivers, with the master attached as SPI.  One slave is bridged,
//and the sketch test drives each motor. (There will be a break when the overtaken motor
//channel is activated.)

//This also shows how to count the number of connected slaves and report, as well as
//arbitrary register access.

#include <Arduino.h>
#include <stdint.h>
#include "SCMD.h"
#include "SCMD_config.h" //Contains #defines for common SCMD register names and values
#include "Wire.h"
#include "Kinematics.h"

//#defines
#define MOTOR_MAX_RPM 73        // motor's maximum rpm
#define WHEEL_DIAMETER 0.03      // robot's wheel diameter expressed in meters
#define WHEEL_DISTANCE 0.1   // distance between front wheel and rear wheel
#define PWM_BITS 8              // microcontroller's PWM pin resolution. Arduino Uno/Mega Teensy is using 8 bits(0-255)

Kinematics kinematics(MOTOR_MAX_RPM, WHEEL_DIAMETER, WHEEL_DISTANCE, PWM_BITS);
//Variables
//***** Create the Motor Driver object*****//
SCMD myMotorDriver;

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  
  Serial.begin(9600);
  
  Serial.println("Starting sketch.");
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
    Serial.print( "ID mismatch, read as 0x" );
    Serial.println( tempReturnValue, HEX );
    delay(500);
    tempReturnValue = myMotorDriver.begin();
  }
  Serial.println( "ID matches 0xA9" );

  Serial.print("Waiting for enumeration...");
  while ( myMotorDriver.ready() == false );
  Serial.println("Done.");
  


  //  Report number of slaves found
  uint8_t tempAddr = myMotorDriver.readRegister(SCMD_SLV_TOP_ADDR);
  if ( tempAddr >= START_SLAVE_ADDR )
  {
    Serial.print("Detected ");
    Serial.print(tempAddr - START_SLAVE_ADDR + 1); //Top address minus bottom address + 1 = number of slaves
    Serial.println(" slaves.");
  }
  else
  {
    Serial.println("No slaves detected");
  }

  //Configure bridging modes
//  myMotorDriver.bridgingMode( 1, 1 ); //( DriverNum 1, bridged state = 1 )  This will bridge the first slave

  //Uncomment to set inversion

  //myMotorDriver.inversionMode(0, 1); //invert master, channel A
  //myMotorDriver.inversionMode(1, 1); //invert master, channel B
  //myMotorDriver.inversionMode(2, 1); //invert slave 1, channel A
  //no need to configure motor 3, this position does nothing because the slave is bridged.
  //myMotorDriver.inversionMode(4, 1); //invert slave 2, channel A
  //myMotorDriver.inversionMode(5, 1); //invert slave 2, channel B
  
   while ( myMotorDriver.busy() ); //Waits until the SCMD is available.
  //Enable the motors.
  myMotorDriver.enable();

}






byte x = 0;

void loop()
{
    
for(int i=1;i<5;i++)
{

//  conecting micro-controllers
//  Wire.beginTransmission(1); // transmit to device #i
//  Wire.write("x is ");        // sends five bytes
//  Wire.write(x);              // sends one byte
//  Wire.endTransmission();// stop transmitting

  Wire.requestFrom(1, 6);    // request 6 bytes from slave device #8

//  while (Wire.available()) { // slave may send less than requested
    int c = Wire.read(); // receive a byte as int
      Serial.println("");
   Serial.println("Sensor measurement is:");
  Serial.println(c);


//  x++;
  delay(100);



// conecting SCMDs 
Serial.println("Now running robot");
Serial.println(i);
    int motor_num1=2*(i-1);
    int motor_num2=2*i-1;

Kinematics::output pwm;

    //simulated required velocities
    float linear_vel_x = 1;  // 1 m/s
    float linear_vel_y = 1;  // 0 m/s
    float angular_vel_z = 0; // 1 m/s

    pwm = kinematics.getPWM(linear_vel_x, linear_vel_y, angular_vel_z);

    Serial.print("\n LEFT MOTOR: ");
    // Assuming you have an encoder for each wheel, you can pass this RPM value to a PID controller 
    // as a setpoint and your encoder data as a feedback.
    Serial.print(pwm.motor1);

    Serial.print(" RIGHT MOTOR: ");
    Serial.print(pwm.motor2);
   
    
    Serial.print("\n LEFT MOTOR: ");
    // Assuming you have an encoder for each wheel, you can pass this RPM value to a PID controller 
    // as a setpoint and your encoder data as a feedback.
    Serial.print(pwm.motor1);

    Serial.print(" RIGHT MOTOR: ");
    Serial.print(pwm.motor2);
    
    myMotorDriver.setDrive( motor_num1, 1, pwm.motor1);
    myMotorDriver.setDrive( motor_num2, 1, pwm.motor2);


//    // This is a simulated feedback from each motor. We'll just pass the calculated rpm above for demo's sake.
//    // In a live robot, these should be replaced with real RPM values derived from encoder.
//    int motor1_feedback = rpm.motor1; //in rpm
//    int motor2_feedback = rpm.motor2; //in rpm
//
//    Kinematics::velocities vel;
//
//    // Now given the RPM from each wheel, you can calculate the linear and angular velocity of the robot.
//    // This is useful if you want to create an odometry data (dead reckoning)
//    vel = kinematics.getVelocities(motor1_feedback, motor2_feedback);
//    Serial.print("\n VEL X: ");
//    Serial.print(vel.linear_x, 4);
//
//    Serial.print(" VEL_Y: ");
//    Serial.print(vel.linear_y, 4);
//
//    Serial.print(" ANGULAR_Z: ");
//    Serial.println(vel.angular_z, 4);
//    Serial.println("");
    delay(100);
    myMotorDriver.setDrive( motor_num1, 1, 0);
    myMotorDriver.setDrive( motor_num2, 1, 0);
//    delay(100);
}
}

