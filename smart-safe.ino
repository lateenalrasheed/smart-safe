
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>


LiquidCrystal_I2C lcd(0x27, 16, 2); 

const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


String correctPassword = "1234"; 
String inputPassword = "";
int attempts = 0;



void setup() {
pinMode(11, OUTPUT); 
pinMode(12, OUTPUT);
  lcd.init();
  lcd.backlight();
  resetSystem();
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == 'D') { 
      if (inputPassword.length() > 0) {
        checkPassword();
      }
    } 
    else if (key == '*') { 
      resetSystem();
    } 
    else if (key >= '0' && key <= '9') { 
      if (inputPassword.length() < 4) { 
        inputPassword += key;
        lcd.setCursor(inputPassword.length() - 1, 1);
        lcd.print('*');
      }
    }
  }
}


void checkPassword() {
  if (inputPassword == correctPassword) {
    lcd.clear();
    lcd.print("Correct password!");
    delay(2000);
    attempts = 0;
    resetSystem();
  } else {
    attempts++;
    lcd.clear();
    lcd.print("Wrong password!");
    delay(1000);
    
    if (attempts >= 2) {
      lcd.clear();
      lcd.print("Error!!!");
      tone(13,500);
    delay(1000);
    noTone(13);
    delay(500);
    tone(13,500);
    delay(1000);
    noTone(13);
    delay(500);
    tone(13,500);
    delay(1000);
    noTone(13);
    attempts = 0;
    }
    resetSystem();
  }
}

void resetSystem() {
  inputPassword = "";
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter 4 Digits:");
  lcd.setCursor(0, 1);
  lcd.print("Press D to Enter");
  delay(2000);
  lcd.clear();
  lcd.print("password:");
}







