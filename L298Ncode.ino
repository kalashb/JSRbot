#include <Servo.h>

// Define Pin Connections
#define motorA1 2
#define motorA2 3
#define motorB1 4
#define motorB2 5
#define leftSensor A0
#define rightSensor A1
#define obstacleSensorTrig 6
#define obstacleSensorEcho 7
#define ledPin 8

Servo obstacleServo; // Create a servo object to control the obstacle sensor

void setup() {
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(obstacleSensorTrig, OUTPUT);
  pinMode(obstacleSensorEcho, INPUT);
  pinMode(ledPin, OUTPUT);

  obstacleServo.attach(9); // Attach servo to pin 9

  // Initialize Serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Call different functions based on the challenge courses
  basicLineFollowing();
  advancedLineFollowing();
  obstacleDetection();
  mazeNavigation();
}

void basicLineFollowing() {
  // Implement code for basic line following
  // Use line tracking sensors and motor control to follow a simple track
}

void advancedLineFollowing() {
  // Implement code for advanced line following
  // Handle sharp turns and loops using the line tracking sensors
}

void obstacleDetection() {
  // Implement code for obstacle detection and avoidance
  if (detectObstacle()) {
    avoidObstacle();
  }
}

bool detectObstacle() {
  // Use Ultrasonic Sensor to detect obstacles
  digitalWrite(obstacleSensorTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(obstacleSensorTrig, HIGH);
  delayMicroseconds(10);
  long duration = pulseIn(obstacleSensorEcho, HIGH);
  int distance = duration * 0.034 / 2;

  // Display distance for debugging
  Serial.print("Distance: ");
  Serial.println(distance);

  return (distance < 20); // Adjust threshold as needed
}

void avoidObstacle() {
  // Implement obstacle avoidance algorithm
  // Use motor control to steer away from obstacles
  digitalWrite(ledPin, HIGH); // Indicate obstacle avoidance with an LED
  delay(1000);
  digitalWrite(ledPin, LOW);
}


