#include <Arduino.h>

#ifndef HYGROMETER_H
#define HYGROMETER_H
class Hygrometer
{
  private:
    byte port;
  public:
    Hygrometer(byte port = 0);
    uint16_t read();
};

#endif