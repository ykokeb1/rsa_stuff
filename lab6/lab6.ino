// Necessary libraries
#include <RH_RF69.h>
#include <SPI.h>

// Setup of necessary pins
#define MOSI 9
#define MISO 10
#define SCK 11
#define CS 8
#define RST 7
#define INT 2

RH_RF69 RF69(CS, INT); // Initialize tranceiver

const int INC_BUT = 5; // Increment button
const int TRANS_BUT = 4; // Trasmit button
const int freq = 915; // in MHz
int i = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Initalize pullup buttons
  pinMode(INC_BUT, INPUT_PULLUP);
  pinMode(TRANS_BUT, INPUT_PULLUP);

  // Initialize reset
  pinMode(RST, OUTPUT);
  digitalWrite(RST, LOW);
  digitalWrite(RST, HIGH);
  delay(10);
  digitalWrite(RST, LOW);
  delay(10);

  // Initialize transmitter and set it to 915 MHz for receiver
  RF69.init();
  RF69.setFrequency(freq);
  RF69.setTxPower(15, true);
}

void loop() {
  // Reads input from button, increments counter if button is pushed
  if (digitalRead(INC_BUT) == LOW) {
    i++;
    if (i > 42) {
      i = 1;  
    }  
  }
  Serial.println(i);

  // Transmits count once transmitter button is pressed
  if (digitalRead(TRANS_BUT) == LOW) {
    char radiopacket[1] = {i};
    // Send a message!
    RF69.send((uint8_t *)radiopacket, strlen(radiopacket));
    RF69.waitPacketSent();
  }
}
