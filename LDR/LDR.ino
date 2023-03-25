
void setup()
{
  pinMode(A0,INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}
int value=0;
void loop()
{
 value=analogRead(A0);
  if(value>20)
  {
    digitalWrite(13,HIGH);
  }
  else
  {
    digitalWrite(13,LOW);
  }
    
  
}
