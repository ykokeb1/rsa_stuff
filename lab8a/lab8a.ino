// Necessary libraries
#include <SoftwareSerial.h>
#include <TinyGPS.h>

const int tx = 3; // TX Pin
const int rx = 4; // RX Pin
float flat, flon;

TinyGPS gps; // Setup GPS
SoftwareSerial ss(rx, tx); // Setup SS

void setup() {
  // Necessary variab;es
  bool newData = false;
  float x, y;
  unsigned long chars;

  // Both serial and SS must be at 9600 BAUD
  Serial.begin(9600);
  ss.begin(9600);
  delay(1000);
  // Setup GPS; if setup failed, print error message
  for (unsigned long start = millis(); millis() - start < 1000;) {
    while (ss.available()) { // 
      char c = ss.read();
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }
  
  if (newData) {
    unsigned long age;
    // Get GPS Data and print latitude and longitude if working
    gps.f_get_position(&flat, &flon, &age);
    Serial.print("LAT=");
    Serial.print(flat);
    Serial.print("   LON=");
    Serial.print(flon);
    Serial.println();
  } else {
    Serial.println("ERROR: GPS setup failed.");
    exit(0);  
  }
}

void loop() {
  float lat, lon, dist, dist_lat, dist_lon, theta, ang;
  unsigned long ag;
  
  if (ss.available()) {
    if (gps.encode(ss.read())) {
      // Only proceeds if SS is available AND a reading is ready
      gps.f_get_position(&lat, &lon, &ag); // Gets latitude and longitude
      dist_lat = TinyGPS::distance_between(flat,flon,lat,flon); // Calculate latitude distance
      dist_lon = TinyGPS::distance_between(flat,flon,flat,lon); // Calculate longitude distance
      // Account for sign of latitude distance
      if (lat < flat) {
        dist_lat = dist_lat * -1;
      }
      // Account for sign of longitude distance
      if (lon < flon) {
        dist_lon = dist_lon * -1;
      }
      dist = sqrt(sq(dist_lat) + sq(dist_lon)); // Magnitude of distance
      theta = atan2(dist_lat, dist_lon); // Angle (in radians)
      ang = (theta*180)/M_PI; // Radians --> Degrees
      // Print stuff
      Serial.print(dist);
      Serial.print("  ");
      Serial.println(ang);
    }
  }
}
