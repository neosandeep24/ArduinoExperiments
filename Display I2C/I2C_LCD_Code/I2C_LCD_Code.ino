#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();         // initialize the lcd
  lcd.backlight();    // Turn on the LCD screen backlight
}

void loop()
{
  lcd.setCursor(2, 0);
  lcd.print("NAMASTE ");
  lcd.setCursor(2, 1);
  lcd.print("       INDIA");
  delay(4000);
  lcd.clear();

  lcd.setCursor(2, 0);
  lcd.print("JAI ");
  lcd.setCursor(2, 1);
  lcd.print("    SRI RAM");
  delay(4000);
  lcd.clear();


  lcd.setCursor(2, 0);
  lcd.print("I LOVE ");
  lcd.setCursor(2, 1);
  lcd.print("      MY MOM");
  delay(4000);
  lcd.clear();
}
