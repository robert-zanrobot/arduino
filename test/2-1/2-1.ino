#include <BluetoothSerial.h>
BluetoothSerial SerialBT;//宣告藍芽物件=SerialBT
void setup() {
  Serial.begin(9600);//序列視窗
  SerialBT.begin("BLETEST");//<<藍芽廣播名稱，請自己記得
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(0, OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(0, LOW);
}
void loop() {
  if(SerialBT.available()){
    Serial.println("");
  }
  while(SerialBT.available())
  {
    char X=SerialBT.read();
    Serial.print(X);//查看藍芽輸入的值
if(X == 'A') {
      digitalWrite(2, HIGH);
      Serial.println("紅燈開"); }
    else if(X == 'a') {
      digitalWrite(2, LOW);
      Serial.println("紅燈關"); }
       if(X == 'B') {
      digitalWrite(4, HIGH);
      Serial.println("綠燈開"); }
    else if(X == 'b') {
      digitalWrite(4, LOW);
      Serial.println("綠燈關"); }
     if(X == 'C') {
      digitalWrite(0, HIGH);
      Serial.println("黃燈開"); }
    else if(X == 'c') {
      digitalWrite(0, LOW);
      Serial.println("黃燈關");   }    
  }  
  delay(100);
}
