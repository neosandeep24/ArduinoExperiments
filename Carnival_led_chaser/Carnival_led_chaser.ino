// please subscribe to my channel https://youtube.com/@theneostudios?si=cTavnV0uBUAKYJ0j 

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD configuration
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set LCD address to 0x27 for a 16x2 display

// Pin definitions
const int ledPins[] = {3, 4, 5, 6, 7, 8, 9, 10, 11}; // Pins for 9 LEDs
const int swpin = 2;

// Variables
int score = 0;
int highScore = 0;
bool direction = true; // true = right to left, false = left to right
bool gameRunning = false;

unsigned long startTime = 0;
const unsigned long gameDuration = 30000; // 30 seconds

void setup() {
  lcd.init();          // Initialize the LCD
  lcd.backlight();     // Turn on the LCD backlight
  pinMode(swpin, INPUT_PULLUP); // Set joystick button as input with pull-up
  
  // Initialize LED pins
  for (int i = 0; i < 9; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW); // Turn all LEDs off initially
  }
  
  Serial.begin(115200); // Initialize serial communication for debugging
  
  // Display welcome message
  lcd.setCursor(0, 0);
  lcd.print("Welcome to the");
  lcd.setCursor(0, 1);
  lcd.print("Carnival!");
  delay(3000);
  
  // Display start prompt
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press Joystick");
  lcd.setCursor(0, 1);
  lcd.print("to Start!");
  
  // Wait for joystick press
  while (digitalRead(swpin) == HIGH) {
    // Wait for user input
  }
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Starting Game...");
  delay(2000);
  lcd.clear();
  gameRunning = true;
  startTime = millis();
}

void loop() {
  static int currentLED = 0; // Current LED index
  static unsigned long lastUpdate = 0; // Timer for LED updates
  const unsigned long delayTime = 200; // Delay between LED changes

  // Game loop
  if (gameRunning) {
    // Calculate remaining time
    unsigned long elapsedTime = millis() - startTime;
    unsigned long remainingTime = (gameDuration - elapsedTime) / 1000; // Convert to seconds
    
    // Check if the game timer has expired
    if (elapsedTime >= gameDuration) {
      gameRunning = false;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Game Over!");
      lcd.setCursor(0, 1);
      lcd.print("Score: ");
      lcd.print(score);
      delay(3000);
      
      // Check for high score
      if (score > highScore) {
        highScore = score;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("New Highscore!");
        lcd.setCursor(0, 1);
        lcd.print("Congrats!");
        delay(3000);
      }
      
      // Display high score
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("High Score: ");
      lcd.print(highScore);
      delay(3000);
      
      // Reset game
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Press Joystick");
      lcd.setCursor(0, 1);
      lcd.print("to Start!");
      while (digitalRead(swpin) == HIGH) {
        // Wait for user input
      }
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Starting Game...");
      delay(2000);
      lcd.clear();
      score = 0;
      startTime = millis();
      gameRunning = true;
      return;
    }

    // LED chaser logic
    if (millis() - lastUpdate >= delayTime) {
      lastUpdate = millis();
      
      // Turn off all LEDs
      for (int i = 0; i < 9; i++) {
        digitalWrite(ledPins[i], LOW);
      }
      
      // Update current LED
      digitalWrite(ledPins[currentLED], HIGH);
      
      // Check for joystick button press at middle LED
      if (currentLED == 4 && digitalRead(swpin) == LOW) {
        score++; // Increment score
      }
      
      // Update LED index based on direction
      if (direction) {
        currentLED++;
        if (currentLED >= 8) direction = false; // Change direction at end
      } else {
        currentLED--;
        if (currentLED <= 0) direction = true; // Change direction at start
      }
    }
    
    // Update LCD with score and timer
    lcd.setCursor(0, 0);
    lcd.print("Score: ");
    lcd.print(score);
    lcd.setCursor(0, 1);
    lcd.print("Time: ");
    lcd.print(remainingTime);
    lcd.print("s ");
  }
}
  




















//version1
//#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
//
//// LCD configuration
//LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16x2 display
//
//// Pin definitions
//const int ledPins[] = {3, 4, 5, 6, 7, 8, 9, 10, 11}; // Pins for 9 LEDs
//const int swpin = 2;
//
//// Variables
//int score = 0;
//bool direction = true; // true = right to left, false = left to right
//
//void setup() {
//  lcd.init();          // Initialize the LCD
//  lcd.backlight();     // Turn on the LCD backlight
//  pinMode(swpin, INPUT_PULLUP); // Set joystick button as input with pull-up
//  
//  // Initialize LED pins
//  for (int i = 0; i < 9; i++) {
//    pinMode(ledPins[i], OUTPUT);
//    digitalWrite(ledPins[i], LOW); // Turn all LEDs off initially
//  }
//  
//  Serial.begin(115200); // Initialize serial communication for debugging
//}
//
//void loop() {
//  static int currentLED = 0; // Current LED index
//  static unsigned long lastUpdate = 0; // Timer for LED updates
//  const unsigned long delayTime = 200; // Delay between LED changes
//  
//  // Check if it's time to update the LED
//  if (millis() - lastUpdate >= delayTime) {
//    lastUpdate = millis();
//    
//    // Turn off all LEDs
//    for (int i = 0; i < 9; i++) {
//      digitalWrite(ledPins[i], LOW);
//    }
//    
//    // Update current LED
//    digitalWrite(ledPins[currentLED], HIGH);
//    
//    // Check for joystick button press at middle LED
//    if (currentLED == 4 && digitalRead(swpin) == LOW) {
//      score++; // Increment score
//      lcd.clear();
//      lcd.setCursor(0, 0);
//      lcd.print("Score: ");
//      lcd.print(score);
//      Serial.println(score); // Debug output
//    }
//    
//    // Update LED index based on direction
//    if (direction) {
//      currentLED++;
//      if (currentLED >= 8) direction = false; // Change direction at end
//    } else {
//      currentLED--;
//      if (currentLED <= 0) direction = true; // Change direction at start
//    }
//  }
//}
