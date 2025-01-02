#include <LiquidCrystal.h>

#define trigPin 9
#define echoPin 10
#define motorPin1 2
#define motorPin2 3

int safeDistance = 20;

const int rs = 12, en 11, d4 5, d5 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(motorPin1, OUTPUT);
    pinMode (motorPin2, OUTPUT);
    lcd.begin(16,2);
    stopMotors();
}

void loop() {
    long duration, distance;
    // Clear the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds (2);
    // Set the trigPin on HIGH for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Read the echoPin, and calculate the distance in cm
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    lcd.setCursor(0, 0);
    lcd.print("Distance: ");
    lcd.setCursor (10, 0);
    lcd.print(distance);
    lcd.setCursor (13, 0);
    lcd.println("cm");
    // Object avoidance logic
    if (distance > safeDistance) {
        // Move forward if safe
        moveForward();
    } else {
        // Stop if object is too close
        stopMotors();
        delay(1000); // wait for a second
    }
    delay(100);
}

void moveForward() {
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Moving forward ");
}
void stopMotors() {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Motors stopped ");
}