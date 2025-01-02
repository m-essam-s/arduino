#include <Keypad.h>

// Define the rows and columns of the keypad

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'}, // use A for forward
  {'4', '5', '6', 'B'}, // use B for backward
  {'7', '8', '9', 'C'}, // use C for right
  {'*', '0', '#', 'D'}  // use D for left
};

byte rowPins[ROWS] = {5, 6, 7, 8};
byte colPins[COLS] = {2, 3, 4};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Define the pins for the motor

int motor1Pin1 = 9;
int motor1Pin2 = 10;
int motor2Pin1 = 11;
int motor2Pin2 = 12;

void setup() {
    // Set the motor pins as output
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);

    // Set the motor pins to low
    digitalWrite(motor1Pin1, LOW);
}

void loop() {
    char key = keypad.getKey();

    if (key == 'A') {
        moveForward();
    } else if (key == 'B') {
        moveBackward();
    } else if (key == 'C') {
        moveRight();
    } else if (key == 'D') {
        moveLeft();
    } else {
        stopMotors();
    } 
}

void moveForward() {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
}

void moveBackward() {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
}

void moveRight() {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
}

void moveLeft() {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
}

void stopMotors() {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
}

