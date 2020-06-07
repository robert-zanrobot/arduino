#include <WiFi.h>  
#include <WiFiClient.h>
#include <WiFiAP.h>
const char* ssid     = "";  // 為ESP32命名WiFi名稱並輸入""內
const char* password = "";  // 為ESP32命名WiFi密碼並輸入""內
WiFiServer server(80);
String header;
void setup() 
{
  Serial.begin(115200);
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
                        }
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            client.println("<body><h1>成功連結ESP32內建網頁</h1>");
            client.println("</body></html>");
            client.println();
            break;
          } 
          else 
          { 
            currentLine = "";
          }
        {  
          currentLine += c;      
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client Disconnected.");
  }
