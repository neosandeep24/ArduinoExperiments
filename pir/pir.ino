int led = 13;  
//int fan=12;              
int sensor = 2;              
int state = LOW;             
int val = 0;                 

void setup() {
  pinMode(led, OUTPUT);
 // pinMode(fan,OUTPUT);      
  pinMode(sensor, INPUT); 
   Serial.begin(9600);  
}

void loop(){
  val = digitalRead(sensor); 
  if (val == HIGH) {  
           
    digitalWrite(led, HIGH); 
   // digitalWrite(fan,HIGH);  
    delay(2000);                
    
    
    /*if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       
    }*/
  } 
  else {
      digitalWrite(led, LOW);
     // digitalWrite(fan,LOW);
      delay(2000);           
  }
   Serial.println(val);
     /* if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;  }  */   
  
}
