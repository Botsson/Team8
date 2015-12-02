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
  button.waitForButton();
  pinMode(13, OUTPUT);
  
  
  reflectanceSensors.init();
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

  if (onLine(sensors)) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
  
  
  int error = position - 2500;
  
  // motors.setSpeeds(m1Speed, m2Speed);
}

bool onLine(unsigned int sensors[])  {
  if(sensors[0] > 500
    || sensors[1] > 500
    || sensors[2] > 500
    || sensors[3] > 500
    || sensors[4] > 500
    || sensors[5] > 500) {
      return true;
    }
    return false;
}

