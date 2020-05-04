#include <Arduino.h>

#ifndef RELE_H
#define RELE_H
class Rele
{
  private:
    byte port;
    bool isOn;
  public:
    Rele(byte port);
    void init();
    uint16_t read();
    byte getReleStatus();
    void start();
    void stop();
};

#endif