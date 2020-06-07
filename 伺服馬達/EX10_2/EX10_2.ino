void setup()
{  
  Serial.begin(9600);         //USB Baudrate
  Serial2.begin(9600);       //DC Motor Baudrate
  SetMode(0);
  DCSpeedControl(0);     
  delay(3000);
}

void loop()
{  
  DCSpeedControl(100);       //-100~100
  ReadDCSpeed();
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
void ReadDCSpeed()
{
  Serial2.print("GV");
  Serial2.write(13);    
  delay(30);
  while (Serial2.available() > 0) 
  {
    byte x = Serial2.read();
    if (x == '#')
    {
      String dataString = ""; 
      String cmdString = "";       
      while (Serial2.available() > 0) 
      {
        delay(1);
        int inChar = Serial2.read();   
        if (inChar == '\r')
        {
          Serial.print(cmdString);
          Serial.println(dataString.toInt());
          Serial.write(0);
          dataString = ""; 
          cmdString = ""; 
          while (Serial2.available() > 0) 
          {
            inChar = Serial2.read();   
          }
          break;
        }           
        if (isDigit(inChar)) 
        {
          dataString += (char)inChar; 
        }
        else
        {
          cmdString += (char)inChar; 
        }
      }
    }
  }  
}
          

