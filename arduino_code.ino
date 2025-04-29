#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // RS, E, D4, D5, D6, D7

String currentWord = "";
String currentLetter = "";

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 4);
  lcd.print("Ready...");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    
    if (command.startsWith("WORD:")) {
      currentWord = command.substring(5);
      updateDisplay();
    }
    else if (command.startsWith("LETTER:")) {
      currentLetter = command.substring(7);
      updateDisplay();
    }
    else if (command.startsWith("SAVE:")) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Saved Word:");
      lcd.setCursor(0, 1);
      lcd.print(command.substring(5));
    }
    else if (command == "CLEAR") {
      currentWord = "";
      currentLetter = "";
      lcd.clear();
      lcd.print("Ready...");
    }
  }
}

void updateDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Current Word:");
  lcd.setCursor(0, 1);
  lcd.print(currentWord);
  
  lcd.setCursor(0, 2);
  lcd.print("Last Letter:");
  lcd.setCursor(0, 3);
  lcd.print(currentLetter);
}