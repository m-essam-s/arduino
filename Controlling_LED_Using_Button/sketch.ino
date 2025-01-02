#define button 5 // Button pin
#define led 13 // LED pin

void seteup() {
    pinMode(button, INPUT);
    pinMode(led, OUTPUT);
}

void loop() {
    if (digitalRead(button) == HIGH) {
        delay(1000);
        digitalWrite(led, HIGH);
    } else { 
        delay(1000);
        digitalWrite(led, LOW);
    }
}