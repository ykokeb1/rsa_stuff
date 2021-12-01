volatile int count = 0; // Counter, volatile b/c of interrupt
const int chanA = 2; // Pin for Channel A
const int chanB = 3; // Pin for Channel B
const int i1 = 7;
const int i2 = 8;
const int e1 = 5;
float kprop = 7;
float anal, err, rad, con, analout, out, prevtime;
float deltaT = 10;

void setup() {
  Serial.begin(9600);
  pinMode(chanA, INPUT); // Channel A Encoder
  pinMode(chanB, INPUT); // Channel B Encoder
  pinMode(i1, OUTPUT); // Input 1
  digitalWrite(i1, LOW);
  pinMode(i2, OUTPUT); // Input 2
  digitalWrite(i2, LOW);
  pinMode(e1, OUTPUT); // Enable 1
  pinMode(A2, INPUT); // Potentiometer
  attachInterrupt(0, change_A, CHANGE); // Setup interrupt for first button
  attachInterrupt(1, change_B, CHANGE); // Setup interrupt for second button
}

void loop() {
  // put your main code here, to run repeatedly:
  anal = (analogRead(A2) * 1632.) / 1023.; // analog --> motor count
  //Serial.println(anal);
  err = anal - count; // error
  // Serial.println(err);
  rad = (2.*M_PI*err) / (1632.); // error in radians
  con = kprop * rad; // control signal
  //Serial.println(con);
  // writing based on sign of control signal
  if (con > 0) {
    digitalWrite(i1, HIGH);
    digitalWrite(i2, LOW);
  } else if (con < 0) {
    digitalWrite(i1, LOW);
    digitalWrite(i2, HIGH);
  }

  analout = (con*255.)/5.; // get analog value from control signal
  out = constrain(abs(analout), 0, 255); // constrain analog value
  analogWrite(e1, out); // write analog value
  //Serial.println(out);

  // set correct timing
  prevtime = millis();
  while (millis() - prevtime < deltaT ) { }
  prevtime = millis();
}



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
