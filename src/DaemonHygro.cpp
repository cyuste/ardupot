#include "daemonHygro.h"

DaemonHygro::DaemonHygro(Relay* pump, Hygrometer* hygro, uint32_t waterTime, int minHumidity)
{
  this->pump = pump;
  this->hygro = hygro;
  this->waterTime = waterTime;
  this->minHumidity = minHumidity;
  this->waterStart = 0;
}

uint32_t DaemonHygro::getWaterTime()
{
  return this->waterTime;
}

void DaemonHygro::setWaterTime(uint32_t t)
{
  this->waterTime = t;
}

int DaemonHygro::getMinHumidity()
{
  return this->minHumidity;
}

void DaemonHygro::setMinHumidity(int h)
{
  this->minHumidity = h;
}

uint16_t DaemonHygro::read()
{
  return this->hygro->read();
}

void DaemonHygro::forceStart()
{
  this->pump->start();
  this->waterStart = millis();
}

void DaemonHygro::forceStop()
{
  this->pump->stop();
}

uint16_t DaemonHygro::getPumpStatus()
{
  return this->pump->getRelayStatus();
}

void DaemonHygro::loop()
{
  if (this->pump->getRelayStatus() == HIGH && millis() >= (this->waterTime + this->waterStart))
  {
    Serial.println("DAEMON HYGRO: Stop pump");
    this->pump->stop();
  }
  else if (this->pump->getRelayStatus() == LOW && this->hygro->read() > this->minHumidity)
  {
    Serial.println("DAEMON HYGRO: Start pump");
    this->pump->start();
    this->waterStart = millis();
  }
}