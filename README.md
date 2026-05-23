
# IR Array Line Follower Robot

A 5-sensor IR Array based autonomous line follower robot built using Arduino Uno and Adafruit Motor Shield.

## Features

- 5 IR sensor array line detection
- Automatic line recovery system
- Sharp recovery spin when line is lost
- Supports left and right sharp turns
- 4-wheel drive motor control
- Memory-based line tracking algorithm

## Components Used

- Arduino Uno
- Adafruit Motor Shield
- 5x IR Sensors
- 4 DC Motors
- Robot Chassis
- Wheels
- Battery Pack
- Jumper Wires

## Pin Configuration

| Sensor | Arduino Pin |
|---------|--------------|
| Far Left | A4 |
| Inner Left | A3 |
| Center | A2 |
| Inner Right | A1 |
| Far Right | A0 |

## Motor Mapping

| Motor Position | Shield Port |
|----------------|-------------|
| Front Left | M3 |
| Front Right | M4 |
| Rear Left | M2 |
| Rear Right | M1 |

## Algorithm

1. Read all IR sensors
2. Center sensor detects line → Move Forward
3. Left sensors detect line → Turn Left
4. Right sensors detect line → Turn Right
5. If line lost:
   - Search left if last line seen left
   - Search right if last line seen right
6. Repeat continuously

## Circuit Diagram

Circuit diagram available in `/circuit`

## Installation

1. Install Arduino IDE
2. Install AFMotor library
3. Upload `line_follower_final.ino`
4. Power robot
5. Place robot on black line

## Future Improvements

- PID control
- Adjustable speed
- Junction detection
- Maze solving
- Bluetooth monitoring

## Author

Shakin Mahmud Tanvir
Electrical and Electronics Engineering Student
Bangladesh
