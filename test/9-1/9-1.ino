#include <BluetoothSerial.h>
BluetoothSerial SerialBT;//宣告藍芽物件=SerialBT
void setup() {
// put your setup code here, to run once:
Serial.begin(115200);//序列視窗
SerialBT.begin(“ESP32”);//<<藍芽名稱，請自己記得
pinMode(A0, INPUT);
pinMode(13,OUTPUT);//電燈relay
}
int pr_min = 400;
void loop() {
char analogRea=SerialBT.read();
int pr = analogRead(A0);{
Serial.println(pr);
SerialBT.println(pr);
delay(1000);
}
while(SerialBT.available())
{
char btdata=SerialBT.read();
Serial.print(btdata);//查看藍芽輸入的值
if (btdata==’3′){digitalWrite(13,HIGH);}//開電燈
if (btdata==’4′){digitalWrite(13,LOW);}//關電燈
}
delay(100);
}
