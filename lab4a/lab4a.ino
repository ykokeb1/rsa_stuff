const int pinNum = 13;  // Digital pin where output is being measured
const int period = 50;  // Period
unsigned long time;  // Time placeholder

// The setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);  // Setup serial monitor
  pinMode(pinNum, OUTPUT);  // Set up LED
}


void loop() {
  digitalWrite(pinNum, HIGH);  // LED turns on
  time = millis();
  while (millis() < time + 0.5*period) {}  // Wait half a period for the next state change  
  digitalWrite(pinNum, LOW);  // LED turns off
  time = millis();
  while (millis() < time + 0.5*period) {}  // One full period has been completed
}
