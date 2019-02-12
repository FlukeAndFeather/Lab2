#include <Arduino.h>
#include <AccelStepper.h>

/*---------------Constants----------------------------------*/
#define INPUT_PIN 23
#define STEP_PIN 22
#define DIR_PIN 21

#define MAX_SPD 1000

/*---------------Module Variables---------------------------*/
AccelStepper stepper(1, STEP_PIN, DIR_PIN);
static uint16_t lastPot;
static uint16_t currSpd;

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
  digitalWrite(DIR_PIN, HIGH);
}

void loop() {
  // Update speed if potentiometer changes
  uint16_t newPot = analogRead(INPUT_PIN);
  if (newPot != lastPot) {
    currSpd = map(newPot, 0, 1023, 0, MAX_SPD);
    stepper.setSpeed(currSpd);
    lastPot = newPot;
  }
  stepper.runSpeed();
}
