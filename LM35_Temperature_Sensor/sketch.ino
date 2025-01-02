#include <LiquidCrystal.h>

#define Sensor ΑΘ

int value = 0;
float volt = 0;
int temp = 0;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd (rs, en, d4, d5, d6, d7);

void setup() {
    lcd.begin(16, 2);
}

void loop() {
    value = analogRead (Sensor);
    volt = (5.0 / 1023.0) * value;
    delay(500);
    temp = volt / 0.01;
    lcd.setCursor(0, 0);
    lcd.print("Temp = ");
    lcd.setCursor(8, 0);
    lcd.print(temp);
}
