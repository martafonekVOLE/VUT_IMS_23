//
// Created by martafonek on 22.11.23.
//
#include "BusStop.h"
#include "simlib.h"

#ifndef DOPRAVA_FIRSTBUSSTOP_H
#define DOPRAVA_FIRSTBUSSTOP_H

#define AMOUNT_OF_STOP_SPOTS 1

class FirstBusStop: public BusStop {
public:
    Facility firstBusStopFacility[AMOUNT_OF_STOP_SPOTS];
    Queue firstBusStopQueue;

    explicit FirstBusStop(int bus);

    void Behavior() override;
};


#endif //DOPRAVA_FIRSTBUSSTOP_H
