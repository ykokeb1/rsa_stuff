const int pinNum = 2;
const int period = 10;
float scale;
float duty_cycle;
int c1 = 0; // First counter
float c2 = 0;  // Second counter
unsigned long time;  // Time placeholder

// The setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);  // Setup serial monitor
  pinMode(pinNum, OUTPUT);
  scale = 0.33;
  duty_cycle = scale * period;
}


void loop() {
  digitalWrite(pinNum, HIGH);
  time = millis();
  while (millis() < time + duty_cycle) {}
  digitalWrite(pinNum, LOW);
  time = millis();
  while (millis() < time + (period - duty_cycle)) {}
}
