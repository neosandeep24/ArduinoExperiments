#include <Servo.h>

// Leg servos
Servo frontLeft;
Servo rearLeft;
Servo frontRight;
Servo rearRight;

// Pin assignments
const int FL_PIN = 8;
const int RL_PIN = 9;
const int FR_PIN = 11;
const int RR_PIN = 10;

// Gait tuning
const int CENTER = 90;      // neutral position
const int SWING  = 25;      // step length
const int STEP   = 1;       // smoothness (smaller = smoother)
const unsigned long STEP_TIME = 20; // ms per update

unsigned long lastUpdate = 0;
int offset = 0;
bool forward = true;

void setup() {
  frontLeft.attach(FL_PIN);
  rearLeft.attach(RL_PIN);
  frontRight.attach(FR_PIN);
  rearRight.attach(RR_PIN);
}

void loop() {
  if (millis() - lastUpdate >= STEP_TIME) {
    lastUpdate = millis();

    // Move offset back and forth
    offset += forward ? STEP : -STEP;

    if (offset >= SWING || offset <= -SWING) {
      forward = !forward;
    }

    // Diagonal trot gait
    frontLeft.write(CENTER + offset);
    rearRight.write(CENTER + offset);

    frontRight.write(CENTER - offset);
    rearLeft.write(CENTER - offset);
  }
}






//Older version
//#include <Servo.h>
//
//Servo servo1; // front left 8
//Servo servo2; //rear left 9
//Servo servo3; // front right 11
//Servo servo4; // rear right 10
//
//int middle = 90;
//int endPoint = 80;
//int stepDelay = 400;
//
//void setup()
//{
//  servo1.attach(8); 
//  servo2.attach(9);
//  servo3.attach(11);
//  servo4.attach(10);
//}
//
//void loop() {
//  servo1.write(middle);
//  servo2.write(middle);
//  servo3.write(middle);
//  servo4.write(middle);
//  delay(stepDelay);
//
//  servo1.write(middle + endPoint);
//  delay(stepDelay);
//  servo3.write(middle + endPoint);
//  delay(stepDelay);
//  servo2.write(middle - endPoint);
//  delay(stepDelay);
//  servo4.write(middle + endPoint);
//  delay(stepDelay);
//}
