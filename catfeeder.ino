#include <Servo.h>

// Define ultrasonic sensor pins
const int trigPin = 9;
const int echoPin = 10;

// Define servo motor pin
Servo foodServo;
const int servoPin = 6;

// Define timing variables
unsigned long lastSensorCheckTime = 0;  // Store the last sensor check time
bool sensorDisabled = false;            // Flag to check if the sensor is disabled
const unsigned long sensorDelayTime = 500;  // 3 minutes in milliseconds (180,000 ms)

// Ultrasonic sensor function to measure distance (in inches)
long readUltrasonicDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.0133 / 2; // inches
  return distance;
}

// Setup function
void setup() {
  // Initialize servo
  foodServo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Start serial communication
  Serial.begin(9600);
}

// Main loop
void loop() {
  // Check current time
  unsigned long currentTime = millis();
  
  // If 3 minutes have passed since the sensor was disabled, enable the sensor again
  if (sensorDisabled && (currentTime - lastSensorCheckTime >= sensorDelayTime)) {
    sensorDisabled = false;  // Re-enable the ultrasonic sensor after 3 minutes
  }

  // If the sensor is not disabled, proceed to check the distance
  if (!sensorDisabled) {
    // Check distance using the ultrasonic sensor
    long distance = readUltrasonicDistance();

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" inches");

    // If the distance is less than 10 inches, activate the servo
    if (distance < 6) {
      foodServo.write(180); // Rotate servo to 180 degrees to dispense
      delay(500);           // Spin for 0.5 seconds
      foodServo.write(0);   // Return servo to original position
      delay(700);           // Short pause

      // Disable the sensor and store the current time
      sensorDisabled = true;          // Disable the ultrasonic sensor for 3 minutes
      lastSensorCheckTime = millis(); // Record the time when the servo was activated
    }
  }

  delay(50); // Small delay to prevent overloading the loop
}
