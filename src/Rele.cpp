#include "Rele.h"



Rele::Rele(byte port)
{
  this->port = port;
}

void Rele::init()
{
  pinMode(this->port, OUTPUT);
  digitalWrite(this->port, LOW);
  this->isOn = false;
}

byte Rele::getReleStatus()
{
  return isOn? HIGH: LOW;
}

void Rele::start()
{
  Serial.print("Start rele. Port: ");
  Serial.println(this->port);
  digitalWrite(this->port, HIGH);
  this->isOn = true;
}

void Rele::stop()
{
  Serial.print("Stop rele. Port: ");
  Serial.println(this->port);
  digitalWrite(this->port, LOW);
  this->isOn = false;
}