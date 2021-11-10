#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_MOSI 9
#define OLED_CLK 10
#define OLED_DC 11
#define OLED_CS 12
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

/*
const int pinNum = 13;  // Digital pin where output is being measured
const int period = 50;  // Period
unsigned long time;  // Time placeholder
*/
const int trig = 2;
const int ech = 3;
float time1, time2;
float dist;
unsigned long time;  // Time placeholder
// The setup routine runs once when you press reset:
void setup() {
  pinMode(trig, OUTPUT);  // Set up trigger
  pinMode(ech, INPUT);  // Set up echo
  display.begin(SSD1306_SWITCHCAPVCC);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(2); // sets text size; 1 is small, 2 is medium, and 3 is large.
  display.setTextColor(WHITE);
   display.print("howdy");
  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
}


void loop() {
  digitalWrite(trig, LOW); // Sets trigger low
  delayMicroseconds(10);
  digitalWrite(trig, HIGH); // Sets trigger high after a delay
  delayMicroseconds(10);
  digitalWrite(trig, LOW); // Sets trigger low
  while (digitalRead(ech) == LOW) {} // Wait until echo receives a signal
  time1 = micros();
  while (digitalRead(ech) == HIGH) { // Wait until signal is finished
   if ((micros() - time1) > 24000) { // If the signal time is greater than 24,000us, end the loop
    break;
   }
  }
  time2 = micros();
  dist = 1.7*1e10*(time2-time1); // Calculate the distance from the reflective material
                                          // based on the time of the signal's round trip and the
                                          // speed of sound in air.
  display.clearDisplay(); // Clear the screen
  display.print(String(dist, 2)); // Print the distance
  display.display(); // Display the printed statement on the OLED screen
}
