/**
 * @project Model logistiky - hromadná osobní přeprava, IMS
 * @brief Main file with program logic
 *
 * @file main.cpp
 * @date 21.11.2023
 *
 * @author Martin Pech (xpechm00)
 * @author Josef Škorpík (xskorp07)
 */

#include <simlib.h>
#include "arg_parse.h"
#include "Classes/Bus.h"

/**
 * New Bus Generator
 * @brief This method is responsible for generating new Processes until time runs out
 */
class BusDispatcher: public Event
{
    void Behavior() override
    {
        (new Bus())->Activate();

        Activate(Time + glob_time_between_bus_starts);
        Print("\n[Time: %f]\t\033[1;32mAutobus by měl nyní vyjet podle jízdního řádu.\033[0m", Time);
    }
};

/**
 * Main function
 *
 * @param int argc
 * @param char* argv
 * @return
 */
int main(int argc, char *argv[])
{
    // Parsing arguments
    arg_parse(argc, argv);

    Init(0, glob_time_to);
    (new BusDispatcher)->Activate();

    Run();

    Print("\n\n========================================================= ");
    Print("\nStatistics:\n");

    if(glob_passenger_happiness < 0.0)
    {
        Print("\nPassenger happiness: \033[1;31m%f\033[0m", glob_passenger_happiness);
    } else if (glob_passenger_happiness > 0.0) {
        Print("\nPassenger happiness: \033[1;32m%f\033[0m", glob_passenger_happiness);
    } else {
        Print("\nPassenger happiness: %f", glob_passenger_happiness);
    }

    Print("\n");
}
