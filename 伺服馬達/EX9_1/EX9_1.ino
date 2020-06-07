void setup()
{  
  Serial.begin(9600);         //USB Baudrate
  Serial2.begin(9600);       //DC Motor Baudrate
  SetMode(0);
  DCSpeedControl(0);     
  delay(3000);
  SetMode(256);
}

void loop()
{  
  DCPositionControl(3072);       //-3072~3072
  delay(6000);  
}
void SetMode(int ModeValue)
{
  Serial2.print("SMOD");
  Serial2.print(ModeValue);
  Serial2.write(13);
}

void DCSpeedControl(int SpeedValue)
{
  Serial2.print("V");
  Serial2.print(SpeedValue);
  Serial2.write(13);
}

void DCPositionControl(int PositionValue)
{
  Serial2.print("MR");
  Serial2.print(PositionValue);
  Serial2.write(13);
}

