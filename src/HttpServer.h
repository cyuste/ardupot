#include <Arduino.h>
#include <ESP32WebServer.h>
#include "daemonHygro.h"
#include "relay.h"


class HttpServer
{
  private:
    ESP32WebServer* server;
    DaemonHygro* dhygro;
    Relay* relay;
    void configureEndpoints();
  public:
    HttpServer(DaemonHygro* hygro, ESP32WebServer* ws);
    void init();
    void loop();
};
