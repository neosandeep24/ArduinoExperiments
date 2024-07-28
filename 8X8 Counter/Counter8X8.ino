#include "LedControl.h"
  
LedControl lc=LedControl(12,10,11,1);

unsigned long delaytime1=1000;
unsigned long delaytime2=5000;
void setup() {
 
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,1);
  /* and clear the display */
  lc.clearDisplay(0);

}

/*
 This method will count down from 10 to 1 then display a heart. Byte letters refer to digits, Byte z is the heart
 */
void CountdownOnMatrix()
{
  
  /* here is the data for the characters */
  byte j[8]={B01000001,B11111111,B10000000,B01111110,B10000001,B10000001,B10000001,B01111110};
  byte i[8]={B00000000,B01001110,B10010001,B10010001,B10010001,B01111110,B00000000,B00000000};
  byte h[8]={B00000000,B01110110,B10001001,B10001001,B10001001,B01110110,B00000000,B00000000};
  byte g[8]={B00000000,B00000001,B11100001,B00010001,B00001001,B00000111,B00000000,B00000000};
  byte f[8]={B00000000,B01111110,B10001001,B10001001,B10001001,B01110010,B00000000,B00000000};
  byte e[8]={B00000000,B01001111,B10001001,B10001001,B10001001,B01110001,B00000000,B00000000};
  byte d[8]={B00000000,B00110000,B00101000,B00100100,B00100010,B11111111,B00100000,B00000000};
  byte c[8]={B00000000,B01000010,B10000001,B10001001,B10001001,B01110110,B00000000,B00000000};
  byte b[8]={B00000000,B10000010,B11000001,B10100001,B10010001,B10001110,B00000000,B00000000};
  byte a[8]={B00000000,B00000000,B10000001,B11111111,B10000000,B00000000,B00000000,B00000000};
  byte z[8]={B00011110,B00111111,B01111111,B11111110,B11111110,B01111111,B00111111,B00011110};
  

  /* now display them one by one with a small delay */
  lc.setRow(0,0,j[0]);
  lc.setRow(0,1,j[1]);
  lc.setRow(0,2,j[2]);
  lc.setRow(0,3,j[3]);
  lc.setRow(0,4,j[4]);
  lc.setRow(0,5,j[5]);
  lc.setRow(0,6,j[6]);
  lc.setRow(0,7,j[7]);
  delay(delaytime1);
  lc.setRow(0,0,i[0]);
  lc.setRow(0,1,i[1]);
  lc.setRow(0,2,i[2]);
  lc.setRow(0,3,i[3]);
  lc.setRow(0,4,i[4]);
  lc.setRow(0,5,i[5]);
  lc.setRow(0,6,i[6]);
  lc.setRow(0,7,i[7]);
  delay(delaytime1);
  lc.setRow(0,0,h[0]);
  lc.setRow(0,1,h[1]);
  lc.setRow(0,2,h[2]);
  lc.setRow(0,3,h[3]);
  lc.setRow(0,4,h[4]);
  lc.setRow(0,5,h[5]);
  lc.setRow(0,6,h[6]);
  lc.setRow(0,7,h[7]);
  delay(delaytime1);
  lc.setRow(0,0,g[0]);
  lc.setRow(0,1,g[1]);
  lc.setRow(0,2,g[2]);
  lc.setRow(0,3,g[3]);
  lc.setRow(0,4,g[4]);
  lc.setRow(0,5,g[5]);
  lc.setRow(0,6,g[6]);
  lc.setRow(0,7,g[7]);
  delay(delaytime1);
  lc.setRow(0,0,f[0]);
  lc.setRow(0,1,f[1]);
  lc.setRow(0,2,f[2]);
  lc.setRow(0,3,f[3]);
  lc.setRow(0,4,f[4]);
  lc.setRow(0,5,f[5]);
  lc.setRow(0,6,f[6]);
  lc.setRow(0,7,f[7]);
  delay(delaytime1);
  lc.setRow(0,0,e[0]);
  lc.setRow(0,1,e[1]);
  lc.setRow(0,2,e[2]);
  lc.setRow(0,3,e[3]);
  lc.setRow(0,4,e[4]);
  lc.setRow(0,5,e[5]);
  lc.setRow(0,6,e[6]);
  lc.setRow(0,7,e[7]);
  delay(delaytime1);
  lc.setRow(0,0,d[0]);
  lc.setRow(0,1,d[1]);
  lc.setRow(0,2,d[2]);
  lc.setRow(0,3,d[3]);
  lc.setRow(0,4,d[4]);
  lc.setRow(0,5,d[5]);
  lc.setRow(0,6,d[6]);
  lc.setRow(0,7,d[7]);
  delay(delaytime1);
  lc.setRow(0,0,c[0]);
  lc.setRow(0,1,c[1]);
  lc.setRow(0,2,c[2]);
  lc.setRow(0,3,c[3]);
  lc.setRow(0,4,c[4]);
  lc.setRow(0,5,c[5]);
  lc.setRow(0,6,c[6]);
  lc.setRow(0,7,c[7]);
  delay(delaytime1);
  lc.setRow(0,0,b[0]);
  lc.setRow(0,1,b[1]);
  lc.setRow(0,2,b[2]);
  lc.setRow(0,3,b[3]);
  lc.setRow(0,4,b[4]);
  lc.setRow(0,5,b[5]);
  lc.setRow(0,6,b[6]);
  lc.setRow(0,7,b[7]);
  delay(delaytime1);
  lc.setRow(0,0,a[0]);
  lc.setRow(0,1,a[1]);
  lc.setRow(0,2,a[2]);
  lc.setRow(0,3,a[3]);
  lc.setRow(0,4,a[4]);
  lc.setRow(0,5,a[5]);
  lc.setRow(0,6,a[6]);
  lc.setRow(0,7,a[7]);
  delay(delaytime1);
  lc.setRow(0,0,z[0]);
  lc.setRow(0,1,z[1]);
  lc.setRow(0,2,z[2]);
  lc.setRow(0,3,z[3]);
  lc.setRow(0,4,z[4]);
  lc.setRow(0,5,z[5]);
  lc.setRow(0,6,z[6]);
  lc.setRow(0,7,z[7]);
  delay(delaytime2);
}


void loop() 
{ 
//  if (digitalRead(buttonApin) == LOW)
//  {
  CountdownOnMatrix();
  lc.clearDisplay(0);
//}
}
