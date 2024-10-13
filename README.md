# Automated Cat Feeding System using Arduino Uno

This project is an automated cat feeder built using Arduino Uno, an ultrasonic sensor, and a servo motor. The feeder detects the presence of a cat when it comes near the feeder and dispenses food accordingly. The sensor is temporarily disabled after each dispensing cycle to prevent overfeeding.

## Components

- **Arduino Uno**: Controls the system.
- **Ultrasonic Sensor (HC-SR04)**: Detects the proximity of the cat.
- **Servo Motor**: Dispenses food when triggered.
- **Breadboard and Jumper Wires**: Used for connections.

## How It Works

1. **Ultrasonic Sensor**: The ultrasonic sensor checks the distance in front of the feeder. If a cat is detected within 6 inches, it triggers the feeder.
2. **Servo Motor**: The servo motor rotates to release food for 0.5 seconds and then returns to its original position.
3. **Cooldown Period**: To prevent overfeeding, the sensor is disabled for 3 minutes after each feed. After this period, it will be re-enabled to detect the next approach.

## Circuit Diagram

1. **Ultrasonic Sensor Connections**:
   - Trig pin: Digital pin 9
   - Echo pin: Digital pin 10
   - VCC and GND: Connected to 5V and GND, respectively.

2. **Servo Motor Connection**:
   - Signal pin: Digital pin 6
   - Power and GND: Connected to 5V and GND.

## Code Overview

The code is organized as follows:

- **Pin Definitions**: Defines the pins for the ultrasonic sensor and servo motor.
- **Functions**:
  - `readUltrasonicDistance()`: Measures the distance to detect if the cat is nearby.
  - `setup()`: Initializes the servo motor, pins, and serial communication.
  - `loop()`: Continuously checks the distance, dispenses food if the cat is close, and enables a cooldown period after each feeding cycle.

## Code Explanation

```cpp
const int trigPin = 9;
const int echoPin = 10;
Servo foodServo;
const int servoPin = 6;
const unsigned long sensorDelayTime = 180000; // Delay time for sensor cooldown in milliseconds
```

- Defines the pins and initializes timing variables.

```cpp
long readUltrasonicDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.0133 / 2; // Convert to inches
  return distance;
}
```

- Measures the distance using the ultrasonic sensor.

```cpp
void loop() {
  if (!sensorDisabled) {
    long distance = readUltrasonicDistance();
    if (distance < 6) {
      foodServo.write(180);
      delay(500);
      foodServo.write(0);
      delay(700);
      sensorDisabled = true;
      lastSensorCheckTime = millis();
    }
  }
}
```

- Checks the distance, dispenses food if within range, and enables the cooldown timer.

## Dependencies

This project requires the Servo library, which comes pre-installed with the Arduino IDE.

## Usage

1. Assemble the circuit as per the above circuit diagram.
2. Upload the code to the Arduino Uno using the Arduino IDE.
3. Place the feeder where the cat can approach it comfortably.
4. The system will dispense food when the cat is detected.

## License

This project is open-source and free to use and modify.
