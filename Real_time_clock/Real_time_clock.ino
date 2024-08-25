 #include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);     // IF YOUR ADDRESS IS DIFFERENT, PUT THAT IN PLACE OF '0x27F'
const char *ssid     = "";    
const char *password = "";      
WiFiUDP ntpUDP;
#define offset 19800              
NTPClient timeClient(ntpUDP, "pool.ntp.org");
void setup() {
  WiFi.begin(ssid, password);
  timeClient.begin();
  timeClient.setTimeOffset(offset);    
  lcd.init();
  lcd.backlight();
  lcd.blink_on();
  lcd.clear();
}
void loop() {
  timeClient.update();
  time_t epochTime = timeClient.getEpochTime();
  String formattedTime = timeClient.getFormattedTime();
  struct tm *ptm = gmtime ((time_t *)&epochTime);

  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon+1;
  int currentYear = ptm->tm_year+1900;
  String currentDate = String(monthDay)+"/"+String(currentMonth)+"/"+String(currentYear); 
  
  lcd.setCursor(0, 0);
  lcd.print("DATE:"+currentDate);
  lcd.setCursor(0, 1);
  lcd.print("TIME:"+formattedTime);
  lcd.setCursor(15, 1);
  delay(500);
}
