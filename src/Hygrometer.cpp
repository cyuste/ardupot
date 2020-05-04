#include "hygrometer.h"


Hygrometer::Hygrometer(byte port)
{
  this->port = port;
}

uint16_t Hygrometer::read()
{
  return analogRead(this->port);
}
