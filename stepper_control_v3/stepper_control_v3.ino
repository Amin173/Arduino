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

SerialUSB.begin(9600);
while(!SerialUSB);
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
  stepper.setCurrentMilliamps(1500);

  // Set the number of microsteps that correspond to one full step.
  stepper.setStepMode(32);

  // Enable the motor outputs.
  stepper.enableDriver();
  sensorValue0 = analogRead(sensorPin);
  SerialUSB.println("\n +: one forward increament");
  SerialUSB.println("\n -: one backward increament");
  SerialUSB.println("\n 0: reset zero point");
  SerialUSB.println("\n g0: go to zero point");
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
while (abs(pos)>50)
{
//  pos=map(pos,0,1023,0,10000);
    sensorValue = analogRead(sensorPin);
    pos=sensorValue-sensorValue0;
    
    step(abs(pos)-50);
}
if (SerialUSB.available()){
handleserial();}

}



int c;
void handleserial(){

    while (SerialUSB.available()>0){
        // get the new byte:
    c = Serial.read()-48;}
    delay(100);
    SerialUSB.println(c);
    int sensorvalue=analogRead(sensorPin);
    switch(c){

      case 1:
      SerialUSB.println("\n Forward increament");
      setDirection(1); 
      step(5);
      sensorvalue=sensorvalue+5;
      break;

      
      case 2:
      SerialUSB.println("\n Backward increament");
      setDirection(0);
      step(5);
      sensorvalue=sensorvalue-5;
      break;

      
      case 3:
      SerialUSB.println("\n set zero point");
      sensorValue0=analogRead(sensorPin);
      break;

      
      case 4:
      SerialUSB.println("\n go to zero point");
      pos=sensorValue-sensorValue0;
  if(pos>=0){
    setDirection(0);}
  if(pos<0){
    setDirection(1);}
while (abs(pos)>50)
{
    sensorValue = analogRead(sensorPin);
    pos=sensorValue-sensorValue0;
    
    step(abs(pos)-50);
    break;

    case ' ':
digitalWrite(amisStepPin, LOW);
break;
    }
  }

}




// Sends a pulse on the NXT/STEP pin to tell the driver to take
// one step, and also delays to control the speed of the motor.
void step(int i)
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
  
  int j=setDelay(i);
  delayMicroseconds(j);
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

int setDelay(int i)
{

int j=1000*(i<50)+400*(i>=50&i<100)+150*(i>=100&i<200)+50*(i>=200&i<400)+1*(i>=400);
//  SerialUSB.println("\n Delay: ");
//  SerialUSB.println(j);
  return j;
}

