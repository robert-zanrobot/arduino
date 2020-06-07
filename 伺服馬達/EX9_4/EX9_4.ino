void setup()
{  
  Serial.begin(9600);         //USB Baudrate
  Serial2.begin(9600);       //DC Motor Baudrate
  SetAbsDCPosition(); 
  SetMode(256);
}

void loop()
{  
  DCAngleControl(384);    //45   
  delay(6000);  
  DCAngleControl(768);    //90    
  delay(6000);  
  DCAngleControl(1152);  //135     
  delay(6000);  
  DCAngleControl(1536);  //180     
  delay(6000);  
  DCAngleControl(0);        //0  
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

void SetAbsDCPosition()
{
  SetMode(0);
  DCSpeedControl(0);
  delay(3000);
  Serial2.print("PO");
  Serial2.write(13);
}
void DCAngleControl(int AngleValue)
{
  Serial2.write("M");
  Serial2.print(AngleValue);
  Serial2.write(13);
}

