#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <ZumoBuzzer.h>
#include <Pushbutton.h>

ZumoBuzzer buzzer;
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

int lastError = 0;

const int MAX_SPEED = 400;
const int CALIBRATION_SPEED = 150;

void setup() {
  reflectanceSensors.init();
  button.waitForButton();
  motors.setSpeeds(0,0);
  Serial.begin(9600);

  motors.setSpeeds(CALIBRATION_SPEED, -CALIBRATION_SPEED);
  
  for (int i = 0; i < 90; i++) {  
    reflectanceSensors.calibrate();
  }
  motors.setSpeeds(0, 0);
}

void loop() {
  unsigned int sensors[6];
  int position = reflectanceSensors.readLine(sensors);
  Serial.println(String(sensors[0]));
}
