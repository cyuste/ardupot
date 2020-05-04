#include <Arduino.h>
#include "Hygrometer.h"
#include "Rele.h"


#ifndef DHYGRO_H
#define DHYGRO_H
class DaemonHygro
{
  private:
    Hygrometer hygro;
    Rele* pump;
    uint32_t waterTime;
    uint32_t waterStart;
    int minHumidity;
  public:
    DaemonHygro(Rele* pump, byte hygroPort = 0, uint32_t waterTime = 0, int minHumidity = 0);
    void loop();
    uint16_t read();
    uint32_t getWaterTime();
    void setWaterTime(uint32_t time);
    int getMinHumidity();
    void setMinHumidity(int hum);
    void forceStart();
    void forceStop();
};

#endif