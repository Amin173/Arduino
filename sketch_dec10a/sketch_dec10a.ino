//This example drives a robot in left and right arcs, driving in an overall wiggly course.
//  It demonstrates the variable control abilities. When used with a RedBot chassis,
//  each turn is about 90 degrees per drive.
//
//  Pin 8 can be grounded to disable motor movement, for debugging.

#include <Arduino.h>
#include <stdint.h>
#include "SCMD.h"
#include "SCMD_config.h" //Contains #defines for common SCMD register names and values
#include "Wire.h"

SCMD myMotorDriver; //This creates the main object of one motor driver and connected slaves.

void setup()
{
  pinMode(8, INPUT_PULLUP); //Use to halt motor movement (ground)

  Serial.begin(9600);
  Serial.println("Starting sketch.");

  //***** Configure the Motor Driver's Settings *****//
  //  .commInter face can be I2C_MODE or SPI_MODE
  myMotorDriver.settings.commInterface = I2C_MODE;
  //myMotorDriver.settings.commInterface = SPI_MODE;

  //  set address if I2C configuration selected with the config jumpers
  myMotorDriver.settings.I2CAddress = 0x5A; //config pattern "0101" on board for address 0x5A

  //  set chip select if SPI selected with the config jumpers
  myMotorDriver.settings.chipSelectPin = 10;

 //*****initialize the driver get wait for idle*****//
  while ( myMotorDriver.begin() != 0xA9 ) //Wait until a valid ID word is returned
  {
    Serial.println( "ID mismatch, trying again" );
    Serial.println( myMotorDriver.begin() );
    delay(500);
  }
  Serial.println( "ID matches 0xA9" );
    
    //Check the driver is done looking for slaves
    Serial.print("Looking for more slaves...");
    while ( myMotorDriver.ready() == false );
    Serial.println( "Done!" );
    Serial.println();

    //Inverting motor 1
    while ( myMotorDriver.busy());
    myMotorDriver.inversionMode(1,1);

    //Enable output driver hardware
    while ( myMotorDriver.busy ());
    myMotorDriver.enable();
}

#define LM 0
#define RM 1

void loop() {
  // setDrive takes a motor number, direction as 0 or 1 and level from 0 to 255
  myMotorDriver.setDrive( LM, 0, 0); //Stop motor
  myMotorDriver.setDrive( RM, 0, 0); //Stop motor
  while (digitalRead(8) == 0);
    for (int i=0; i<256; i++)
    {
      myMotorDriver.setDrive( LM,0,i); //Increase speed of left motor and back
      myMotorDriver.setDrive( RM, 0,20+(i/2));
      delay(5);
      }
     for (int i=255; i>=0; i--)
     {
      myMotorDriver.setDrive( LM, 0, i);
      myMotorDriver.setDrive( RM,0, 20+(i/2));
      delay(5);
      }
     for (int i=0; i<256; i++)
     {
      myMotorDriver.setDrive( LM, 0, 20+(i/2)); //Increase speed of right motor and back
      myMotorDriver.setDrive(RM, 0, i);
      delay(5);
      }
     for (int i=255; i>= 0; i--)
     {
      myMotorDriver.setDrive( LM,0,20+(i/2));
      myMotorDriver.setDrive( RM, 0, i);
      delay(5);
      } 
}
