#include "httpServer.h"

HttpServer::HttpServer(DaemonHygro* dhygro, ESP32WebServer* ws)
{
  this->server = ws;
  this->dhygro = dhygro;
}

void HttpServer::init()
{
  this->configureEndpoints();
  this->server->begin();
  Serial.println(F("HTTP Server started"));
}

void HttpServer::configureEndpoints()
{
  this->server->on("/status", HTTP_GET, [&]() {
    String relStatusStr =  this->dhygro->getPumpStatus() == HIGH ? "on" : "off";
    char buffer[60];
    snprintf(buffer, sizeof(buffer), "{\"h\": %d, \"status\": \"%s\", \"irrT\": %d, \"humMin\": %d}\n",
      this->dhygro->read(),
      relStatusStr.c_str(),
      this->dhygro->getWaterTime(),
      this->dhygro->getMinHumidity());

    this->server->send(200, "application/json", buffer);
    Serial.println(buffer);
  });

  this->server->on("/on", HTTP_POST, [&]() {
    this->dhygro->forceStart();
    this->server->send(200, "text/plain", "");
  });

  this->server->on("/off", HTTP_POST, [&]() {
    this->dhygro->forceStop();
    this->server->send(200, "text/plain", "");
  });

  this->server->on("/config", HTTP_POST, [&]() {
    String irrT = this->server->arg("irrT");
    String minH = this->server->arg("minH");
    this->dhygro->setMinHumidity(minH.toInt());
    this->dhygro->setWaterTime(irrT.toInt());
    this->server->send(200, "text/plain", "");
  });

  this->server->onNotFound([&]() {
    String message = "Server is running!\n\n";
    message += "URI: ";
    message += this->server->uri();
    message += "\nMethod: ";
    message += (this->server->method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += this->server->args();
    message += "\n";
    this->server->send(200, "text/plain", message);
  });
}

void HttpServer::loop()
{
  this->server->handleClient();
}