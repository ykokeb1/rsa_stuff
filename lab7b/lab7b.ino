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

bool checker = false;
const int but = 5;

// Floats for easy division
float x,y,z;
float xs,ys,zs;
float theta;
float ang;

// Switch case states
enum state {
  inits,
  disph,
  calib  
};
state S = inits;

void setup() {
  Serial.begin(9600);
  pinMode(but, INPUT_PULLUP); // Setup button
  // Initialize magnetometer
  Wire.begin();
  mag.init();
  mag.enableDefault();
}

void loop() {
  // Switch case
  partb();
}

void read_mag() {
  while (1) {
    if (digitalRead(but) == LOW) { // End process if button is pressed
      Serial.println("Reading complete.");
      break; 
    }
    mag.read(); // Reads device for x,y,z
    x = mag.m.x;
    y = mag.m.y;
    z = mag.m.z;
    // Scales x,y,z to be from [-1,1]
    xs = 2*(float ((x-minx)/(maxx-minx))) - 1;
    ys = 2*(float ((y-miny)/(maxy-miny))) - 1;
    zs = 2*(float ((z-minz)/(maxz-minz))) - 1;
    // Find the angle in radians (theta) AND degrees (ang), then display
    theta = atan2(ys,xs);
    ang = (theta*180)/M_PI;
    Serial.println(ang);
    delay(200);
  }
}

void partb () {
  switch (S) {
    case inits:
      // Initialize device, then switch to calibrate state
      mag.init();
      mag.enableDefault();
      S = calib;
      break;  
    case calib:
      // Calibrate device, then switch to display state
      calibrate();
      S = disph;  
      break;
    case disph:
      // Repeatedly display results until button is pressed, then switch to calibrate state
      read_mag();
      S = calib;  
      break;
    default:
      // Never reached, but just in case
      S = calib; 
  }
  delay(500);  
}

void calibrate() {
  checker = false;
  // Set terrible estimates to guarantee calibration
  maxx, maxy, maxz = -30000;
  minx, miny, minz = 30000;
  
  while (!checker) {
    if (digitalRead(but) == LOW) { // End process if button is pressed
      Serial.println("Calibration complete.");
      break; 
    }
    
    mag.read();
    Serial.println("Calibrating...");

    // Continuously updates the max and min values
    maxx = max(mag.m.x, maxx);
    maxy = max(mag.m.y, maxy);
    maxz = max(mag.m.z, maxz);
    
    minx = min(mag.m.x, minx);
    miny = min(mag.m.y, miny);
    minz = min(mag.m.z, minz);

    // Displays the max and min values to see when calibration is complete
    Serial.print(maxx);
    Serial.print(", ");
    Serial.print(maxy);
    Serial.print(", ");
    Serial.println(maxz);

    delay(200);
  }
}
