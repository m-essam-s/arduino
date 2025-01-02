#include <LiquidCrystal.h>

#define Button 6

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup (){
    lcd.begin(16, 2);
    pinMode(Button, INPUT);
}

void loop (){
    lcd.setCrusor(0, 0);
    lcd.pfint("Hello, World!");

    if ( digitalReade(Button) == HIGH ){
        lcd.setCrusor(0, 1);
        lcd.print("Button Pressed");
        delay(200);
    } else {
        lcd.setCrusor(0, 1);
        lcd.print("Button Released");
        delay(200);
    }
}
