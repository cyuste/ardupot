#include "httpAp.h"

HttpAp::HttpAp(ESP32WebServer* ws)
{
  this->ws = ws;
}

void HttpAp::configMode()
{
  char AP_ssid[15];
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
  String endOfMac = WiFi.macAddress().substring(12,14);
  endOfMac.concat(WiFi.macAddress().substring(15,17));
  snprintf(AP_ssid, sizeof(AP_ssid), "esp32_%s",
        endOfMac.c_str());

  Serial.println();

  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_ssid, NULL);
  delay(200);
  if(!WiFi.softAPConfig(IPAddress(192, 168, 10, 1), IPAddress(192, 168, 10, 1), IPAddress(255, 255, 255, 0))){
      Serial.println("AP Config Failed");
  }
  
  Serial.print("Starting WiFi SSID: ");
  Serial.print(AP_ssid);
  Serial.print(", ESP IP address: ");
  Serial.println(WiFi.softAPIP());
  
  this->ws->on("/", HTTP_GET, [&]() {
    const char* form = "<!DOCTYPE html>"
      "<html>"
        "<body>"
        "<h2>Please configure WiFi access: </h2>"
        "<form action=\"/do\" target=\"_blank\" method=\"post\">"
          "<label for=\"ssid\">SSID:</label><br>"
          "<input type=\"text\" id=\"ssid\" name=\"ssid\"><br>"
          "<label for=\"password\">Password:</label><br>"
          "<input type=\"password\" id=\"password\" name=\"password\"><br><br>"
          "<input type=\"submit\" value=\"Submit\">"
        "</form> "
        "</body>"
      "</html>\n";
    this->ws->send(200, "text/html", form);
  });

  this->ws->on("/do", HTTP_POST, [&]() {
    String ssid = this->ws->arg("ssid");
    String password = this->ws->arg("password");
    Serial.print("WiFI creds received. SSID: ");
    Serial.println(ssid);
    storeSettings(&ssid, &password);
    this->ws->send(200, "text/plain", "...Reseting iFlowerpot");
    Serial.println(F("Reboot"));
    ESP.restart();
  });
  this->ws->begin();
}

void HttpAp::handleClient()
{
  this->ws->handleClient();
}
