/**
 * @project Model logistiky - hromadná osobní přeprava, IMS
 * @brief Implementation of Accident.h, implements behavior on accident
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
Accident::Accident(int bus, int stop, int peopleInBus): Process()
{
    busNumber = bus;
    busStop = stop;
    people = peopleInBus;

    for (int i = 0; i < peopleInBus; i++) {
        glob_passenger_happiness -= 3;
    }

    Print("\n[Time: %f]\t\033[1;31mAutobus číslo [%d] měl nehodu při opouštění zastávky číslo [%d].\033[0m", Time, busNumber + 1, busStop + 1);
}

/**
 * @inheritDoc
 */
void Accident::Behavior()
{
    double waitingTimeForReplacementBus = 0.0;
    for (int currentBusStop = 0; currentBusStop < busStop; currentBusStop++) {
        waitingTimeForReplacementBus += Normal(glob_time_between_stops, 3);
    }

    (new Bus(busStop, waitingTimeForReplacementBus, busNumber, people))->Activate();
}
