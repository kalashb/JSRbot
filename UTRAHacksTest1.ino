const int IR1_A = A0; // analog input IR left
const int IR1_D = 8; // digital input IR left
double A0_Voltage;
double A1_Voltage;

const int IR2_A = A1; // analog input IR right
const int IR2_D = 9; // digital input IR right

const int M_IN1 = 2; // left motor IN1
const int M_IN2 = 3; // left motor IN2
const int M_IN3 = 4; // right motor IN2
const int M_IN4 = 5; // right motor IN1

const int trigPin = 6;
const int echoPin = 7;

const int obstacleThreshold = 10; // Distance in centimeters

#define White 0
#define Black 1

void setup() {
  // Set motor control pins to outputs
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  
  // Set up ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void setup() {
Serial.begin(9600);
pinMode (IR1_A, INPUT);
pinMode (IR1_D, INPUT);

}

void loop() {
  // Read distance from ultrasonic sensor
  int distance = getDistance();

  // Check for obstacle and adjust robot's movement
  if (distance < obstacleThreshold) {
    avoidObstacle();
  } else {
    // Continue forward if no obstacle detected
    moveForward();
  }
}

int getDistance() {
  // Function to get distance from ultrasonic sensor

  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the pulse duration from the echo pin
  long duration = pulseIn(echoPin, HIGH);

  // Convert the duration to distance in centimeters
  int distance = duration * 0.034 / 2;

  return distance;
}

int valueIR1_A;
bool valueIR1_D;
int valueIR2_A;
bool valueIR2_D;

void loop() {
valueIR1_A = analogRead(IR1_A); // reads the analog input from the IR distance sensor
valueIR1_D = digitalRead(IR1_D);// reads the digital input from the IR distance sensor
A0_Voltage = (double)(valueIR1_A * (double) 5 / 1024);

valueIR2_A = analogRead(IR2_A); // reads the analog input from the IR distance sensor
valueIR2_D = digitalRead(IR2_D);// reads the digital input from the IR distance sensor
A1_Voltage = (double)(valueIR2_A * (double) 5 / 1024);


if (IR1_D == Black && IR2_D == White){
digitalWrite(M_IN1, LOW);
digitalWrite(M_IN2, HIGH);
digitalWrite(M_IN3, LOW);
digitalWrite(M_IN4, HIGH);
}
else if (IR1_D == White && IR2_D == Black){ //moveforward
digitalWrite(M_IN1, HIGH);
digitalWrite(M_IN2, LOW);
digitalWrite(M_IN3, HIGH);
digitalWrite(M_IN4, LOW);
}
else if (IR1_D == White && IR2_D == White){ //avoidObstacle
digitalWrite(M_IN1, HIGH);
digitalWrite(M_IN2, LOW);
digitalWrite(M_IN3, LOW);
digitalWrite(M_IN4, HIGH);
}
Serial.print(" Analog = "); 
Serial.print(A0_Voltage);
Serial.print("\t Digital ="); 
Serial.println(valueIR1_D);
Serial.print("\n Analog = "); 
Serial.print(A1_Voltage);
Serial.print("\t Digital ="); 
Serial.println(valueIR2_D);
delay(500);
}