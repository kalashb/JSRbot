const int M_OUT1 = 6; // left motor IN1
const int M_OUT2 = 5; // left motor IN2
const int M_OUT3 = 11; // right motor IN2
const int M_OUT4 = 10; // right motor IN1

const int trigPin = 7;
const int echoPin = 3;

const int IR1_A = A0; // analog input IR left
const int IR1_D = 8; // digital input IR left
int rnd;

double A0_Voltage;
double A1_Voltage;

const int IR2_A = A1; // analog input IR right
const int IR2_D = 9; // digital input IR right

const int obstacleThreshold = 10; // Distance in centimeters

#define White 1
#define Black 0

void setup() {
  // Set motor control pins to outputs
  pinMode(M_OUT1, OUTPUT);
  pinMode(M_OUT2, OUTPUT);
  pinMode(M_OUT3, OUTPUT);
  pinMode(M_OUT4, OUTPUT);

  // Set up ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode (IR1_A, INPUT);
  pinMode (IR1_D, INPUT);

  pinMode (IR2_A, INPUT);
  pinMode (IR2_D, INPUT);

  // Initialize serial communication for debugging
  Serial.begin(9600);
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

if (valueIR1_D == Black && valueIR2_D == White){ //1=left 2=right
analogWrite(M_OUT1, 0); //motor1pin1 left
analogWrite(M_OUT2, 92); //motor1pin2 left
analogWrite(M_OUT3, 0); //motor2pin2 right
analogWrite(M_OUT4, 128); //motor2pin1 right
}
else if (valueIR1_D == White && valueIR2_D == Black){ //moveforward
analogWrite(M_OUT1, 92);
analogWrite(M_OUT2, 0);
analogWrite(M_OUT3, 128);
analogWrite(M_OUT4, 0);
}
else if (valueIR1_D == White && valueIR2_D == White){ //avoidObstacle
analogWrite(M_OUT1, 0);
analogWrite(M_OUT2, 92);
analogWrite(M_OUT3, 128);
analogWrite(M_OUT4, 0);
}
else {rnd = (int)(rand()%2);
analogWrite(M_OUT1, 0);
analogWrite(M_OUT2, 0);
analogWrite(M_OUT3, 0);
analogWrite(M_OUT4, 0);
delay(920);
if (rnd == 0){
analogWrite(M_OUT1, 0); //motor1pin1 left
analogWrite(M_OUT2, 92); //motor1pin2 left
analogWrite(M_OUT3, 0); //motor2pin2 right
analogWrite(M_OUT4, 0); //motor2pin1 right
delay(100);
analogWrite(M_OUT1, 92);
analogWrite(M_OUT2, 0);
analogWrite(M_OUT3, 0);
analogWrite(M_OUT4, 128);
delay(100);
}
else {
analogWrite(M_OUT1, 0);
analogWrite(M_OUT2, 0);
analogWrite(M_OUT3, 128);
analogWrite(M_OUT4, 0);
delay(100);
analogWrite(M_OUT1, 92);
analogWrite(M_OUT2, 0);
analogWrite(M_OUT3, 0);
analogWrite(M_OUT4, 128);
delay(100);
}}


Serial.print(" Analog = "); 
Serial.print(A0_Voltage);
Serial.print("\t Digital ="); 
Serial.println(valueIR1_D);
Serial.print("\n Analog = "); 
Serial.print(A1_Voltage);
Serial.print("\t Digital ="); 
Serial.println(valueIR2_D);
delay(20);
}