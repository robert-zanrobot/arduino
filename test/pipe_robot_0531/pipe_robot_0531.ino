int rposition = -20000;
int position = 20000;
int32_t read_position = (Serial1.read() == 0x16)|(Serial1.read() << 24)|(Serial1.read() << 16)|(Serial1.read() << 8)|Serial1.read();
void setup()
{
  Serial1.begin(115200);
  Serial.begin(115200);
  Driver_reset();
  delay(1000);
  // 設定驅動器為 "位置速度模式"
}

void loop()
{
  while (true)
  {
    CW_move();
    delay(2000);
    Driver_reset();
    delay(2000);
    Stop_move();
    delay(2000);
    Driver_reset();
    delay(2000);
  }
}

void Driver_reset()
{
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
}
void Stop_move()
{
  Serial1.write(0xAA);
  Serial1.write(0x51);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  Serial1.write(0xAA);
  Serial1.write(0x0B);
  Serial1.write((unsigned char)((rposition >> 24) & 0xff));
  Serial1.write((unsigned char)((rposition >> 16) & 0xff));
  Serial1.write((unsigned char)((rposition >> 8) & 0xff));
  Serial1.write((unsigned char)((rposition >> 0) & 0xff));
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  Serial.println(read_position);
}
void CW_move()
{
  Serial1.write(0xAA);
  Serial1.write(0x51);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  Serial1.write(0xAA);
  Serial1.write(0x0B);
  Serial1.write((unsigned char)((position >> 24) & 0xff));
  Serial1.write((unsigned char)((position >> 16) & 0xff));
  Serial1.write((unsigned char)((position >> 8) & 0xff));
  Serial1.write((unsigned char)((position >> 0) & 0xff));
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  Serial.println(read_position);
}
void CCW_move()
{
  //還不太會, 晚點測
}
