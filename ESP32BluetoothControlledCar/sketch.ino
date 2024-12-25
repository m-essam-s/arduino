#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// Motor control pins for Channel A (Motor Pair 1)
#define ENA 14 // Speed control (PWM)
#define IN1 27 // Direction 1
#define IN2 26 // Direction 2

// Motor control pins for Channel B (Motor Pair 2)
#define ENB 13 // Speed control (PWM)
#define IN3 25 // Direction 1
#define IN4 33 // Direction 2

int motorSpeed = 255; // Set initial motor speed (0 - 255)

void setup(){
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);

    SerialBT.begin("ESP32_Essam'sCar"); 
    stopMotors();                       // Make sure motors are stopped at the start
}

void loop(){
    if (SerialBT.available()){
        char command = SerialBT.read(); // Read the incoming command
        handleCommand(command);
    }
}

// Function to handle the received command
void handleCommand(char command){
    switch (command){
    case 'F': // Forward
        forward();
        break;
    case 'B': // Backward
        backward();
        break;
    case 'L': // Left
        turnLeft();
        break;
    case 'R': // Right
        turnRight();
        break;
    case 'S': // Stop
        stopMotors();
        break;
    default: // Stop if an unknown command is received
        stopMotors();
        break;
    }
}

void forward(){
    analogWrite(ENA, motorSpeed); // Set speed for left motor
    analogWrite(ENB, motorSpeed); // Set speed for right motor
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void backward(){
    analogWrite(ENA, motorSpeed);
    analogWrite(ENB, motorSpeed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void turnLeft(){
    analogWrite(ENA, motorSpeed);
    analogWrite(ENB, motorSpeed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void turnRight(){
    analogWrite(ENA, motorSpeed);
    analogWrite(ENB, motorSpeed);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void stopMotors(){
    analogWrite(ENA, 0); // Stop left motor
    analogWrite(ENB, 0); // Stop right motor
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}
