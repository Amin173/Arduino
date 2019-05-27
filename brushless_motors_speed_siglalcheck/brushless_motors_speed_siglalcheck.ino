//#include <Servo.h>
//
//Servo esc1;
//Servo esc2;
//int throttlePin = 0;
//int stearpin = 1;
//int stear1;
//int stear2;
//int minPulseRate = 1000;
//int maxPulseRate = 2000;
//int throttleChangeDelay = 100;
//
//void setup()
//{
//  Serial.begin(9600);
//  // Attach the the servo to the correct pin and set the pulse range
//  esc1.attach(9,minPulseRate,maxPulseRate);
//  esc2.attach(10,minPulseRate,maxPulseRate);
////  // Write a minimum value (most ESCs require this correct startup)
//  esc1.write(0);
//  esc2.write(0);
//}
//
//void loop()
//{
////  if (Serial.available() > 0) {
//    int throttle = analogRead(throttlePin);
//    throttle = map(throttle, 0, 1023, 0, 180);
//    //esc.write(throttle);
//    int stear = analogRead(stearpin);
//    stear1 = map(stear, 0, 1023, 0, 180) - 90;
//    stear2 = 90 - stear1;
////    if (abs(stear1) > 10 && (abs(stear1) + throttle) > 135) {
////      throttle = throttle - 45;
////    }
//     esc1.write(stear1 + throttle);
//     esc2.write(stear2 + throttle);
////    changeThrottle(stear1 + throttle, 1);
////    changeThrottle(stear2 + throttle, 2);
////  }
//}
//
//int readThrottle(int a) {
//  int t;
//  if (a == 1)
//    t = esc1.read();
//  if (a == 2)
//    t = esc2.read();
//
//  Serial.print("Current throttle is: ");
//  Serial.println(t);
//
//  return t;
//}
//
//void changeThrottle(int tt, int a) {
//
//  // Read the current throttle value
//  int currentThrottle = readThrottle(a);
//
//  // Are we going up or down?
//  int step = 1;
//  if ( tt < currentThrottle )
//    step = -1;
//
//  // Slowly move to the new throttle value
//  while ( currentThrottle != tt ) {
//    if (a == 1)
//      esc1.write(currentThrottle + step);
//    if (a == 2)
//      esc2.write(currentThrottle + step);
//    currentThrottle = readThrottle(a);
//    delay(throttleChangeDelay);
//  }
//
//}

//#include <Servo.h> 
//
//Servo esc;
//
//int escPin = 9;
//int minPulseRate = 1000;
//int maxPulseRate = 2000;
//int throttleChangeDelay = 100;
//
//void setup() {
//  
//  Serial.begin(9600);
//  Serial.setTimeout(500);
//  
//  // Attach the the servo to the correct pin and set the pulse range
//  esc.attach(escPin, minPulseRate, maxPulseRate); 
//  // Write a minimum value (most ESCs require this correct startup)
//  esc.write(0);
//  
//}
//
//void loop() {
//
//  // Wait for some input
//  if (Serial.available() > 0) {
//    
//    // Read the new throttle value
//        int throttle1 = analogRead(0);
//    throttle1 = map(throttle1, 1023*0.26/5, 1023*0.48/5, 0, 180);
////    int throttle = normalizeThrottle( Serial.parseInt() );
//    
//    // Print it out
//    Serial.print("Setting throttle to: ");
//    Serial.println(throttle1);
//    
//    // Change throttle to the new value
//    esc.write(throttle1);
//    
//  }
//
//}

//void changeThrottle(int throttle) {
//  
//  // Read the current throttle value
//  int currentThrottle = readThrottle();
//  
//  // Are we going up or down?
//  int step = 1;
//  if( throttle < currentThrottle )
//    step = -1;
//  
//  // Slowly move to the new throttle value 
//  while( currentThrottle != throttle ) {
//    esc.write(currentThrottle + step);
//    currentThrottle = readThrottle();
//    delay(throttleChangeDelay);
//  }
//  
//}
//
//int readThrottle() {
//  int throttle = esc.read();
//  
//  Serial.print("Current throttle is: ");
//  Serial.println(throttle);
//  
//  return throttle;
//}
//
//// Ensure the throttle value is between 0 - 180
//int normalizeThrottle(int value) {
//  if( value < 0 )
//    return 0;
//  if( value > 180 )
//    return 180;
//  return value;
//}

#include <Servo.h>
 
Servo esc;
int throttlePin = 6;

void setup()
{
Serial.begin(9600);
esc.attach(9);
}
 
void loop()
{
int throttle = pulseIn(throttlePin,HIGH);
  Serial.print("Channel 2:");
  Serial.println(throttle);
delay(1000);
//throttle = map(throttle,53, 102, 0,1023);
throttle = map(throttle, 1125,1920,0, 180);
esc.write(throttle);
  Serial.println(throttle);
}
