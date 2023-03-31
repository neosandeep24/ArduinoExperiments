int pirSensor = 3;

void setup() {
  pinMode(pirSensor, INPUT);
  pinMode(13, OUTPUT); 
  Serial.begin(9600); 
}

void loop() {
  int sensorValue = digitalRead(pirSensor);

  if (sensorValue == 1) {
    digitalWrite(13,HIGH);
     Serial.write("Detected\n");
  }
  else
  {
    digitalWrite(13,LOW);
         Serial.write("Not Detected\n");

  }
  delay(2000);
}
