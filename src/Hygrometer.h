#ifndef HYGROMETER_H
#define HYGROMETER_H

#include <Arduino.h>

class Hygrometer
{
  private:
    byte port;
  public:
    Hygrometer(byte port = 0);
    uint16_t read();
};

#endif