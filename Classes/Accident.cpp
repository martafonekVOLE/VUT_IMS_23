#include "Accident.h"
#include "../arg_parse.h"
#include "Bus.h"


/**
 * @inheritDoc
 */
Accident::Accident(int bus, int stop): Process()
{
    busNumber = bus;
    busStop = stop;
    Print("\n\n\n[Time: [%f]]\tAutobus číslo [%d] měl nehodu při opouštění zastávky číslo [%d].", Time, busNumber + 1, busStop + 1);
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

    (new Bus(busStop, waitingTimeForReplacementBus, busNumber))->Activate();
}
