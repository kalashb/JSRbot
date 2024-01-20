const int IR1_A = A0; // analog input IR left
const int IR1_D = 8; // digital input IR left
double A0_Voltage;

const int IR2_A = A1; // analog input IR right
const int IR2_D = 9; // digital input IR right

const int M_IN1 = 2; // left motor IN1
const int M_IN2 = 3; // left motor IN2
const int M_IN3 = 4; // right motor IN2
const int M_IN4 = 5; // right motor IN1

#define White 1
#define Black 0

void setup() {
Serial.begin(9600);
pinMode (IR1_A, INPUT);
pinMode (IR1_D, INPUT);

}
int valueIR1_A;
bool valueIR1_D;
void loop() {
valueIR1_A = analogRead(IR1_A); // reads the analog input from the IR distance sensor
valueIR1_D = digitalRead(IR1_D);// reads the digital input from the IR distance sensor
A0_Voltage = (double)(valueIR1_A * (double) 5 / 1024);

if (IR1_D == Black && IR2_D == White){
digitalWrite(M_IN1, 0);
digitalWrite(M_IN2, 1);
digitalWrite(M_IN3, 0);
digitalWrite(M_IN4, 1);
}
else if (IR1_D == White && IR2_D == Black){
digitalWrite(M_IN1, 1);
digitalWrite(M_IN2, 0);
digitalWrite(M_IN3, 1);
digitalWrite(M_IN4, 0);
}
else if (IR1_D == White && IR2_D == White){
digitalWrite(M_IN1, 1);
digitalWrite(M_IN2, 0);
digitalWrite(M_IN3, 0);
digitalWrite(M_IN4, 1);
}
Serial.print(" Analog = "); 
Serial.print(A0_Voltage);
Serial.print("\t Digital ="); 
Serial.println(valueIR1_D);
delay(100);
}