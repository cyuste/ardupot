#include "relay.h"



Relay::Relay(byte port)
{
  this->port = port;
}

void Relay::init()
{
  pinMode(this->port, OUTPUT);
  digitalWrite(this->port, LOW);
  this->isOn = false;
}

byte Relay::getRelayStatus()
{
  return isOn? HIGH: LOW;
}

void Relay::start()
{
  Serial.print("Start Relay. Port: ");
  Serial.println(this->port);
  digitalWrite(this->port, HIGH);
  this->isOn = true;
}

void Relay::stop()
{
  Serial.print("Stop Relay. Port: ");
  Serial.println(this->port);
  digitalWrite(this->port, LOW);
  this->isOn = false;
}