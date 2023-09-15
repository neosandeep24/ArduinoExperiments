//You will need a Max7219 library
//In Arduino IDE go to Tools -> Manage Libraries -> Search Max7219 and install it

int ANIMDELAY = 100;  
int INTENSITYMIN = 0; 
int INTENSITYMAX = 8; 
//Subcribe to the neo studios 
//Pins
//VCC -> VCC
//GND -> GND
int DIN_PIN = 12;      // data in pin
int CS_PIN = 10;       // load (CS) pin
int CLK_PIN = 11;      // clock pin
 
// MAX7219 registers
byte MAXREG_DECODEMODE = 0x09;
byte MAXREG_INTENSITY  = 0x0a;
byte MAXREG_SCANLIMIT  = 0x0b;
byte MAXREG_SHUTDOWN   = 0x0c;
byte MAXREG_DISPTEST   = 0x0f;

//heart pattern for each led
const unsigned char heart[] =
{
  B01100110,
  B11111111,
  B11111111,
  B11111111,
  B01111110,
  B00111100,
  B00011000,
  B00000000
};
 
void setup ()
{
  pinMode(DIN_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  pinMode(CS_PIN, OUTPUT);
 
  // initialization of the MAX7219
  setRegistry(MAXREG_SCANLIMIT, 0x07);
  setRegistry(MAXREG_DECODEMODE, 0x00); 
  setRegistry(MAXREG_SHUTDOWN, 0x01);    
  setRegistry(MAXREG_DISPTEST, 0x00);   
  setRegistry(MAXREG_INTENSITY, 0x0f & INTENSITYMIN);
 
  // draw hearth
  setRegistry(1, heart[0]);
  setRegistry(2, heart[1]);
  setRegistry(3, heart[2]);
  setRegistry(4, heart[3]);
  setRegistry(5, heart[4]);
  setRegistry(6, heart[5]);
  setRegistry(7, heart[6]);
  setRegistry(8, heart[7]);
}
 
 
void loop ()
{
  // second beat
  setRegistry(MAXREG_INTENSITY, 0x0f & INTENSITYMAX);
  delay(ANIMDELAY);
  
  // switch off
  setRegistry(MAXREG_INTENSITY, 0x0f & INTENSITYMIN);
  delay(ANIMDELAY);
  
  // second beat
  setRegistry(MAXREG_INTENSITY, 0x0f & INTENSITYMAX);
  delay(ANIMDELAY);
  
  // switch off
  setRegistry(MAXREG_INTENSITY, 0x0f & INTENSITYMIN);
  delay(ANIMDELAY*6);
}
 
 
void setRegistry(byte reg, byte value)
{
  digitalWrite(CS_PIN, LOW);
 
  putByte(reg);   // specify register
  putByte(value); // send data
 
  digitalWrite(CS_PIN, LOW);
  digitalWrite(CS_PIN, HIGH);
}
 
void putByte(byte data)
{
  byte i = 8;
  byte mask;
  while (i > 0)
  {
    mask = 0x01 << (i - 1);        
    digitalWrite( CLK_PIN, LOW);   
    if (data & mask)              
      digitalWrite(DIN_PIN, HIGH); 
    else
      digitalWrite(DIN_PIN, LOW);  
    digitalWrite(CLK_PIN, HIGH);  
    --i;                          
  }
}
