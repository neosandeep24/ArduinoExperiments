#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include <Servo.h> 

#define FIREBASE_HOST "ENTER YOUR FIREBASE HOST WILL BE LIKE ------.firebaseio.com"
#define WIFI_SSID "YOUR WIFI NAME"
#define WIFI_PASSWORD "YOUR WIFI PASSWORD"
#define FIREBASE_Authorization_key "YOUR AUTHORIZATION KEY"

FirebaseData firebaseData;
FirebaseJson json;

unsigned long presentTime1 = 0, presentTime2 = 0;
unsigned long previousTime1 = 0, previousTime2 = 0;
int resultTime1, resultTime2;
int f1 = 0, f2 = 0;
int rate = 10; // per 1 second
int amount1, amount2;
String filled = "Filled";
String empty = "Empty";

Servo gateServo;
int servoPin = 14; 

void setup() {
  Serial.begin(9600);
  delay(10);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  Serial.print("Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_Authorization_key);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  gateServo.attach(servoPin);
  Serial.println("Initializing...");
  delay(10);
}

void loop() {
  if (digitalRead(4) == LOW) {
    Serial.println("\nP1:Filled4");
    Firebase.setString(firebaseData, "PS1", filled);
    presentTime1 = millis();
    f1 = 1;
    resultTime1 = (presentTime1 - previousTime1) / 1000;
  }
  if (digitalRead(4) == HIGH) {
    if (f1 == 1) {
      amount1 = resultTime1 * rate;
      Serial.print("\nP1 Amount:");
      Serial.print(amount1);
      previousTime1 = presentTime1;
    }
    f1 = 0;
    Serial.println("\nP1:Empty4");
    Firebase.setString(firebaseData, "PS1", empty);
  }
  if (digitalRead(5) == LOW) {
    Serial.println("\nP2:Filled5");
    Firebase.setString(firebaseData, "PS2", filled);
    presentTime2 = millis();
    f2 = 1;
    resultTime2 = (presentTime2 - previousTime2) / 1000;
  }
  if (digitalRead(5) == HIGH) {
    if (f2 == 1) {
      amount2 = resultTime2 * rate;
      Serial.print("\nP2 Amount:");
      Serial.print(amount2);
      previousTime2 = presentTime2;
    }
    f2 = 0;
    Serial.println("\nP2:Empty5");
    Firebase.setString(firebaseData, "PS2", empty);
  }

  Firebase.setFloat(firebaseData, "PS1Bill", amount1);
  Firebase.setFloat(firebaseData, "PS2Bill", amount2);
  
//any ir sensor detects nothing then free parking slot is available

  if (digitalRead(4) == LOW && digitalRead(5) == LOW) {
    openGate();
  } else {
    closeGate();
  }
}

void openGate() {
  gateServo.write(150); // Adjust the angle to open the gate
  delay(2000);
}

void closeGate() {
  gateServo.write(0); // Adjust the angle to close the gate
}
