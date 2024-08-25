#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// Initialize the LCD with the address 0x27 for a 16x2 display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Initialize Bluetooth module using SoftwareSerial on pins 2 (RX) and 3 (TX)
SoftwareSerial bluetooth(2, 3); // RX, TX

void setup() {
  lcd.init();
  lcd.backlight();

  bluetooth.begin(9600); 

  lcd.setCursor(0, 0);
  lcd.print("Waiting for BT");
}

void loop() {
  if (bluetooth.available()) {
    delay(100);
    lcd.clear();

    while (bluetooth.available() > 0) {
      char incomingChar = bluetooth.read();
      lcd.write(incomingChar);
      delay(100); 
    }
  }
}
