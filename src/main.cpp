#include <Arduino.h>
#include <AccelStepper.h>

AccelStepper stepper(1, 22, 21);

/*---------------Teensy Main Functions----------------------*/
void setup() {
  // Connect to Serial
  Serial.begin(9600);
  while(!Serial);

  // DIR and STEP on pins 22 and 21
  pinMode(22, OUTPUT);
  pinMode(21, OUTPUT);

  // Set up motor
  stepper.setMaxSpeed(1000);
  stepper.setSpeed(500);
}

void loop() {
  stepper.runSpeed();
}
