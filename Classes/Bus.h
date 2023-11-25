#include <simlib.h>
#include "FirstBusStop.h"
#include "SecondBusStop.h"
#include "Accident.h"
#include "../arg_parse.h"

#ifndef DOPRAVA_BUS_H
#define DOPRAVA_BUS_H

#define AMOUNT_OF_BUSES 4

class Bus: public Process{
public:
    Facility busFacility[AMOUNT_OF_BUSES];
    Queue waitingForBusDispatch;

    bool shouldBeQueued = true;
    int actualBus = 0;
    int startBusStop;
    double waitTimeToFirstStop;

    explicit Bus(int startStop = 0, double waitTimeStop = 0);

    void SetActualBusOrPutProcessInQueue();
    void BusMovement();
    void Behavior() override;
};


#endif //DOPRAVA_BUS_H
