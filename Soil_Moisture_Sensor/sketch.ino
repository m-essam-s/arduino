#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int moisturePin = A0;
const int relayPin = 7;
const int dryThreshold = 400;
const int wetThreshold = 700;

void setup (){
    pinMode(relayPin, OUTPUT);
    pinMode(moisturePin, INPUT);
    digitalWrite(relayPin, HIGH);
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Irrigation System");
}

void loop(){
    int moistureValue = analogRead(moisturePin);
    int humidityPercent = map(moistureValue, dryThreshold, wetThreshold, 100, 0);
    humidityPercent = constrain(humidityPercent, 0, 100);
    lcd.setCursor(0, 1);
    lcd.print(humidityPercent);
    lcd.print("%       ");

    if (humidityPercent < 30){
        lcd.setCursor(12, 1);
        lcd.print("ON");
        digitalWrite(relayPin, HIGH);
    }else if (humidityPercent > 70){
        lcd.setCursor(12, 0);
        lcd.print("OFF");
        digitalWrite(relayPin, LOW);
    }
    delay(2000);
}