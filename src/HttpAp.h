#include <Arduino.h>
#include <WiFi.h>
#include <ESP32WebServer.h>
#include <Preferences.h>

#define APP_NAME "iflowerpot"
#define SSID_KEY "ssid"
#define PASSWD_KEY "paswd"

void configMode();
String getSSID();
String getPassword();