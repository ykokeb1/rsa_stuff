boolean ard_state = LOW; // Arduino LED state
volatile boolean state = LOW; // External LED state, volatile b/c of interrupt
const int led = 7; // Pin for external LED
const int ard_led = 13; // Pin for Arduino LED

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP); // Button #1
  pinMode(3, INPUT_PULLUP); // Button #2
  pinMode(led, OUTPUT); // LED
  pinMode(ard_led, OUTPUT); // Arduino LED
  attachInterrupt(digitalPinToInterrupt(2), led_blink, FALLING); // Setup interrupt for first button
  attachInterrupt(digitalPinToInterrupt(3), led_blink, FALLING); // Setup interrupt for second button
}

void loop() {
  // put your main code here, to run repeatedly:
  ard_state = !ard_state; // Alternate Arduino LED state
  digitalWrite(ard_led, ard_state); // Write this to Arduino LED
  delay(1000); // Delay by one second
}

// Happens if there is a LOW state for either of the buttons
void led_blink() {
    state = !state; // Alternate external LED state
    digitalWrite(led, state); // Write this to external LED
    int t = millis(); // Record the current time
    while (millis() < t + 500) {} // Do nothing until elapsed time exceeds 500ms (debounce)
}
