const int numPhases = 4; // Number of phases
const int incrementsPerPhaseCycle = 4; // Increments per phase
const int phasePins[numPhases]= {12,10,11,9}; // LED Pins
const int delayTime = 500; // Duration of delay
const int but2 = 2;
const int but3 = 3;
const int but4 = 4;
int dir = 1;
int phase = 0; // Phase of LEDs
int inc = 0; // Increment
int deg = 360;

const boolean polesOnOff[incrementsPerPhaseCycle][numPhases] = {
  {HIGH, HIGH, LOW, LOW}, // Step 1
  {LOW, HIGH, HIGH, LOW}, // Step 2
  {LOW, LOW, HIGH, HIGH}, // Step 3
  {HIGH, LOW, LOW, HIGH} // Step 4
};
/*
const boolean polesOnOff[incrementsPerPhaseCycle][numPhases] = {
  {HIGH, LOW, LOW, LOW}, // Step 1
  {LOW, HIGH, LOW, LOW}, // Step 2
  {LOW, LOW, HIGH, LOW}, // Step 3
  {LOW, LOW, LOW, HIGH} // Step 4
};
*/
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(but2, INPUT_PULLUP); // Setup pullup switch
  pinMode(but3, INPUT_PULLUP); // Setup pullup switch
  pinMode(but4, INPUT_PULLUP); // Setup pullup switch
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
  if (digitalRead(but2) == LOW) {
    inc=inc + dir;
    if (inc == -1) {
        inc = 3;
    }
    inc = inc % 4; // Resets after third increment (since it goes from 3 to 4 and goes back to zero)
    for (int phase= 0; phase < numPhases; phase++) {
      digitalWrite(phasePins[phase], polesOnOff[inc][phase]); // Set LEDs according to polesOnOff
    }
    delay(delayTime); // Delay after 50ms
  }
  if (digitalRead(but3) == LOW) {
    for (int j = 0; j < int(deg/(7.5)); j++) { // 360 degree turn requires 48 iterations (360/7.5)
      inc=inc + dir;
      if (inc == -1) {
        inc = 3;
      }
      inc = inc % 4; // Resets after third increment (since it goes from 3 to 4 and goes back to zero)
      for (int phase= 0; phase < numPhases; phase++) {
        digitalWrite(phasePins[phase], polesOnOff[inc][phase]); // Set LEDs according to polesOnOff
      }
      delay(4); // Delay after 50ms
    }
  }
  if (digitalRead(but4) == LOW) {
    dir = dir * -1;
    delay(delayTime);
  }
}
