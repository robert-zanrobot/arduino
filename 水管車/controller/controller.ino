int DE = 25;
int RE = 26;
int num;
long int GG;

void setup()
{
    Serial.begin(115200); // initialize serial at baudrate 9600:
    Serial2.begin(115200);
    pinMode(DE, OUTPUT);
    pinMode(RE, OUTPUT);
    delay(10);
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW); //  (always high as Master Writes data to Slave)
}
void loop()
{
    if (Serial.available() == 2)
    {
        num = Serial.read(); //Serial Write POTval to RS-485 Bus
        digitalWrite(DE, HIGH);
        Serial2.write(num);
        Serial.read() > 0;
        delay(50);
        Serial2.read() > 0;
        digitalWrite(DE, LOW);
    }
    else
    {
        digitalWrite(DE, LOW);
        while (Serial2.available() >= 3)
        {
            GG = Serial2.read();
            Serial.println(GG);
        }
    }
}