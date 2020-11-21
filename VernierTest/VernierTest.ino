// Get the SerialPlot app here : https://hackaday.io/project/5334-serialplot-realtime-plotting-software

#include "VernierLib.h"

VernierLib Vernier;

bool state = true;
volatile unsigned long last_millis;

void setup() {
  Serial.begin(9600);
  Vernier.autoID();
  digitalWrite(13, state);
}

void loop() {
  
  if (digitalRead(12) == LOW && (long)(millis() - last_millis) >= 200) {
    state = !state;
    digitalWrite(13, state);
    last_millis = millis();
  }
  
  if (state) {
    Serial.println(Vernier.readSensor());
  }
}
