#include <Arduino.h>
#include <ESP32WebServer.h>
#include "DaemonHygro.h"
#include "Relay.h"


class HttpServer
{
  private:
    ESP32WebServer server;
    DaemonHygro* dhygro;
    Relay* relay;
    void configureEndpoints();
  public:
    HttpServer(DaemonHygro* hygro, Relay* relay, int port = 80);
    void init();
    void loop();
};
