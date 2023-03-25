
void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}
int value=0;
void loop()
{
  value=analogRead(A0);
  int values=(value/539.00)*100;
  Serial.println(values);//percentage of moisture
  if(values>50)
  digitalWrite(13, HIGH);
  else
  digitalWrite(13, LOW);
  delay(1000);
}
