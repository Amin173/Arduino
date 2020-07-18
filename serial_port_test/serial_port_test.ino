void setup() {
  // put your setup code here, to run once:
SerialUSB.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int a= read_integer();
SerialUSB.print(a);
}



int read_integer(){
     while(SerialUSB.available() > 0)
  {
byte dummyread = SerialUSB.read();
  }
  
while (!SerialUSB.available()); // Wait for characters

unsigned int integerValue=0;  // Max value is 65535
char a;

 if (SerialUSB.available() > 0) { // something came across serial
  integerValue = 0;                        // throw away previous integerValue
       while(1) {               // force into a loop until 'n' is received
      a = SerialUSB.read();
      if (a == '\n') break;   // exit the while(1), we're done receiving
      if (a == -1) continue; // if no characters are in the buffer read() returns -1
      integerValue *= 10;   // shift left 1 decimal place
      // convert ASCII to integer, add, and shift left 1 decimal place
      integerValue = ((a - 48) + integerValue);
    }
}

return(integerValue);
}
