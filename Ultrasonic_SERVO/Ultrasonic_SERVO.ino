#include <Servo.h>

Servo myServo; 

int inches = 0;
int cm = 0;

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
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  myServo.attach(9); 
  myServo.write(0);  
}

void loop()
{
  cm = 0.01723 * readUltrasonicDistance(6, 7);

  if (cm <= 15)
  {
    digitalWrite(4, HIGH);
    myServo.write(30); 
    Serial.print(cm);
    Serial.println("cm");
  }
  else
  {
    digitalWrite(4, LOW);
    myServo.write(0); 
  }

  delay(100); 
}
