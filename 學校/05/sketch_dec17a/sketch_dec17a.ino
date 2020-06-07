
#include "FlagTank.h"
#include "FlagTankArm.h"


int Ultrasound(int trigPin, int echoPin)
{
  long duration;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  duration = duration / 59;
  if ((duration < 5) || (duration > 80))
    return 100;
  return duration;
}

void setup()
{
  digitalWrite(12, LOW);
  iArm.turnTo(180,169,90,22);
  Serial.begin(9600);
}

void loop()
{
  Serial.print("0:");
  Serial.print(" ");
  Serial.print(analogRead(A0));
  Serial.print(" ");
  Serial.println();
  Serial.print("1:");
  Serial.print(" ");
  Serial.print(analogRead(A1));
  Serial.print(" ");
  Serial.println();
  Serial.print("2:");
  Serial.print(" ");
  Serial.print(analogRead(A2));
  Serial.print(" ");
  Serial.println();
  Serial.print("3:");
  Serial.print(" ");
  Serial.print(analogRead(A3));
  Serial.print(" ");
  Serial.println();
  Serial.print("6:");
  Serial.print(" ");
  Serial.print(analogRead(A6));
  Serial.print(" ");
  Serial.println();
  Serial.print("7:");
  Serial.print(" ");
  Serial.print(analogRead(A7));
  Serial.print(" ");
  Serial.println();
  Serial.print("超音波:");
  Serial.print(" ");
  Serial.print(Ultrasound(12,11));
  Serial.print(" ");
  Serial.println();
  delay(100);
}