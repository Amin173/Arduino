const int signalpin1 =  0;      // the number of the signal output pin1
const int signalpin2 =  2;      // the number of the signal output pin2
const int button =  3;      // the number of the signal output pin2
int val = 0;
int led = 1;
void setup() {
  // initialize the LED pin as an output:
  pinMode(signalpin1, OUTPUT);
  pinMode(signalpin2, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(button,INPUT_PULLUP);
}

void loop() {
val =digitalRead(button);
digitalWrite(signalpin1,val);
digitalWrite(signalpin2,LOW);
digitalWrite(led,val);
delay(200);
digitalWrite(signalpin1,LOW);
digitalWrite(signalpin2,val);
digitalWrite(led,LOW);
delay(200);
}
