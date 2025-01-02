#include <LiquidCrystal.h>
#include <Keypad.h>

const int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte ROWS = 4;
const byte COLS = 3;
char kyes[ROWS][COLS]={
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
}

byte rowPins[ROWS] = {5, 6, 7, 8}
byte colPins[COLS] = {2, 3, 4}

Keypad keypad = Keypade(makekeymap(keys), rowPins, colPins, ROWS, COLS );

char Pass [6];
char storedPass [] = "123456"

int i = 0;
int count = 0;

void setup(){
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Enter The Pass");
    lcd.setCursor(0, 1);
}

void loop(){
    char key = keypad.getKey();
    if (key != '#'){
        lcd.print('*');
        Pass[i] = key;
        i++;
    } else if (key == '#'){
        if (i = 6){
            for (int j = 0; j < 6; j++){
                if (Pass[j] == storedPass[j]){
                    count ++;
                }   
            }
            if (count == 6){
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Correct Pass     ");
                delay(2000);
                i = 0;
                count = 0;
                lcd.setCursor(0, 0);
                lcd.print("Enter The Pass");
                lcd.setCursor(0, 1);
            }else{
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Wrong Pass     ");
                delay(2000);
                i = 0;
                count = 0;
                lcd.setCursor(0, 0);
                lcd.print("Enter The Pass");
                lcd.setCursor(0, 1);
            }
        }else{
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Wrong Pass     ");
            delay(2000);
            i = 0;
            count = 0;
            lcd.setCursor(0, 0);
            lcd.print("Enter The Pass");
            lcd.setCursor(0, 1);
        }
    }
}