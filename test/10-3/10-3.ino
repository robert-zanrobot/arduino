#include <WiFi.h>  
#include <WiFiClient.h>
#include <WiFiAP.h>
const char* ssid     = "";  // 為ESP32命名WiFi名稱並輸入""內
const char* password = "";  // 為ESP32命名WiFi密碼並輸入""內
WiFiServer server(80);
String header;
String output26State = "off";
String output27State = "off";
//填入您所要使用之腳位
const int output26 = 26;
const int output27 = 27;
void setup() 
{
  Serial.begin(115200);
  pinMode(output26, OUTPUT);
  pinMode(output27, OUTPUT);
  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);
  Serial.print("");
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  // 序列阜顯示WiFi的連接狀況&WiFi的IP
  Serial.println("");
  Serial.println("WiFi Start.");
  Serial.print("WEB IP address: ");
  Serial.println(myIP);
  Serial.println("");
  Serial.print("進入網頁搜尋[");
  Serial.print(myIP);
  Serial.print("]以進入控制LED網頁");
  server.begin();
}
void loop()
{
  WiFiClient client = server.available();  
  if (client) 
  {                             
    Serial.println("New Client.");          
    String currentLine = "";                
    
    while (client.connected()) 
    {            
      if (client.available()) 
      {            
        char c = client.read();             
        Serial.write(c);                   
        header += c;
        if (c == '\n') 
        {                    
          if (currentLine.length() == 0) 
          {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            if (header.indexOf("GET /26/on") >= 0) 
            {
              Serial.println("GPIO 26 on");
              output26State = "on";
              digitalWrite(output26, HIGH);
            } 
            else if (header.indexOf("GET /26/off") >= 0) 
            {
              Serial.println("GPIO 26 off");
              output26State = "off";
              digitalWrite(output26, LOW);
            } 
            else if (header.indexOf("GET /27/on") >= 0) 
            {
              Serial.println("GPIO 27 on");
              output27State = "on";
              digitalWrite(output27, HIGH);
            } 
            else if (header.indexOf("GET /27/off") >= 0) 
            {
              Serial.println("GPIO 27 off");
              output27State = "off";
              digitalWrite(output27, LOW);
            }
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            client.println("<body><h1>ESP32 Web Server</h1>");
            client.println("<p>GPIO 26 腳位- LED目前狀態 " + output26State + "</p>");      
            if (output26State=="off") 
            {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
            } 
            else 
            {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
            }             
            client.println("<p>GPIO 27 腳位- LED目前狀態 " + output27State + "</p>");
                  
            if (output27State=="off") 
            {
              client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
            } 
            else 
            {
              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            client.println();
            break;
          } 
          else 
          { 
            currentLine = "";
          }
        } else if (c != '\r') 
        {  
          currentLine += c;      
        }
      }
    }
    header = "";
    
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
