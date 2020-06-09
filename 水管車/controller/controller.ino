#include <PS2X_lib.h>

int DE = 25;
int RE = 26;
int num;
long int GG;
PS2X ps2x;
int error;

// parameters for reading the joystick:
int range = 12;               // output range of X or Y movement
int responseDelay = 5;        // response delay of the mouse, in ms
int threshold = range/4;      // resting threshold
int center = range/2;         // resting position value


void setup()
{
    Serial.begin(115200); // initialize serial at baudrate 9600:
    Serial2.begin(115200);
    do
    {
        //GamePad(clock, command, attention, data, Pressures?, Rumble?)
        error = ps2x.config_gamepad(13, 11, 10, 12, true, true); //這行要和接線對應正確
        if (error == 0)
        {
            Serial.print("Gamepad found!");
            break;
        }
        else
        {
            delay(100);
        }
    } while (1);
    pinMode(DE, OUTPUT);
    pinMode(RE, OUTPUT);
    delay(10);
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW); //  (always high as Master Writes data to Slave)
    int vrx = analogRead(14);
    int vry = analogRead(27);
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
void PS2()
{
    ps2x.read_gamepad(false, 0);
    int xReading = readAxis(PSS_LX);
    int yReading = readAxis(PSS_LY);
}
int readAxis(int thisAxis)
{
    // read the analog input:
    int reading = ps2x.Analog(thisAxis);

    // map the reading from the analog input range to the output range:
    reading = map(reading, 0, 255, 0, range);

    // if the output reading is outside from the
    // rest position threshold,  use it:
    int distance = reading - center;

    if (abs(distance) < threshold)
    {
        distance = 0;
    }

    // return the distance for this axis:
    return distance;
}