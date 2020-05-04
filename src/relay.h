#ifndef RELE_H
#define RELE_H

#include <Arduino.h>
class Relay
{
  private:
    byte port;
    bool isOn;
  public:
    Relay(byte port);
    void init();
    byte getRelayStatus();
    void start();
    void stop();
};

#endif