void moveForward();
void moveBackward();
void moveRight();
void moveLeft();
void stopMotors();
int getDistance();
int threshold = 10;

const int ML_OUT1 = 6; // left motor IN1
const int ML_OUT2 = 5; // left motor IN2
const int MR_OUT1 = 11; // right motor IN2
const int MR_OUT2 = 10; // right motor IN1

const int trigPin = 7;
const int echoPin = 3;

const int IR1_A = A0; // analog input IR left
const int IR1_D = 8; // digital input IR left
double A0_Voltage;

const int IR2_A = A1; // analog input IR right
const int IR2_D = 9; // digital input IR right
double A1_Voltage;

const int obstacleThreshold = 20; // Distance in centimeters

#define White 0
#define Black 1

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

void moveRight() {
  // Function to make the robot move forward
  analogWrite(ML_OUT1, 120);
  analogWrite(ML_OUT2, 0);
  analogWrite(MR_OUT1, 128);
  analogWrite(MR_OUT2, 0);
}

void moveLeft() {
  // Function to make the robot move forward
  analogWrite(ML_OUT1, 0);
  analogWrite(ML_OUT2, 120);
  analogWrite(MR_OUT1, 0);
  analogWrite(MR_OUT2, 128);
}

void moveBackward() {
  // Function to avoid the obstacle by turning
  analogWrite(ML_OUT1, 120);
  analogWrite(ML_OUT2, 0);
  analogWrite(MR_OUT1, 0);
  analogWrite(MR_OUT2, 128);
}

void moveForward() {
  // Function to avoid the obstacle by turning
  analogWrite(ML_OUT1, 0);
  analogWrite(ML_OUT2, 120);
  analogWrite(MR_OUT1, 128);
  analogWrite(MR_OUT2, 0);
}

void stopMotors() {
  // Function to stop both motors
  analogWrite(ML_OUT1, 0);
  analogWrite(ML_OUT2, 0);
  analogWrite(MR_OUT1, 0);
  analogWrite(MR_OUT2, 0);
}

void avoidObstacle() {
  moveLeft();
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
  // Read IR sensor values
  int distance = getDistance();
  int valueIR1_A = analogRead(IR1_A);
  bool valueIR1_D = digitalRead(IR1_D);
  A0_Voltage = (double)(valueIR1_A * (double)5 / 1024);

  int valueIR2_A = analogRead(IR2_A);
  bool valueIR2_D = digitalRead(IR2_D);
  A1_Voltage = (double)(valueIR2_A * (double)5 / 1024);

  //analogWrite(ML_OUT1, 0); //2r
  //analogWrite(ML_OUT2, 92); //1r
  //analogWrite(MR_OUT1, 128); //3l
  //analogWrite(MR_OUT2, 0); //4l

  // Check for obstacle and adjust robot's movement

  int frontDistance = getDistance(); // Distance in front of the robot

 if (distance < obstacleThreshold) {
    avoidObstacle();
  } else {
    // Continue forward if no obstacle detected
    moveForward();
  }

  if (frontDistance > threshold) {
    moveForward();
  } else {
      moveRight();
    }
  delay(10);

  if (valueIR1_D == Black && valueIR2_D == White){ //1=left 2=right
  moveLeft();
  }
  else if (valueIR1_D == White && valueIR2_D == Black){ //moveforward
  moveRight();
  }
  else if (valueIR1_D == White && valueIR2_D == White){ //avoidObstacle
  moveForward();
  }
  else if (valueIR1_D == Black && valueIR2_D == Black){ //avoidObstacle
  moveLeft();
  }
  else if (distance < obstacleThreshold)
  moveLeft();
  else {
  stopMotors();
  }
  delay(10);

}