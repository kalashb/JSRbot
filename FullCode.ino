void moveForward();
void moveBackward();
void moveRight();
void moveLeft();
void stopMotors();
int getDistance();
int rnd;
int threshold = 10;
bool wallFollow = false;

const int ML_OUT1 = 6;   // left motor IN1
const int ML_OUT2 = 5;   // left motor IN2
const int MR_OUT1 = 11;  // right motor IN2
const int MR_OUT2 = 10;  // right motor IN1

const int trigPin = 7;
const int echoPin = 3;

const int IR1_A = A0;  // analog input IR left
const int IR1_D = 8;   // digital input IR left
double A0_Voltage;

const int IR2_A = A1;  // analog input IR right
const int IR2_D = 9;   // digital input IR right
double A1_Voltage;

const int obstacleThreshold = 10;  // Distance in centimeters

#define White 1
#define Black 0

void setup() {
  // Set motor control pins to outputs
  pinMode(ML_OUT1, OUTPUT);
  pinMode(ML_OUT2, OUTPUT);
  pinMode(MR_OUT1, OUTPUT);
  pinMode(MR_OUT2, OUTPUT);

  // Set up ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(IR1_A, INPUT);
  pinMode(IR1_D, INPUT);

  pinMode(IR2_A, INPUT);
  pinMode(IR2_D, INPUT);

  getDistance();
  delay(10);
  // Initialize serial communication for debugging
  Serial.begin(9600);
}

int valueIR1_A;
bool valueIR1_D;
int valueIR2_A;
bool valueIR2_D;

void moveForward() {
  // Function to make the robot move forward
  digitalWrite(ML_OUT1, 92);
  digitalWrite(ML_OUT2, 0);
  digitalWrite(MR_OUT1, 128);
  digitalWrite(MR_OUT2, 0);
}

void moveBackward() {
  // Function to make the robot move forward
  digitalWrite(ML_OUT1, 0);
  digitalWrite(ML_OUT2, 92);
  digitalWrite(MR_OUT1, 0);
  digitalWrite(MR_OUT2, 128);
}

void moveRight() {
  // Function to avoid the obstacle by turning
  digitalWrite(ML_OUT1, 92);
  digitalWrite(ML_OUT2, 0);
  digitalWrite(MR_OUT1, 0);
  digitalWrite(MR_OUT2, 128);
}

void moveLeft() {
  // Function to avoid the obstacle by turning
  digitalWrite(ML_OUT1, 0);
  digitalWrite(ML_OUT2, 92);
  digitalWrite(MR_OUT1, 128);
  digitalWrite(MR_OUT2, 0);
}

void stopMotors() {
  // Function to stop both motors
  digitalWrite(ML_OUT1, 0);
  digitalWrite(ML_OUT2, 0);
  digitalWrite(MR_OUT1, 0);
  digitalWrite(MR_OUT2, 0);
}

void avoidObstacle() {
  moveRight();
  delay(500);
}

int getDistance() {
  // Function to get distance from ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.0343 / 2;
  return distance;
}

void loop() {
  // Read distance from ultrasonic sensor
  int distance = getDistance();
  // Read IR sensor values
  int valueIR1_A = analogRead(IR1_A);
  bool valueIR1_D = digitalRead(IR1_D);
  A0_Voltage = (double)(valueIR1_A * (double)5 / 1024);

  int valueIR2_A = analogRead(IR2_A);
  bool valueIR2_D = digitalRead(IR2_D);
  A1_Voltage = (double)(valueIR2_A * (double)5 / 1024);

  // Check for obstacle and adjust robot's movement
  if (distance < obstacleThreshold) {
    avoidObstacle();
  } else {
    // Continue forward if no obstacle detected
    moveForward();
  }
  int leftDistance = getDistance();   // Distance to the left wall
  int frontDistance = getDistance();  // Distance in front of the robot

  if (frontDistance > threshold) {  // left hand rule + wall following
    moveForward();
  } else {
    if (leftDistance > threshold) {
      moveLeft();
    } else {
      moveRight();
    }
  }
  if (!wallFollow) {  // highly possible we need to remove this bit, part of
                      // pledge algorithm but it compiles
    // Turn in one direction until a path is found
    moveLeft();
    while (getDistance() < 10) {
      delay(100);
    }
    wallFollow = true;
  } else {
    // Follow the wall
    moveForward();
    if (getDistance() < 10) {
      moveRight();
      delay(500);
    }
  }

  delay(100);

  if (valueIR1_D == Black && valueIR2_D == White) {         // 1=left 2=right
    analogWrite(ML_OUT1, 0);                                // motor1pin1 left
    analogWrite(ML_OUT2, 92);                               // motor1pin2 left
    analogWrite(MR_OUT1, 0);                                // motor2pin2 right
    analogWrite(MR_OUT2, 128);                              // motor2pin1 right
  } else if (valueIR1_D == White && valueIR2_D == Black) {  // moveforward
    analogWrite(ML_OUT1, 92);
    analogWrite(ML_OUT2, 0);
    analogWrite(MR_OUT1, 128);
    analogWrite(MR_OUT2, 0);
  } else if (valueIR1_D == White && valueIR2_D == White) {  // avoidObstacle
    analogWrite(ML_OUT1, 0);
    analogWrite(ML_OUT2, 92);
    analogWrite(MR_OUT1, 128);
    analogWrite(MR_OUT2, 0);
  } else {
    rnd = (int)(rand() % 2);
    analogWrite(ML_OUT1, 0);
    analogWrite(ML_OUT2, 0);
    analogWrite(MR_OUT1, 0);
    analogWrite(MR_OUT2, 0);
    delay(920);
    if (rnd == 0) {
      analogWrite(ML_OUT1, 0);   // motor1pin1 left
      analogWrite(ML_OUT2, 92);  // motor1pin2 left
      analogWrite(MR_OUT1, 0);   // motor2pin2 right
      analogWrite(MR_OUT2, 0);   // motor2pin1 right
      delay(100);
      analogWrite(ML_OUT1, 92);
      analogWrite(ML_OUT2, 0);
      analogWrite(MR_OUT1, 0);
      analogWrite(MR_OUT2, 128);
      delay(100);
    } else {
      analogWrite(ML_OUT1, 0);
      analogWrite(ML_OUT2, 0);
      analogWrite(MR_OUT1, 128);
      analogWrite(MR_OUT2, 0);
      delay(100);
      analogWrite(ML_OUT1, 92);
      analogWrite(ML_OUT2, 0);
      analogWrite(MR_OUT1, 0);
      analogWrite(MR_OUT2, 128);
      delay(100);
    }
  }
  delay(10);
}