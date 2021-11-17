const int numPhases = 4; // Number of phases
const int incrementsPerPhaseCycle = 4; // Increments per phase
const int phasePins[numPhases]= {12,10,11,9}; // LED Pins
const int delayTime = 500; // Duration of delay
const int but = 2;
int phase = 0; // Phase of LEDs
int inc = 0; // Increment
const boolean polesOnOff[incrementsPerPhaseCycle][numPhases] = {
  {HIGH, LOW, LOW, LOW}, // Step 1
  {LOW, HIGH, LOW, LOW}, // Step 2
  {LOW, LOW, HIGH, LOW}, // Step 3
  {LOW, LOW, LOW, HIGH} // Step 4
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(but, INPUT_PULLUP); // Setup pullup switch
  int i = phase; // Don't want to overwrite phase for loop()
  for (int i= 0; i < numPhases; i++) {
    pinMode(phasePins[i], OUTPUT);
    digitalWrite(phasePins[i], LOW);
  }
  // LED setup
}

void loop() {
  // Set each of the phase wires on or off,
  // according to the current increment
  if (digitalRead(but) == LOW) { // Detects when the pullup switches from ground
    for (int phase= 0; phase < numPhases; phase++) {
      digitalWrite(phasePins[phase], polesOnOff[inc][phase]); // Set LEDs according to polesOnOff
    }
    inc++;
    inc = inc % 4; // Resets after third increment (since it goes from 3 to 4 and goes back to zero)
  }
  delay(delayTime); // Half second delay  
}
