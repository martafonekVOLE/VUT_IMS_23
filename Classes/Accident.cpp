#include "Accident.h"
#include "../arg_parse.h"

/**
 * @inheritDoc
 */
Accident::Accident(int bus, int stop): Process()
{
    busNumber = bus;
    busStop = stop;
    Print("\n[Time: [%f]]\tAutobus číslo [%d] měl nehodu při opouštění zastávky číslo [%d].", Time, bus, stop);
}

/**
 * @inheritDoc
 */
void Accident::Behavior()
{
    double waitingTimeForReplacementBus = 0;
    for (int currentBusStop = 0; currentBusStop < busStop; currentBusStop++) {
        waitingTimeForReplacementBus += Exponential(glob_time_between_stops);
    }

    // todo + čas přestupu
    Wait(waitingTimeForReplacementBus + Exponential(2));
    Print("\n[Time: [%f]]\tAutobus číslo [%d] přeložil cestující a není ho již možné použít.", Time, (busNumber + 1));
}
