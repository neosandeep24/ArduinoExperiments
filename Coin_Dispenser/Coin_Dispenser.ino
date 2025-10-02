#include <Servo.h>

Servo myServo; 

int inches = 0;
int cm = 0;
int servoPin =9;
int initialPos = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT); 
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void setup()
{
 Serial.begin(9600);
 myServo.attach(servoPin);   // attach servo to pin
  myServo.write(initialPos);  // set servo to initial position
  delay(1000);                // wait for servo to settle
}

void loop()
{
  cm = 0.01723 * readUltrasonicDistance(6, 7);
  Serial.println(cm);
  if (cm <= 5)
  {
    myServo.write(180);
  delay(500);
  // Return servo back to initial position (0 degrees)
  myServo.write(initialPos);
 delay(1000);  // wait 1 second at original position
  }
  delay(100); 
}


//Testing 3d model
//#include <Servo.h>
//
//Servo myServo;  // create servo object
//int servoPin = 9; // servo signal pin connected to D9
//int initialPos = 0; // starting position
//
//void setup() {
//  myServo.attach(servoPin);   // attach servo to pin
//  myServo.write(initialPos);  // set servo to initial position
//  delay(1000);                // wait for servo to settle
//}
//
//void loop() {
//  // Rotate servo to 60 degrees
//  myServo.write(180);
//  delay(500);
//  // Return servo back to initial position (0 degrees)
//  myServo.write(initialPos);
// delay(1000);  // wait 1 second at original position
//}
