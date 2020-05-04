#ifndef DHYGRO_H
#define DHYGRO_H

#include <Arduino.h>
#include "hygrometer.h"
#include "relay.h"

class DaemonHygro
{
  private:
    Hygrometer* hygro;
    Relay* pump;
    uint32_t waterTime;
    uint32_t waterStart;
    int minHumidity;
  public:
    DaemonHygro(Relay* pump, Hygrometer* hygro, uint32_t waterTime = 0, int minHumidity = 0);
    void loop();
    uint16_t read();
    uint32_t getWaterTime();
    void setWaterTime(uint32_t time);
    int getMinHumidity();
    void setMinHumidity(int hum);
    void forceStart();
    void forceStop();
    uint16_t getPumpStatus();
};

#endif