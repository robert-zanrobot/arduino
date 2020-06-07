# 1 "g:\\nickw\\Documents\\Arduino Save\\work\\TRtest\\03\\03.ino"
# 2 "g:\\nickw\\Documents\\Arduino Save\\work\\TRtest\\03\\03.ino" 2




long int Lcounter = 0; //定義 counter 為 int 類型變數，且初始值為0
long int LaState; //定義 aState 為 int 類型變數
long int LaLastState; //定義 aLastState 為 int 類型變數
long int Rcounter = 0; //定義 counter 為 int 類型變數，且初始值為0
long int RaState; //定義 aState 為 int 類型變數
long int RaLastState; //定義 aLastState 為 int 類型變數
long int Ltest;
long int RE = 12;
long int DE = 10;
int num;

void DigitalWrite(int pinNumber, boolean status)
{
    pinMode(pinNumber, 0x1);
    digitalWrite(pinNumber, status);
}
void AnalogWrite(int pinNumber, int value)
{
    pinMode(pinNumber, 0x1);
    analogWrite(pinNumber, value);
}
const int AnalogRead(int pinNumber)
{
    pinMode(pinNumber, 0x0);
    analogRead(pinNumber);
}
int Position(uint8_t pinNumber)
{
    pinMode(pinNumber, 0x0);
    digitalRead(pinNumber);
}

DHT dht(A4, 21);

void setup()
{
    Serial.begin(115200);
    Serial2.begin(115200);
    dht.begin();
    LaLastState = Position(2);
    RaLastState = Position(3);
    pinMode(RE, 0x1);
    pinMode(DE, 0x1);
    delay(10);
    digitalWrite(RE, 0x0);
    digitalWrite(DE, 0x0);
    attachInterrupt(0, Ldata, 1);
    attachInterrupt(1, Rdata, 1);
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
            DigitalWrite(9, 0x1);
            DigitalWrite(8, 0x0);
            AnalogWrite(A0, 255);
            DigitalWrite(7, 0x1);
            DigitalWrite(6, 0x0);
            AnalogWrite(A2, 255);
            break;
        case 2:
            Serial.println("R");
            DigitalWrite(9, 0x1);
            DigitalWrite(8, 0x0);
            AnalogWrite(A0, 255);
            DigitalWrite(7, 0x0);
            DigitalWrite(6, 0x1);
            AnalogWrite(A2, 255);
            break;
        case 3:
            Serial.println("L");
            DigitalWrite(9, 0x0);
            DigitalWrite(8, 0x1);
            AnalogWrite(A0, 255);
            DigitalWrite(7, 0x1);
            DigitalWrite(6, 0x0);
            AnalogWrite(A2, 255);
            break;
        case 4:
            Serial.println("BD");
            DigitalWrite(9, 0x0);
            DigitalWrite(8, 0x1);
            AnalogWrite(A0, 255);
            DigitalWrite(7, 0x0);
            DigitalWrite(6, 0x1);
            AnalogWrite(A2, 255);
            break;
        case 5:
            Serial.println("S");
            DigitalWrite(9, 0x1);
            DigitalWrite(8, 0x1);
            AnalogWrite(A0, 255);
            DigitalWrite(7, 0x1);
            DigitalWrite(6, 0x1);
            AnalogWrite(A2, 255);
            break;
        }
    }
    else
    {
        digitalWrite(DE, 0x1);
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
        digitalWrite(DE, 0x0);
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
        { //條件判斷，當outputB讀取值 不等於 aState時發生
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
        { //條件判斷，當outputB讀取值 不等於 aState時發生
            Rcounter--; //計數器+1
        }
        else
        {
            Rcounter++; //計數器-1
        }
    }
    RaLastState = RaState; //將aState 最後的值 設給 aLastState
}
