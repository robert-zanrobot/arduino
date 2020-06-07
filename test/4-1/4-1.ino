int photocellPin = 2; // 光敏電阻 (photocell) 接在 anallog pin 2
int photocellVal = 0; // photocell variable
int LED=0;
int vv;
void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);  //設定 DIO Pin 2 為 LED 輸出 
}
void loop() {
  // 讀取光敏電阻並輸出到 Serial Port 
  photocellVal = analogRead(photocellPin);
  Serial.println(photocellVal);  
  delay(1000);       
vv=analogRead(photocellPin);
if (vv<400){
   digitalWrite(LED, HIGH);}
else {  digitalWrite(LED, LOW);
}}
