/* This example shows basic use of the AMIS-30543 stepper motor
driver.
It shows how to initialize the driver, set the current limit, set
the micro-stepping mode, and enable the driver.  It shows how to
send pulses to the NXT/STEP pin to get the driver to take steps
and how to switch directions using the DIR pin.  The DO pin is
not used and does not need to be connected.
Before using this example, be sure to change the
setCurrentMilliamps line to have an appropriate current limit for
your system.  Also, see this library's documentation for
information about how to connect the driver:
    http://pololu.github.io/amis-30543-arduino/
*/

#include <SPI.h>
#include <AMIS30543.h>

const uint8_t amisDirPin = 2;
const uint8_t amisStepPin = 3;
const uint8_t amisSlaveSelect = 4;
int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue0;  // variable to store the value coming from the sensor
int sensorValue;  // variable to store the value coming from the sensor

AMIS30543 stepper;

void setup()
{
//  Serial1.begin(9600);
//   // while the serial stream is not open, do nothing:
//   while (!Serial) ;

  SPI.begin();
  stepper.init(amisSlaveSelect);

  // Drive the NXT/STEP and DIR pins low initially.
  digitalWrite(amisStepPin, LOW);
  pinMode(amisStepPin, OUTPUT);
  digitalWrite(amisDirPin, LOW);
  pinMode(amisDirPin, OUTPUT);

  // Give the driver some time to power up.
  delay(100);

  // Reset the driver to its default settings.
  stepper.resetSettings();

  // Set the current limit.  You should change the number here to
  // an appropriate value for your particular system.
  stepper.setCurrentMilliamps(1200);

  // Set the number of microsteps that correspond to one full step.
  stepper.setStepMode(32);

  // Enable the motor outputs.
  stepper.enableDriver();
  sensorValue0 = analogRead(sensorPin);
}



int pos=0;
void loop()
{
  sensorValue = analogRead(sensorPin);
//  Serial.println(sensorValue);
  // Step in the default direction 1000 times.
  pos=sensorValue-sensorValue0;
  if(pos>=0){
    setDirection(0);}
  if(pos<0){
    setDirection(1);}

//  pos=map(pos,0,1023,0,10000);
  while (abs(pos)>100){
    sensorValue = analogRead(sensorPin);
    pos=sensorValue-sensorValue0;
    step();
  }

}


// Sends a pulse on the NXT/STEP pin to tell the driver to take
// one step, and also delays to control the speed of the motor.
void step()
{
  // The NXT/STEP minimum high pulse width is 2 microseconds.
  digitalWrite(amisStepPin, HIGH);
  delayMicroseconds(3);
  digitalWrite(amisStepPin, LOW);
  delayMicroseconds(3);

  // The delay here controls the stepper motor's speed.  You can
  // increase the delay to make the stepper motor go slower.  If
  // you decrease the delay, the stepper motor will go fast, but
  // there is a limit to how fast it can go before it starts
  // missing steps.
  delayMicroseconds(200);
}

// Writes a high or low value to the direction pin to specify
// what direction to turn the motor.
void setDirection(bool dir)
{
  // The NXT/STEP pin must not change for at least 0.5
  // microseconds before and after changing the DIR pin.
  delayMicroseconds(1);
  digitalWrite(amisDirPin, dir);
  delayMicroseconds(1);
}
