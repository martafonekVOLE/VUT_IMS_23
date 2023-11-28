/**
 * @project Model logistiky - hromadná osobní přeprava, IMS
 * @brief Accident Process implementation
 *
 * @file Accident.cpp
 * @date 21.11.2023
 *
 * @author Martin Pech (xpechm00)
 * @author Josef Škorpík (xskorp07)
 */

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
    Print("\n\n[Time: [%f]]\tAutobus číslo [%d] měl nehodu při opouštění zastávky číslo [%d].", Time, busNumber + 1, busStop + 1);
}

/**
 * @inheritDoc
 */
void Accident::Behavior()
{
    if(busStop + 2 >= glob_amount_of_bus_stops)
    {
        Print("\n[Time: [%f]]\tAutobus byl v poslední zastávce, díky čemuž už nemusí překládat cestující.", Time);
        return;
    }

    double waitingTimeForReplacementBus = 0;
    for (int currentBusStop = 0; currentBusStop < busStop; currentBusStop++) {
        waitingTimeForReplacementBus += Exponential(glob_time_between_stops);
    }

    (new Bus(busStop, waitingTimeForReplacementBus, busNumber))->Activate();
}
