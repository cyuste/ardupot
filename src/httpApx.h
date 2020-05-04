#ifndef HTTPAP_H
#define HTTPAP_H

#include <Arduino.h>
#include <WiFi.h>
#include <ESP32WebServer.h>
#include "potParams.h"

#define APP_NAME "iflowerpot"
#define SSID_KEY "ssid"
#define PASSWD_KEY "paswd"

class HttpApx
{
  private:
    ESP32WebServer* ws;
  public:
    HttpApx(ESP32WebServer* ws);
    void configMode();
    void handleClient();
};


#endif
