#include <WiFi.h>
#include <HTTPClient.h>
//請修改以下參數--------------------------------------------
char ssid[] = "wifi名稱";
char password[] = "wifi密碼";
//請修改為你自己的API Key，並將https改為http
String url = "http://api.thingspeak.com/update?api_key=NSHF4GEN1YCQC4H2";
int photocellPin = 39; // 光敏電阻 (photocell) 接在 anallog pin 
//---------------------------------------------------------
int photocellVal = 0; // photocell variable
int LED=0;
String LED_status = "OFF";
int vv;
void setup()
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT); //設定 DIO Pin 2 為 LED 輸出
  pinMode(photocellPin,INPUT);
  
  Serial.print("開始連線到無線網路SSID:");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
    {
      Serial.print("");
      delay(1000);
    }
  Serial.println("已連接WiFi");
}
void loop()
{
  // 讀取光敏電阻並輸出到 Serial Port
  photocellVal = analogRead(photocellPin);
  Serial.println("");
  Serial.print("讀取光敏值:");
  Serial.println(photocellVal);
  delay(100);
  vv=analogRead(photocellPin);
  if (vv<400)
    {
      digitalWrite(LED, HIGH);    
      Serial.println("LED ON");
      LED_status="ON";
    }
  else 
    {
      digitalWrite(LED, LOW);
      Serial.println("LED OFF");
      LED_status="OFF";
    }
  //開始傳送到thingspeak
  Serial.println("傳送數值至網頁");
  HTTPClient http;
  //將溫度及濕度以http get參數方式補入網址後方
  String url1 = url + "&field1=" + photocellVal;
  //http client取得網頁內容
  http.begin(url1);
  int httpCode = http.GET();
  
  if (httpCode == HTTP_CODE_OK)      
    {
      //讀取網頁內容到payload
      String payload = http.getString();
      //將內容顯示出來
      Serial.print("以上為第");
      Serial.print(payload);
      Serial.println("筆資料");
    } 
  else 
    {
      //讀取失敗
      Serial.println("網路傳送失敗");
    }
  http.end();
  Serial.println("15秒後再次偵測");
  delay(15000);//延遲15秒
}
