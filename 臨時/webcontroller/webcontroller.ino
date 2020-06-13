#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DBH1.h>

const char *ssid = "Lavender";
const char *password = "12345678";

ESP8266WebServer server(80);
DBH1 dbh1;


void handleRoot()
{
  server.send(200, "text/plain", "hello from esp8266!");
}

void handleCar()
{
  String message = "";
  int BtnValue = 0;
  for (uint8_t i = 0; i < server.args(); i++)
  {
    if (server.argName(i) == "a")
    {
      String s = server.arg(i);
      BtnValue = s.toInt();
    }
    Serial.println(server.argName(i) + ": " + server.arg(i) + "\n");
  }

  switch (BtnValue)
  {
  case 1: // sola donuş
      dbh1.EnableBoth();
      dbh1.ReverseA(900);
      dbh1.ForwardB(1023);
      break;
  case 2: // düz ileri
      dbh1.EnableBoth();
      dbh1.Forward(1023, 1023);
      break;
  case 3: // saga donuş
      dbh1.EnableBoth();
      dbh1.ForwardA(1023);
      dbh1.ReverseB(900);
      break;
  case 4: // tam sola donuş
      dbh1.EnableBoth();
      dbh1.ForwardA(900);
      dbh1.ReverseB(900);
      break;
  case 5: // stop
      dbh1.DisableBoth();
      break;
  case 6: //
      dbh1.EnableBoth();
      dbh1.ReverseA(900);
      dbh1.ForwardB(900);
      break;
  case 7: //sol geri
      dbh1.EnableBoth();
      dbh1.ForwardA(900);
      dbh1.ReverseB(1023);
      break;
  case 8: // tam geri
      dbh1.EnableBoth();
      dbh1.Reverse(900, 900);
      break;
  case 9: // sag geri
      dbh1.EnableBoth();
      dbh1.ReverseA(1023);
      dbh1.ForwardB(900);
  default:
    break;
  }

  message += "<html> <head> <title>Gungor yalcin</title><head>";
  message += "<body><h3>Wifi Robot Car NodeMCU  Web Server</h1>";
  message += "<table> ";
  message += "<tr>";
  message += "<td><p><a href=\"/car?a=1\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\">\\</button></a></p> ";
  message += "<td><p><a href=\"/car?a=2\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\">^</button></a></p> ";
  message += "<td><p><a href=\"/car?a=3\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\">/</button></a></p> ";
  message += "<tr>";
  message += "<td><p><a href=\"/car?a=4\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\"> < </button></a></p> ";
  message += "<td><p><a href=\"/car?a=5\"><button style=\"width:100;height:100;font-size:40px;\" class=\"button\">Stop</button></a></p> ";
  message += "<td><p><a href=\"/car?a=6\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\"> > </button></a></p> ";
  message += "<tr>";
  message += "<td><p><a href=\"/car?a=7\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\">/</button></a></p> ";
  message += "<td><p><a href=\"/car?a=8\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\">v</button></a></p> ";
  message += "<td><p><a href=\"/car?a=9\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\">\\</button></a></p> ";
  message += "</table> ";
  message += "</body></html>";
  server.send(200, "text/html", message);
}

void handleNotFound()
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
  Serial.begin(115200);
  dbh1.init(7, 5, 8, 6, 1, 2, 0, 0);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.println("");
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(myIP);

  server.on("/", handleRoot);
  server.on("/car", handleCar);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
  server.handleClient();
}