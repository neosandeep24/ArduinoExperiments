#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin definitions for joystick
#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin

// Pin definitions for Display LCD i2c
// SDA -> A4
// SCL -> A5

// Variables to store joystick values
int xValue = 0; // To store value of the X axis
int yValue = 0; // To store value of the Y axis

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16x2 display

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
}

void loop() {
  // Read analog X and Y values from joystick
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);

  Serial.print("x = ");
  Serial.print(xValue);
  Serial.print(", y = ");
  Serial.println(yValue);

  lcd.clear(); // Clear LCD before displaying new direction
  lcd.setCursor(2, 0); // Set cursor position

  if (xValue > 600) {
    lcd.print("  RIGHT");
  } else if (xValue < 400) {
    lcd.print("  LEFT");
  } else if (yValue > 600) {
    lcd.print("  DOWN");
  } else if (yValue < 400) {
    lcd.print("  UP");
  } else {
    lcd.print("  CENTER");
  }

  delay(500); // Add a small delay for stability
}
