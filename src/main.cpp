#include <Arduino.h>

/*---------------Constants----------------------------------*/
#define INPUT_PIN 23
#define SPD_PIN 22
#define DIR_PIN 20

#define MAX_SPD 255
#define MAX_POT 1023

/*---------------Module Function Prototypes-----------------*/
u_int16_t testPotentiometer(void);
bool testKeyboard(void);
void changeSpeed(uint16_t newSpeed);
void toggleDir(void);
void flushSerial(void);

/*---------------Module Variables---------------------------*/
static uint16_t currPot = MAX_POT / 2;
static bool currDir = false;

/*---------------Teensy Main Functions----------------------*/
void setup() {
  // Connect to Serial
  Serial.begin(9600);
  while(!Serial);

  // Read input from pin 23
  pinMode(INPUT_PIN, INPUT);

  // SPD and DIR on pins 22 and 20
  pinMode(SPD_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  // Start the motor
  changeSpeed(currPot);
  toggleDir();
}

void loop() {
  // Read input
  uint16_t newPot = testPotentiometer();
  bool newKey = testKeyboard();

  // Respond to potentiometer
  if (newPot) {
    changeSpeed(newPot);
  }

  // Respond to keyboard
  if (newKey) {
    toggleDir();
  }
}

/*----------------Module Functions--------------------------*/
u_int16_t testPotentiometer(void) {
  u_int16_t result = analogRead(INPUT_PIN);
  return result != currPot ? result : 0;
}

bool testKeyboard(void) {
  bool result = false;
  if (Serial.available()) {
    result = true;
    flushSerial();
  }
  return result;
}

void changeSpeed(uint16_t newPot) {
  analogWrite(SPD_PIN, map(newPot, 0, MAX_POT, 0, MAX_SPD));
}

void toggleDir(void) {
  currDir = !currDir;
  digitalWrite(DIR_PIN, currDir);
}

void flushSerial(void) {
  while(Serial.available()) {
    char downthedrain = Serial.read();
  }
}