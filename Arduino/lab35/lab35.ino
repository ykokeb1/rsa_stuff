const int analPin = A2;  // Analog pin (cleverly named)
int val;  // Analog value
float volt;  // Voltage
float d; // Distance

// The setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);  // Setup serial monitor
}


void loop() {
  val = analogRead(analPin);  // Reads analog input
  volt = 5*(val/1023.);  // Converts value to voltage
  // d = 20/(volt-0.4);  // Gets distance (cm)
  d = 1/(0.05*volt+0.01);  // Gets distance (cm)
  Serial.println(d);  // Prints distance
  delay(100);
}
