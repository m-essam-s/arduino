#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
    lcd.begin(16, 2);
    lcd.print("Hello, World!");
    delay(1000);
}

void loop() {

    for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
        lcd.scrollDisplayLeft();
        delay(150);
    }
    
    for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
        lcd.scrollDisplayRight();
        delay(150);
    }

    for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
        lcd.scrollDisplayLeft();
        delay(150);
    }
    delay(1000);
}
