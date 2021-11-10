const int pinNum = 2;
const int period = 1000;
long scale;  // Scaler for the duty_cycle variable
float duty_cycle; 

// The setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);  // Setup serial monitor
  pinMode(pinNum, OUTPUT);
}


void loop() {
  scale = 0.33;  // LED is 33% high, 67% low across period
  duty_cycle = scale * period;  // Scales 0.33 by period
  digitalWrite(pinNum, HIGH);
  time = millis();
  while (millis() < time + duty_cycle) {}  // Turns the LED on depending on duty cycle time
  digitalWrite(pinNum, LOW);
  time = millis();
  while (millis() < time + (period - duty_cycle)) {} // Turns the LED off with the remaining time from the period
}
