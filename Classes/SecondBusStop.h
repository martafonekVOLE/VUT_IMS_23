#include "BusStop.h"

#ifndef DOPRAVA_SECONDBUSSTOP_H
#define DOPRAVA_SECONDBUSSTOP_H


class SecondBusStop: public BusStop {
public:
    Facility secondBusStopFacility;
    Queue secondBusStopQueue;

    explicit SecondBusStop(int bus);

    void Behavior() override;
};


#endif //DOPRAVA_SECONDBUSSTOP_H
