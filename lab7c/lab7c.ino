#include <Servo.h>

// Libraries needed
#include <LSM6.h>
#include <LIS3MDL.h>
#include <Wire.h>
#include <math.h>
#include <EEPROM.h>
#include <EEWrap.h>

// For storing the variables even after power disconnect
int16_e maxx,maxy,maxz EEMEM; // This is the equivalent of "int x",
int16_e minx,miny,minz EEMEM; // This is the equivalent of "int x",
int16_e temp_minx, temp_miny, temp_minz;
int16_e temp_maxx, temp_maxy, temp_maxz;
 // but stored in EEPROM
LIS3MDL mag;
LSM6 myAccel;
Servo spinny;

bool checker = false;
const int but = 5;

// Floats for easy division
float x,y,z;
float xs,ys,zs;
float theta;
float ang;
float curr_pos, pos;
float val;
float num;

// Switch case states
enum state {
  inits,
  disph,
  calib  
};
state S = inits;

void setup() {
  Serial.begin(9600);
  spinny.attach(3); // Initialize servo motor to pin 3
  pinMode(but, INPUT_PULLUP); // Setup button
  // Initialize accelerometer
  Wire.begin();
  myAccel.init();
  myAccel.enableDefault();
  num = calibrate(); // See calibrate function
}

void loop() {
  // Read the accelerometer
  myAccel.read();
  z = myAccel.a.z;
  val = z/num; // Gets the acceleration in G's
  theta = acos(constrain(val, -1, 1)); // Keeps the arg from -1 to 1
  ang = (theta*180)/M_PI; // Get the value in degrees
  spinny.write(ang); // Writes it to the Servo
  Serial.println(ang);
  delay(250);
}

void read_accel() {
  while (1) {
    if (digitalRead(but) == LOW) { // End process if button is pressed
      Serial.println("Reading complete.");
      break; 
    }
    myAccel.read(); // Reads device for z-accelerometer
    z = myAccel.a.z;
    Serial.println(z);
    delay(200);
  }
}

float calibrate() {
  checker = false;
  float sum = 0;
  for (int i = 0; i < 5; i++) { // Get five measurements
    if (digitalRead(but) == LOW) { // End process if button is pressed
      Serial.println("Calibration complete.");
      break; 
    }
    
    myAccel.read();
    Serial.println("Calibrating...");
    Serial.println("Place the device flat on the table...");
    delay(500);

    // Updates the z-value of the acceleration
    Serial.println(myAccel.a.z);
    sum = sum + myAccel.a.z; // Keeps adding previous value to get total
    delay(1000);
  }
  return sum/5.; // Get the average
}
