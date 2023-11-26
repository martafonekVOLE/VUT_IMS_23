#include <simlib.h>
#include "Accident.h"

#ifndef DOPRAVA_BUS_H
#define DOPRAVA_BUS_H

class Bus: public Process{
public:
    Facility firstBusStopFacility[1];
    Queue waitingForBusDispatch;
    Queue firstBusStopQueue;

    bool shouldBeQueued = true;
    int actualBus = 0;
    int startBusStop;
    double waitTimeToFirstStop;

    /**
     * Construct
     *
     * @param startStop
     * @param waitTimeStop
     */
    explicit Bus(int startStop = 0, double waitTimeStop = 0);

    /**
     * Decide if bus can be dispatched or must be put in a queue
     */
    void SetActualBusOrPutProcessInQueue();

    /**
     * Does handle bus movement
     */
    void BusMovement();

    /**
     *
     */
    void HandleBusStop();

    /**
     * Does generate traffic jam with some probability
     */
    void DecideAboutTrafficJam();

    /**
     * Does generate accident with some probability
     *
     * @param currentBusStop
     * @return bool
     */
    bool AccidentOccurred(int currentBusStop);

    /**
     * Required method behavior, does handle default behavior
     */
    void Behavior() override;
};


#endif //DOPRAVA_BUS_H
