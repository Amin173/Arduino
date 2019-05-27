//Arduino Pins
// Pin9 to Signal of ESC1
// Pin10 to Signal of ESC2
//Pin5 input
//Pin6 input

//Include Servo library.The Servo library supports up to 12 motors on most Arduino boards and 48 on the Arduino Mega. 
#include <Servo.h>
//Create servo objects to control the servo motors
Servo servoMotor1;
Servo servoMotor2;

//Define variables for the position of the servos
int posServo1 = 0;
int posServo2 = 0;
int throttle1;
int throttle2;

//Define a variable for the channel of the Receiver with which you want to control the servos, in this case channel2 (ailerons channel from my receiver)
int channel6;
int channel7;

//Attach each servo variable to a pin
void setup() { 
  servoMotor1.attach(9);   //Servo1 attached to pin 9
  servoMotor2.attach(10);  //Servo2 attached to pin 10
    //Define the input Pin for the Receiver
  pinMode(5, INPUT);
  pinMode(6,INPUT);
  Serial.begin(9600);     //Serial comunication for later monitoring of channel signal value
}

void loop() {

  
  //Read the pulse from Pin5&6 either HIGH or LOW
  channel6 = pulseIn(5, HIGH); //thrust input
  channel7 = pulseIn(6, HIGH); //stearing input

  
  //Monitor channel value
  Serial.print("Channel 5:");
  Serial.println(channel6);
  Serial.print("\t");
  Serial.print("Channel 6:");
  Serial.println(channel7);



 //Define a range of the channel value to center the servo when the stick of the transmiter is centered. This range can vary depending on which servos and Transmiter you are using. ESCs are off at 45 degrees.
if(channel7<1550&&channel7>=1450&&channel6<1130){
    posServo1 = 44;
    posServo2 = 44;
    servoMotor1.write(posServo1);
    servoMotor2.write(posServo2);
  }

else{
  if(channel7<1550&&channel7>=1450&&channel6>1130){
    throttle1 = channel6;
    throttle2 = channel6;
  }  

  
  else{
throttle1=channel6+channel7-1500;
throttle2=channel6-channel7+1500;
  if (throttle1>=1925){
    throttle1=1925;}
    if (throttle1<=1125){
      throttle1=1125;}
        if (throttle2>=1925){
    throttle2=1925;}
    if (throttle2<=1125){
      throttle2=1125;}
  }
throttle1=map(throttle1,1130,1925,45,180);
throttle2=map(throttle2,1130,1925,45,180);

  //If the channel value is bigger than the highest value of the range do following
  if(posServo1<=throttle1&&posServo2<=throttle2){
    while((posServo1 < throttle1)||(posServo2 < throttle2)){
      if ((posServo1 < throttle1)){
        posServo1 ++;
      servoMotor1.write(posServo1);
            delay(10);               //Time for servo2 to reach the value
      }

      if ((posServo2 < throttle2)){
      posServo2 ++;
      servoMotor2.write(posServo2);
           delay(10);            //Time for servo1 to reach the value 
      }

 if((posServo1 = throttle1)&&(posServo2 = throttle2)){
  servoMotor1.write(posServo1);
  delay(10);
  servoMotor2.write(posServo2);
break;
      }
    }
  }
  //If the channel value is smaller than the lowest value of the range do following
  if(posServo1>=throttle1&&posServo2>=throttle2){
    while((posServo1 > throttle1)||(posServo2 >throttle2)){
      if ((posServo1 > throttle1)){
        posServo1 --;
      servoMotor1.write(posServo1);
            delay(10);               //Time for servo2 to reach the value
      }

      if ((posServo2 > throttle2)){
      posServo2 --;
      servoMotor2.write(posServo2);
           delay(10);            //Time for servo1 to reach the value 
      }

      if((posServo1 = throttle1)&&(posServo2 = throttle2)){
        servoMotor1.write(posServo1);
        delay(10);
        servoMotor2.write(posServo2);
break;
      }
    }
    
  }

  if(posServo1>=throttle1&&posServo2<=throttle2){
    while((posServo1 > throttle1)||(posServo2 < throttle2)){
      if ((posServo1 > throttle1)){
        posServo1 --;
      servoMotor1.write(posServo1);
        delay(10);               //Time for servo2 to reach the value
      }
    
      if ((posServo2 < throttle2)){
      posServo2 ++;
      servoMotor2.write(posServo2);
        delay(10);            //Time for servo1 to reach the value 
      }
   
      if((posServo1 = throttle1)&&(posServo2 = throttle2)){
        servoMotor1.write(posServo1);
        delay(10);
        servoMotor2.write(posServo2);
break;
      }
    }
  }

    if(posServo1<=throttle1&&posServo2>=throttle2){
    while((posServo1 < throttle1)||(posServo2 >throttle2)){
      if ((posServo1 < throttle1)){
        posServo1 ++;
      servoMotor1.write(posServo1);
      delay(10);               //Time for servo2 to reach the value
      }
      
      if ((posServo2 > throttle2)){
      posServo2 --;
      servoMotor2.write(posServo2);
       delay(10);            //Time for servo1 to reach the value 
      }
    
      if((posServo1 = throttle1)&&(posServo2 = throttle2)){
        servoMotor1.write(posServo1);
        delay(10);
        servoMotor2.write(posServo2);
break;

      }
    }
  }

  }
//  delay(100);               //Time for Monitoring values
}

