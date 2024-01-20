const int IN_A0 = A0; // analog input
const int IN_D0 = 8; // digital input
void setup() {
Serial.begin(9600); //clockspeed 9600
pinMode (IN_A0, INPUT); 
pinMode (IN_D0, INPUT);

}
int value_A0;
bool value_D0;
void loop() {
value_A0 = analogRead(IN_A0); // reads the analog input from the IR distance sensor (0, 5)(range/bitrate = size of each bit)(size of each bit(analog) * 5/1024 = voltage)
value_D0 = digitalRead(IN_D0);// reads the digital input from the IR distance sensor {0, 5}
Serial.print(" Analog = "); 
Serial.print(value_A0);
Serial.print("\t Digital ="); 
Serial.println(value_D0);
delay(100); //milliseconds
}