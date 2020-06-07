void setup()
{  
  Serial.begin(9600);         //USB Baudrate
  Serial2.begin(9600);       //DC Motor Baudrate
  SetMode(0);
  DCSpeedControl(0);     
}

void loop()
{  
  DCSpeedControl(30);       //-100~100
  delay(1000);  
}
void SetMode(int ModeValue)
{
  Serial2.print("SMOD");
  Serial2.print(ModeValue);
  Serial2.write(13);
}

void DCSpeedControl(int SpeedValue)
{
  Serial2.write("V");
  Serial2.print(SpeedValue);
  Serial2.write(13);
}


