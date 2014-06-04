#include <Touch.h>
#include <Wire.h>

Touch touch (2);

void setup() {
  Serial.begin(9600);
  Serial.println("Start example program");
  
  touch.setup();
  // put your setup code here, to run once:
}

void loop() {
  
  byte touchStatus[12] = { false, false, false, false, false, false, false, false, false, false, false, false};
  touch.readTouchInputs(touchStatus);
  for (int i = 0; i < 12; i++)
    if (touchStatus[i] == true){
      Serial.print("Pulse ");
      Serial.println(i, DEC);
  }
  delay(10);
}
