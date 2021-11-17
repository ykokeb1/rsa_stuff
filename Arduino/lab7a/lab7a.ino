#include <EEPROM.h>
#include <EEWrap.h>
int16_e x EEMEM; // This is the equivalent of "int x",
 // but stored in EEPROM
 
void setup() {
 Serial.begin(9600);
}

void loop() {
  Serial.println(x);
  x++;
  if ( (x > 100) || (x < 0) ) {
    x = 0;
  }
  delay(500);
}
