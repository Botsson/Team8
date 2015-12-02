#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <ZumoBuzzer.h>
#include <Pushbutton.h>

ZumoBuzzer buzzer;
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

const int MAX_SPEED = 100;

void setup() {
  reflectanceSensors.init();
  button.waitForButton();
}

void loop() {
  motors.setSpeeds(MAX_SPEED, MAX_SPEED);
}
