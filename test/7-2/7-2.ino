const int trigPin = 5;
const int echoPin = 4;
const int ledPin = 12;
const int freq = 2000;
const int ledChannel = 0;
const int resolution = 8;
long duration; int distance;
int safetyDistance;
void setup() { pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
Serial.begin(115200);
ledcSetup(ledChannel, freq, resolution);
ledcAttachPin(ledPin, ledChannel);
ledcWriteTone(ledChannel, 0);
}
void loop()
{ digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
{ distance= duration*0.034/2;
safetyDistance = distance; if (safetyDistance <= 30){ ledcWriteTone(ledChannel,0);
delay(100);
}
if (safetyDistance < 5){ ledcWriteTone(ledChannel,1730);
delay(100);
}
if (safetyDistance < 20){ ledcWriteTone(ledChannel,1046);
delay(100); }
}
Serial.print(“Distance: “);
Serial.println(distance);
}
