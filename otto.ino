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

const char rhapsody[] PROGMEM = "O6 T40 L16 d#<b<f#<d#<f#<bd#f#"
  "T80 c#<b-<f#<c#<f#<b-c#8"
  "T180 d#b<f#d#f#>bd#f#c#b-<f#c#f#>b-c#8 c>c#<c#>c#<b>c#<c#>c#c>c#<c#>c#<b>c#<c#>c#"
  "c>c#<c#>c#<b->c#<c#>c#c>c#<c#>c#<b->c#<c#>c#"
  "c>c#<c#>c#f>c#<c#>c#c>c#<c#>c#f>c#<c#>c#"
  "c>c#<c#>c#f#>c#<c#>c#c>c#<c#>c#f#>c#<c#>c#d#bb-bd#bf#d#c#b-ab-c#b-f#d#";



void setup() {
  button.waitForButton();
  buzzer.playFromProgramSpace(rhapsody);
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
    followLine();
  } else {
    digitalWrite(13, LOW);
    motors.setSpeeds(0, 0);
    goStraight();
  }
  

  /*
  if (onLineWithPosition(position)) {
    digitalWrite(13, HIGH);
    //motors.setSpeeds(MAX_SPEED, MAX_SPEED);
  } else {
    digitalWrite(13, LOW);
    //motors.setSpeeds(0, 0);
  }
  */
  
  
  int error = position - 2500;
  
  // motors.setSpeeds(m1Speed, m2Speed);
}

void goStraight() {
  motors.setSpeeds(MAX_SPEED, MAX_SPEED);
}

void followLine() {
  
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

bool onLineWithPosition(int pos){
  if (pos == 0){
    return false;
  } else if (pos > 5000) {
    return false;
  }
  return true;
  
}


