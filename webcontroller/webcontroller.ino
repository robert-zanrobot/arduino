#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DBH1.h> // DBH1.cpp 第178行 IN2A 應該是 IN1B

const char* ssid = "Lavender";     // 為ESP8266命名WiFi名稱並輸入""內
const char* password = "12345678"; // 為ESP8266命名WiFi密碼並輸入""內

ESP8266WebServer server(80);
DBH1 dbh1;

void handleCar()
{
  String message = "";
  int BtnValue = 0;
  for (uint8_t i = 0; i < server.args(); i++) //拆字
  {
    if (server.argName(i) == "a")
    {
      String s = server.arg(i);
      BtnValue = s.toInt();
    }
    Serial.println(server.argName(i) + ": " + server.arg(i) + "\n");
  }

  switch (BtnValue) //控制
  {
  case 1: // 左前
      dbh1.EnableBoth();
      dbh1.ReverseA(300);
      dbh1.ForwardB(500);
      break;
  case 2: // 前
      dbh1.EnableBoth();
      dbh1.Forward(500, 500);
      break;
  case 3: // 右前
      dbh1.EnableBoth();
      dbh1.ForwardA(500);
      dbh1.ReverseB(300);
      break;
  case 4: // 左
      dbh1.EnableBoth();
      dbh1.ReverseA(300);
      dbh1.ForwardB(300);

      break;
  case 5: // 停
      dbh1.Coasting();
      break;
  case 6: // 右
      dbh1.EnableBoth();
      dbh1.ForwardA(300);
      dbh1.ReverseB(300);
      break;
  case 7: // 左後
      dbh1.EnableBoth();
      dbh1.ForwardA(300);
      dbh1.ReverseB(500);
      break;
  case 8: // 後
      dbh1.EnableBoth();
      dbh1.Reverse(300, 300);
      break;
  case 9: // 右後
      dbh1.EnableBoth();
      dbh1.ReverseA(500);
      dbh1.ForwardB(300);
  default:
    break;
  }
  //網頁內容
  message += "<html> <head> <title>Gungor yalcin</title><head>";
  message += "<body><h3>Wifi Robot Car NodeMCU  Web Server</h1>";
  message += "<table> ";
  message += "<tr>";
  message += "<td><p><a href=\"/?a=1\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\">\\</button></a></p> ";
  message += "<td><p><a href=\"/?a=2\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\">^</button></a></p> ";
  message += "<td><p><a href=\"/?a=3\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\">/</button></a></p> ";
  message += "<tr>";
  message += "<td><p><a href=\"/?a=4\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\"> < </button></a></p> ";
  message += "<td><p><a href=\"/?a=5\"><button style=\"width:100;height:100;font-size:40px;\" class=\"button\">Stop</button></a></p> ";
  message += "<td><p><a href=\"/?a=6\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\"> > </button></a></p> ";
  message += "<tr>";
  message += "<td><p><a href=\"/?a=7\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\">/</button></a></p> ";
  message += "<td><p><a href=\"/?a=8\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\">v</button></a></p> ";
  message += "<td><p><a href=\"/?a=9\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\">\\</button></a></p> ";
  message += "</table> ";
  message += "</body></html>";
  server.send(200, "text/html", message);
}

void handleNotFound() //錯誤位址回報錯誤
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup()
{
  pinMode(D4,OUTPUT);
  digitalWrite(D4,LOW); //這個是繼電器開關
  dbh1.init(D7, D5, D8, D6, D1, D2, D0, D0); //DBH1 pin定義
  Serial.begin(115200);
  WiFi.mode(WIFI_AP); //WIFI模式
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  // 序列阜顯示WiFi的連接狀況&WiFi的IP
  Serial.println("");
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(myIP);

  server.on("/", handleCar);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");  //test web
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
  server.handleClient();
}