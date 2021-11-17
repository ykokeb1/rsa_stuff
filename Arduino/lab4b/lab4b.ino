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
// The setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);  // Setup serial monitor
  pinMode(trig, INPUT);  // Set up trigger
  pinMode(ech, OUTPUT);  // Set up echo
  display.begin(SSD1306_SWITCHCAPVCC);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(3); // sets text size; 1 is small, 2 is medium, and 3 is large.
  display.setTextColor(WHITE);
  display.print("balls");
  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
}


void loop() {
  
}
