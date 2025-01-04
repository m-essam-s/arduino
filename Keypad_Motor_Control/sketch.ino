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

byte rowPins[ROWS] = {6, 7, 8, 9};
byte colPins[COLS] = {2, 3, 4, 5};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Define the pins for the motor
int motor1Pin1 = 10;
int motor1Pin2 = 11;
int motor2Pin1 = 12;
int motor2Pin2 = 13;

void setup() {
    // Set the motor pins as output
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);

    stopMotors();
}

void loop() {
    char key = keypad.getKey();
    switch (key){
    case 'A':
        moveForward();
        break;
    case 'B':
        moveBackward();
        break;
    case 'C':
        moveRight();
        break;
    case 'D':
        moveLeft();
        break;
    
    default:
        stopMotors();
        break;
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

