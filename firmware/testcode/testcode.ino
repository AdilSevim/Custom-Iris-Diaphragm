#include <Servo.h>

Servo myServo;
const int servoPin = 9;

// Motion settings
const int minAngle   = 45;   // lower limit (degrees)
const int maxAngle   = 135;  // upper limit (degrees)
const int stepDeg    = 1;    // angle increment per step (degrees)
const int stepDelay  = 10;   // delay between steps (milliseconds)

void setup() {
  myServo.attach(servoPin);    // attach servo signal to D9
  myServo.write(minAngle);     // start at 45°
  delay(500);                  // small settling delay
}

void loop() {
  // Sweep 45° -> 135°
  for (int a = minAngle; a <= maxAngle; a += stepDeg) {
    myServo.write(a);
    delay(stepDelay);
  }

  // Sweep 135° -> 45°
  for (int a = maxAngle; a >= minAngle; a -= stepDeg) {
    myServo.write(a);
    delay(stepDelay);
  }
}
