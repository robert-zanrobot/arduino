

#define RESET 0
#define OPEN 1
#define SPEED 2
#define POSITION 3
#define SPEEDPOSITION 4

byte state;
int position = 6666;

void setup()
{
    Serial1.begin(115200);
    state = RESET;
}
void loop()
{
    switch (state)
    {
    case RESET:
        Serial1.write(0xAA);
        Serial1.write(0x4D);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0x39);
        break;

    case OPEN:
        Serial1.write(0xAA);
        Serial1.write(0x4D);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0x39);
        break;
    case SPEED:
        Serial1.write(0xAA);
        Serial1.write(0x52);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xAA);
        Serial1.write(0x6F);
        Serial1.write((unsigned char)((position >> 8) & 0xff));
        Serial1.write((unsigned char)((position >> 0) & 0xff));
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        break;
    case POSITION:
        Serial1.write(0xAA);
        Serial1.write(0x4D);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0x39);
        break;
    case SPEEDPOSITION:
        Serial1.write(0xAA);
        Serial1.write(0x4D);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0xFF);
        Serial1.write(0x39);
        break;
    }
    Serial1.write(0xAA);
    Serial1.write(0x52);
    Serial1.write(0xFF);
    Serial1.write(0xFF);
    Serial1.write(0xFF);
    Serial1.write(0xFF);
    Serial1.write(0xFF);
    Serial1.write(0xFF);
    Serial1.write(0xFF);
    Serial1.write(0xFF);
    Serial1.write(0xAA);
    Serial1.write(0x6F);
    Serial1.write((unsigned char)((position >> 8) & 0xff));
    Serial1.write((unsigned char)((position >> 0) & 0xff));
    Serial1.write(0xFF);
    Serial1.write(0xFF);
    Serial1.write(0xFF);
    Serial1.write(0xFF);
    Serial1.write(0xFF);
    Serial1.write(0xFF);
}