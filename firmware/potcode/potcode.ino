#include <Servo.h>

Servo myServo;

const int servoPin = 9;     // servo signal on D9
const int potPin   = A0;    // potentiometer wiper on A0

// Angle limits
const int minAngle = 45;    // lower mechanical limit
const int maxAngle = 135;   // upper mechanical limit

// Optional smoothing / update settings
const int avgSamples = 10;  // moving-average window (reduce jitter)
const int updateMs   = 15;  // write interval to servo

int lastAngle = -1;

// Read potentiometer with simple moving average
int readPotAveraged(int samples) {
  long sum = 0;
  for (int i = 0; i < samples; i++) {
    sum += analogRead(potPin);
    delay(1); // tiny delay between samples
  }
  return sum / samples;
}

void setup() {
  // You can optionally set pulse width limits for your servo model:
  // myServo.attach(servoPin, 500, 2400); // microseconds (min, max)
  myServo.attach(servoPin);
}

void loop() {
  // 1) Read pot (0..1023) with averaging
  int raw = readPotAveraged(avgSamples);

  // 2) Map to desired angle range (45..135)
  int angle = map(raw, 0, 1023, minAngle, maxAngle);

  // 3) Safety clamp
  angle = constrain(angle, minAngle, maxAngle);

  // 4) Write only if changed to reduce unnecessary commands
  if (angle != lastAngle) {
    myServo.write(angle);
    lastAngle = angle;
  }

  delay(updateMs);
}
