volatile int count = 0; // Counter, volatile b/c of interrupt
const int chanA = 2; // Pin for Channel A
const int chanB = 3; // Pin for Channel B

void setup() {
  Serial.begin(9600);
  pinMode(chanA, INPUT_PULLUP); // Channel A Encoder
  pinMode(chanB, INPUT_PULLUP); // Channel B Encoder
  attachInterrupt(digitalPinToInterrupt(chanA), change_A, CHANGE); // Setup interrupt for first button
  attachInterrupt(digitalPinToInterrupt(chanB), change_B, CHANGE); // Setup interrupt for second button
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(count); // Print current value of count
  delay(500); // Delay by half-second
}

// Happens if there is a CHANGE state for Channel A
void change_A() {
  if (digitalRead(chanA) != digitalRead(chanB)) {
    count++; // Incrememnt count if different
  } else {
    count--; // Decrement couunt if same
  }
}

// Happens if there is a CHANGE state for Channel B
void change_B() {
    if (digitalRead(chanA) == digitalRead(chanB)) {
    count++; // Increment count if same
  } else {
    count--; // Decrement count if different
  }
}
