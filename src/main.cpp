#include <Arduino.h>
#include <AccelStepper.h>

/*---------------Constants----------------------------------*/
#define INPUT_PIN 23
#define STEP_PIN 22
#define DIR_PIN 20

#define MAX_SPD 1000

/*---------------Module Function Prototypes-----------------*/
void flushSerial(void);

/*---------------Module Variables---------------------------*/
AccelStepper stepper(1, STEP_PIN, DIR_PIN);
static uint16_t lastPot;
static int16_t currSpd;
static bool currDir = true;

/*---------------Teensy Main Functions----------------------*/
void setup() {
  // Connect to Serial
  Serial.begin(9600);
  while(!Serial);

  // Read input from pin 23
  pinMode(INPUT_PIN, INPUT);

  // STEP and DIR on pins 22 and 21
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  // Set up motor
  stepper.setMaxSpeed(MAX_SPD);
}

void loop() {
  // Update speed if potentiometer changes
  uint16_t newPot = analogRead(INPUT_PIN);
  if (newPot != lastPot) {
    currSpd = map(newPot, 0, 1023, 0, MAX_SPD);
    if (!currDir) currSpd = currSpd * -1;
    stepper.setSpeed(currSpd);
    lastPot = newPot;
  }

  // Update direction if keyboard pressed
  if (Serial.available()) {
    char input = Serial.read();
    currDir = !currDir;
    flushSerial();
  }

  stepper.runSpeed();
}

/*----------------Module Functions--------------------------*/
void flushSerial(void) {
  while(Serial.available()) {
    char downthedrain = Serial.read();
  }
}