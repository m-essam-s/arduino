#include <LiquidCrystal.h>

#define rightButtonPin 9
#define leftButtonPin 10
#define motorPin1 7
#define motorPin2 6

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(rightButtonPin, INPUT_PULLUP);
    pinMode(leftButtonPin, INPUT_PULLUP);

    lcd.begin(2, 16);
    stopMotor();
    lcd.setCoursor(0, 0);
    lcd.print("no motion    ");
}

void loop()
{
    if (digitalRead(rightButtonPin) == HIGH)
    {
        delay(300);
        moveRight();
    }
    else if (digitalRead(leftButtonPin) == HIGH)
    {
        delay(300);
        moveLeft() :
    }
    else
    {
        delay(300);
        stopMotor();
    }
}

moveRight()
{
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.pring("moving right")
}
moveLeft()
{
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.pring("moving left")
}
stopMotor()
{
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.pring("no motion")
}
