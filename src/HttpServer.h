#include <Arduino.h>
#include <ESP32WebServer.h>
#include "DaemonHygro.h"
#include "Rele.h"


class HttpServer
{
  private:
    ESP32WebServer server;
    DaemonHygro* dhygro;
    Rele* rele;
    void configureEndpoints();
  public:
    HttpServer(DaemonHygro* hygro, Rele* rele, int port = 80);
    void init();
    void loop();
};
