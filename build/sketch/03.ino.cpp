#include <Arduino.h>
#line 1 "g:\\nickw\\Documents\\Arduino Save\\work\\TRtest\\03\\03.ino"
#include <DHT.h>

#define DHTPIN A4
#define DHTTYPE DHT21

long int Lcounter = 0; //定義 counter 為 int 類型變數，且初始值為0
long int LaState;      //定義 aState 為 int 類型變數
long int LaLastState;  //定義 aLastState 為 int 類型變數
long int Rcounter = 0; //定義 counter 為 int 類型變數，且初始值為0
long int RaState;      //定義 aState 為 int 類型變數
long int RaLastState;  //定義 aLastState 為 int 類型變數
long int Ltest;
long int RE = 12;
long int DE = 10;
int num;

#line 17 "g:\\nickw\\Documents\\Arduino Save\\work\\TRtest\\03\\03.ino"
void DigitalWrite(int pinNumber, boolean status);
#line 22 "g:\\nickw\\Documents\\Arduino Save\\work\\TRtest\\03\\03.ino"
void AnalogWrite(int pinNumber, int value);
#line 27 "g:\\nickw\\Documents\\Arduino Save\\work\\TRtest\\03\\03.ino"
const int AnalogRead(int pinNumber);
#line 32 "g:\\nickw\\Documents\\Arduino Save\\work\\TRtest\\03\\03.ino"
int Position(uint8_t pinNumber);
#line 40 "g:\\nickw\\Documents\\Arduino Save\\work\\TRtest\\03\\03.ino"
void setup();
#line 56 "g:\\nickw\\Documents\\Arduino Save\\work\\TRtest\\03\\03.ino"
void loop();
#line 143 "g:\\nickw\\Documents\\Arduino Save\\work\\TRtest\\03\\03.ino"
void Ldata();
#line 161 "g:\\nickw\\Documents\\Arduino Save\\work\\TRtest\\03\\03.ino"
void Rdata();
#line 17 "g:\\nickw\\Documents\\Arduino Save\\work\\TRtest\\03\\03.ino"
void DigitalWrite(int pinNumber, boolean status)
{
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, status);
}
void AnalogWrite(int pinNumber, int value)
{
    pinMode(pinNumber, OUTPUT);
    analogWrite(pinNumber, value);
}
const int AnalogRead(int pinNumber)
{
    pinMode(pinNumber, INPUT);
    analogRead(pinNumber);
}
int Position(uint8_t pinNumber)
{
    pinMode(pinNumber, INPUT);
    digitalRead(pinNumber);
}

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(115200);
    Serial2.begin(115200);
    dht.begin();
    LaLastState = Position(2);
    RaLastState = Position(3);
    pinMode(RE, OUTPUT);
    pinMode(DE, OUTPUT);
    delay(10);
    digitalWrite(RE, LOW);
    digitalWrite(DE, LOW);
    attachInterrupt(0, Ldata, CHANGE);
    attachInterrupt(1, Rdata, CHANGE);
}

void loop()
{
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    int x = analogRead(A7); //read from xpin
    int y = analogRead(A6); //read from ypin
    int z = analogRead(A5); //read from zpin
    if (Serial2.available() == 1)
    {
        num = Serial2.parseInt();
        switch (num)
        {
        case 1:
            Serial.println("F");
            DigitalWrite(9, HIGH);
            DigitalWrite(8, LOW);
            AnalogWrite(A0, 255);
            DigitalWrite(7, HIGH);
            DigitalWrite(6, LOW);
            AnalogWrite(A2, 255);
            break;
        case 2:
            Serial.println("R");
            DigitalWrite(9, HIGH);
            DigitalWrite(8, LOW);
            AnalogWrite(A0, 255);
            DigitalWrite(7, LOW);
            DigitalWrite(6, HIGH);
            AnalogWrite(A2, 255);
            break;
        case 3:
            Serial.println("L");
            DigitalWrite(9, LOW);
            DigitalWrite(8, HIGH);
            AnalogWrite(A0, 255);
            DigitalWrite(7, HIGH);
            DigitalWrite(6, LOW);
            AnalogWrite(A2, 255);
            break;
        case 4:
            Serial.println("BD");
            DigitalWrite(9, LOW);
            DigitalWrite(8, HIGH);
            AnalogWrite(A0, 255);
            DigitalWrite(7, LOW);
            DigitalWrite(6, HIGH);
            AnalogWrite(A2, 255);
            break;
        case 5:
            Serial.println("S");
            DigitalWrite(9, HIGH);
            DigitalWrite(8, HIGH);
            AnalogWrite(A0, 255);
            DigitalWrite(7, HIGH);
            DigitalWrite(6, HIGH);
            AnalogWrite(A2, 255);
            break;
        }
    }
    else
    {
        digitalWrite(DE, HIGH);
        Serial2.println();
        Serial2.print("Ldata: ");
        Serial2.println(Lcounter);
        Serial2.print("Rdata: ");
        Serial2.println(Rcounter);
        Serial2.print("X: ");
        Serial2.print(x);
        Serial2.print("Y: ");
        Serial2.print(y);
        Serial2.print(" Z: ");
        Serial2.print(z);
        Serial2.println();
        Serial2.print("H: ");
        Serial2.print(h);
        Serial2.print(" %\t");
        Serial2.print("Temp: ");
        Serial2.print(t);
        Serial2.println(" *C");
        delay(50);
        digitalWrite(DE, LOW);
        while (Serial2.read() >= 0)
        {
        }
    }
}
void Ldata()
{
    LaState = Position(2); //將outputA的讀取值 設給 aState

    if (LaState != LaLastState)
    { //條件判斷，當aState 不等於 aLastState時發生

        if (Position(4) != LaState)
        {               //條件判斷，當outputB讀取值 不等於 aState時發生
            Lcounter++; //計數器+1
        }
        else
        {
            Lcounter--; //計數器-1
        }
    }
    LaLastState = LaState; //將aState 最後的值 設給 aLastState
}
void Rdata()
{
    RaState = Position(3); //將outputA的讀取值 設給 aState

    if (RaState != RaLastState)
    { //條件判斷，當aState 不等於 aLastState時發生

        if (Position(5) != RaState)
        {               //條件判斷，當outputB讀取值 不等於 aState時發生
            Rcounter--; //計數器+1
        }
        else
        {
            Rcounter++; //計數器-1
        }
    }
    RaLastState = RaState; //將aState 最後的值 設給 aLastState
}

