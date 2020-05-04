#include "HttpAp.h"

Preferences preferences;

void configMode ()
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
  ESP32WebServer server(80);
  
  server.on("/", HTTP_GET, [&]() {
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
    server.send(200, "text/html", form);
  });

  server.on("/do", HTTP_POST, [&]() {
    String ssid = server.arg("ssid");
    String password = server.arg("password");
    Serial.print("WiFI creds received. SSID: ");
    Serial.println(ssid);
    preferences.begin(APP_NAME, false);
    preferences.putString(SSID_KEY, ssid);
    preferences.putString(PASSWD_KEY, password);
    preferences.end();
    server.send(200, "text/plain", "...Reseting iFlowerpot");
    Serial.println(F("Reboot"));
    ESP.restart();
  });
  server.begin();
  while(true)
  {
    server.handleClient();
  }
}

String getSSID()
{
  String ssid;
  preferences.begin(APP_NAME, true);
  ssid = preferences.getString(SSID_KEY, "no_wifi");
  preferences.end();
  return ssid;
}

String getPassword()
{
  String password;
  preferences.begin(APP_NAME, true);
  password = preferences.getString(PASSWD_KEY, "no_passwd");
  preferences.end();
  return password;
}