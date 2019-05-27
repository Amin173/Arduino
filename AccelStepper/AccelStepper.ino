
/* This example shows how to use the AMIS-30543 stepper motor
driver with the AccelStepper library.
You will need to install the AccelStepper library for this
example to work.  Documentation and installation instructions for
the AccelStepper library are available here:
    http://www.airspayce.com/mikem/arduino/AccelStepper/
Before using this example, be sure to change the
setCurrentMilliamps line to have an appropriate current limit for
your system.  Also, see this library's documentation for
information about how to connect the driver:
    http://pololu.github.io/amis-30543-arduino/
*/

#include <SPI.h>
#include <AMIS30543.h>
#include <AccelStepper.h>

const uint8_t amisDirPin = 2;
const uint8_t amisStepPin = 3;
const uint8_t amisSlaveSelect = 4;

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int pos;

AMIS30543 stepper;
AccelStepper accelStepper(AccelStepper::DRIVER, amisStepPin, amisDirPin);

void setup()
{
//  Serial.begin(9600); // Initialize hardware serial port, pins 0/1
  SPI.begin();
  stepper.init(amisSlaveSelect);
  delay(1);

  stepper.resetSettings();
  stepper.setCurrentMilliamps(1200);
  stepper.setStepMode(32);
 

stepper.enableDriver();
accelStepper.setMaxSpeed(1000);
  accelStepper.setAcceleration(1000);
 
}
int posr=0;
void loop()
{
  
  sensorValue = analogRead(sensorPin);
//  Serial.print("\n Sensor value is: ");
//  Serial.print(sensorValue);
  pos=map(sensorValue,0,1023,0,15000);
//  Serial.print("\n Pos value is: ");
//  Serial.print(pos);
while(posr<pos+100){
  posr=posr+100;
  accelStepper.runToNewPosition(posr);
  delay(100);
}
while(posr>pos-100){
  posr=posr-100;
  accelStepper.runToNewPosition(posr);
  delay(100);
}

//  accelStepper.runToNewPosition(0);
//  delay(500);
//  accelStepper.runToNewPosition(10000);
//  delay(500);
}
