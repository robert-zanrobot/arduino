int trigPin = 12;
int echoPin = 14;
long duration, disCM;
void setup() { Serial.begin (115200);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
} void loop() {
digitalWrite(trigPin, LOW);
delayMicroseconds(5);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH); disCM = (duration/2) * 0.0343; Serial.print(disCM);
Serial.print(“cm”);
Serial.println(); delay(100); }
