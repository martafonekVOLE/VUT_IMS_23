/**
 * @project Model logistiky - hromadná osobní přeprava, IMS
 * @brief Header file, contains declaration
 *
 * @file Bus.h
 * @date 21.11.2023
 *
 * @author Martin Pech (xpechm00)
 * @author Josef Škorpík (xskorp07)
 */

#include <simlib.h>
#include "Accident.h"

#ifndef DOPRAVA_BUS_H
#define DOPRAVA_BUS_H

class Bus: public Process{
private:
    int capacity;
    int peopleInBus = 0;

public:
    Queue firstBusStopQueue;

    bool shouldBeQueued = true;
    int actualBus = 0;
    int startBusStop;
    double waitTimeToFirstStop;
    bool isSpareBus = false;
    int spareBusFor;

    /**
     * Construct
     *
     * @param startStop
     * @param waitTimeStop
     */
    explicit Bus(int startStop = -1, double waitTimeStop = 0, int spareFor = -1, int people = 0);

    /**
     * Decide if bus can be dispatched or must be put in a queue
     */
    void SetActualBusOrPutProcessInQueue();

    /**
     * Does handle bus movement
     */
    void BusMovement();

    /**
     * Does handle bus stop
     */
    void HandleBusStop(int currentBusStop);

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
