//Note : Each Sensor is different you have to calibrate for your own sensor
//How ? First read the analog values(In arduino ide in the top right corner there is a search icon clicking that will give analog values) then write action based on that 
//For example when i bend the flex sensor the analog value changed to > 850 so I added an action to it like light a bulb
//If any code is not working please feel free to change it based on your need
//ALL THE CODES ARE AVAILABLE IN ORDER IN THE SAME FILE ITSELF 1)BULB 2)Display 3)Bulb with Display 4)Bulbs with Display 




// 1 bulb
//const int flexPin = A0;
//const int ledPin = 13;
//
//void setup()
//{
//  Serial.begin(9600);
//  pinMode(ledPin, OUTPUT);
//}
//
//void loop()
//{
//  int flexValue;
//  flexValue = analogRead(flexPin);
//  Serial.print("sensor: ");
//  Serial.println(flexValue);
//  
//  if(flexValue > 850)
//    digitalWrite(ledPin, HIGH);
//  else
//    digitalWrite(ledPin, LOW);
//    
//  delay(20);
//}





//just i2c

//#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
//
//const int flexPin = A0;
//
//// LCD
//LiquidCrystal_I2C lcd(0x27, 16, 2);
//
//// Variables to track analog value changes
//int previousFlexValue = 0;
//
//void setup()
//{
//  Serial.begin(9600);
//  
//  // Initialize LCD
//  lcd.init();
//  lcd.backlight();
//  
//  // Read initial value
//  previousFlexValue = analogRead(flexPin);
//  
//  // Display initial message
//  lcd.setCursor(0, 0);
//  lcd.print("System Ready");
//  delay(1000);
//}
//
//void loop()
//{
//  int flexValue = analogRead(flexPin);
//  int difference = flexValue - previousFlexValue;
//  
//  // Check if analog value dropped by more than 300
//  if(difference > 300)
//  {
//    // Display "NO FLEX" on LCD
//    lcd.clear();
//    lcd.setCursor(0, 0);
//    lcd.print("   NO FLEX   ");
//    lcd.setCursor(0, 1);
//    lcd.print("              ");
//    
//    Serial.println("Flex dropped! NO FLEX");
//  }
//  
//  // Check if analog value increased by more than 300
//  if(difference <  -300)
//  {
//    // Display "FLEX ALERT" on LCD
//    lcd.clear();
//    lcd.setCursor(0, 0);
//    lcd.print("  FLEX ALERT  ");
//    lcd.setCursor(0, 1);
//    lcd.print("              ");
//    
//    Serial.println("Flex increased! FLEX ALERT");
//  }
//  
//  // Display current values on Serial Monitor
//  Serial.print("Sensor: ");
//  Serial.print(flexValue);
//  Serial.print(" | Previous: ");
//  Serial.print(previousFlexValue);
//  Serial.print(" | Diff: ");
//  Serial.println(difference);
//  
//  // Update previous value
//  previousFlexValue = flexValue;
//  
//  delay(100);
//}
//
//
//
//
//

// 1 bulb with i2c
//#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
//
//const int flexPin = A0;
//const int bulbPin = 13;
//
//// LCD
//LiquidCrystal_I2C lcd(0x27, 16, 2);
//
//// Variables to track analog value changes
//int previousFlexValue = 0;
//unsigned long bulbOnTime = 0;
//bool bulbIsOn = false;
//
//void setup()
//{
//  Serial.begin(9600);
//  
//  // Set bulb pin as output
//  pinMode(bulbPin, OUTPUT);
//  digitalWrite(bulbPin, LOW);
//  
//  // Initialize LCD
//  lcd.init();
//  lcd.backlight();
//  
//  // Read initial value
//  previousFlexValue = analogRead(flexPin);
//  
//  // Display initial message
//  lcd.setCursor(0, 0);
//  lcd.print("System Ready");
//  delay(1000);
//}
//
//void loop()
//{
//  int flexValue = analogRead(flexPin);
//  int difference = flexValue - previousFlexValue;
//  
//  // Check if analog value dropped by more than 300
//  if(difference < -300)
//  {
//    digitalWrite(bulbPin, HIGH); // Turn bulb ON
//    bulbOnTime = millis();
//    bulbIsOn = true;
//    
//    // Display alert on LCD
//    lcd.clear();
//    lcd.setCursor(0, 0);
//    lcd.print("Flex Alert !!");
//    lcd.setCursor(0, 1);
//    lcd.print("Bulb ON");
//    
//    Serial.println("Flex dropped! Bulb ON");
//  }
//  
//  // Check if analog value increased by more than 300
//  if(difference > 300)
//  {
//    digitalWrite(bulbPin, LOW); // Turn bulb OFF
//    bulbIsOn = false;
//    
//    // Display on LCD
//    lcd.clear();
//    lcd.setCursor(0, 0);
//    lcd.print("No Flex");
//    lcd.setCursor(0, 1);
//    lcd.print("Bulb OFF");
//    
//    Serial.println("Flex increased! Bulb OFF");
//  }
//  
//  // If bulb is on and 5 seconds have passed, turn it off
//  if(bulbIsOn && (millis() - bulbOnTime >= 5000))
//  {
//    digitalWrite(bulbPin, LOW);
//    bulbIsOn = false;
//    
//    lcd.clear();
//    lcd.setCursor(0, 0);
//    lcd.print("Timeout");
//    lcd.setCursor(0, 1);
//    lcd.print("Bulb OFF");
//    
//    Serial.println("5 seconds passed! Bulb OFF");
//  }
//  
//  // Display current values on Serial Monitor
//  Serial.print("Sensor: ");
//  Serial.print(flexValue);
//  Serial.print(" | Previous: ");
//  Serial.print(previousFlexValue);
//  Serial.print(" | Diff: ");
//  Serial.println(difference);
//  
//  // Update previous value
//  previousFlexValue = flexValue;
//  
//  delay(100);
//}



//BULBS

//#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
//
//const int flexPin = A0;
//
//// LED pins array
//int leds[] = {2, 3, 4, 5, 6, 7, 8, 9};
//
//// LCD
//LiquidCrystal_I2C lcd(0x27, 16, 2);
//
//// Variables to track analog value changes
//int previousFlexValue = 0;
//
//void setup()
//{
//  Serial.begin(9600);
//  
//  // Set all LED pins as OUTPUT
//  for(int i = 0; i < 8; i++)
//  {
//    pinMode(leds[i], OUTPUT);
//    digitalWrite(leds[i], LOW);
//  }
//  
//  // Initialize LCD
//  lcd.init();
//  lcd.backlight();
//  
//  // Read initial value
//  previousFlexValue = analogRead(flexPin);
//  
//  // Display initial message
//  lcd.setCursor(0, 0);
//  lcd.print("System Ready");
//  delay(1000);
//}
//
//void loop()
//{
//  int flexValue = analogRead(flexPin);
//  int difference = flexValue - previousFlexValue;
//  
//  // Check if analog value increased by more than 300 (FLEXED)
//  if(difference < 300)
//  {
//    // Display "FLEX ALERT" on LCD
//    lcd.clear();
//    lcd.setCursor(0, 0);
//    lcd.print("  FLEX ALERT  ");
//    
//    Serial.println("Flex increased! Turning on LEDs sequentially");
//    
//    // Turn on LEDs sequentially from red to white
//    for(int i = 0; i < 8; i++)
//    {
//      digitalWrite(leds[i], HIGH);
//      delay(1000);
//    }
//  }
//  
//  // Check if analog value dropped by more than 300 (NO FLEX)
//  if(difference > -300)
//  {
//    // Display "NO FLEX" on LCD
//    lcd.clear();
//    lcd.setCursor(0, 0);
//    lcd.print("   NO FLEX   ");
//    
//    Serial.println("Flex dropped! Turning off LEDs sequentially");
//    
//    // Turn off LEDs sequentially from white to red (reverse)
//    for(int i = 7; i >= 0; i--)
//    {
//      digitalWrite(leds[i], LOW);
//      delay(1000);
//    }
//  }
//  
//  // Display current values on Serial Monitor
//  Serial.print("Sensor: ");
//  Serial.print(flexValue);
//  Serial.print(" | Previous: ");
//  Serial.print(previousFlexValue);
//  Serial.print(" | Diff: ");
//  Serial.println(difference);
//  
//  // Update previous value
//  previousFlexValue = flexValue;
//  
//  delay(100);
//}
