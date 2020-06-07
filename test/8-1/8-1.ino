#include <Servo.h>//宣告
Servo servo;//命名
int pos = 0;
void setup() {
Serial.begin(115200);//序列阜監控視窗
servo.attach(16); //橘色的線接主要是訊號線，接到 p16
}
void loop() {
if(Serial.available()){                 //
int num = Serial.parseInt();     // case 前置 num(數字鍵)
switch(num) {                            //   
case 1 :   //1~9
for(pos = 0; pos < 180; pos += 1) // 一度一度由 0 度旋轉到 180 度
servo.write(pos);
delay(15);
break;
case 2 : // 1~9
for(pos = 180; pos>=1; pos-=1) // 一度一度由 180 度旋轉到 0 度
servo.write(pos);
delay(15);
break;
}}}
