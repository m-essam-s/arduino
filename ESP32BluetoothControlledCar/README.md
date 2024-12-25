# ESP32 Bluetooth Controlled Car

This project demonstrates how to build a Bluetooth-controlled car using the ESP32 microcontroller, an L298 motor driver, and four DC motors (grouped into two motor pairs). You can control the car's movement using commands sent via Bluetooth.

## Features

- Forward, backward, left, right, and stop functionality.
- Bluetooth control via any serial terminal app (e.g., Bluetooth Terminal).
- Adjustable motor speed using PWM.

## Components Required

-ESP32 microcontroller
-L298 motor driver module
-4 DC motors (grouped as 2 motor pairs)
-Battery pack (e.g., 2x 3.7V batteries in series or equivalent)
-Jumper wires
-Chassis and wheels for the car

## Pin Connections

### L298 Motor Driver to Motors

- Motor Pair 1: Connect to OUT1 and OUT2.
- Motor Pair 2: Connect to OUT3 and OUT4.

### L298 Motor Driver to ESP32

| L298 Pin | ESP32 Pin |
|----------|-----------|
| ENA      | GPIO 14   |
| IN1      | GPIO 27   |
| IN2      | GPIO 26   |
| ENB      | GPIO 13   |
| IN3      | GPIO 25   |
| IN4      | GPIO 33   |

### Power Connections

- Connect the + terminal of the battery pack to the L298's 12V  pin.
- Connect the - terminal of the battery pack to the L298's GND pin.
- Connect the 5V output pin on the L298 to the VIN pin on the - ESP32.
- Connect all GND pins (L298, ESP32, and battery) together.

## Bluetooth Commands

| Command | Action   |
|---------|----------|
| F Move  | forward  |
| B Move  | backward |
| L Turn  | left     |
| R Turn  | right    |
| S Stop  | motors   |

## Usage

1. Upload the code to your ESP32.
2. Pair your phone or computer with the ESP32 via Bluetooth (name: ESP32_Essam'sCar).
3. Open a Bluetooth terminal app and connect to the ESP32.
4. Send commands (F, B, L, R, S) to control the car.

## Notes

- Adjust the motorSpeed variable to change the speed of the motors.
- Ensure all connections are secure to avoid loose wires during operation.
- For higher torque motors, ensure your battery can provide sufficient current.
