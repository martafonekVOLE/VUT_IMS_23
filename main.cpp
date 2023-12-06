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
#include <vector>
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
        glob_total_amount_of_dispatched_buses++;

        Activate(Time + glob_time_between_bus_starts);
        Print("\n[Time: %f]\t\033[1;32mAutobus by měl nyní vyjet podle jízdního řádu.\033[0m", Time);
    }
};

/**
 * Prints statistics
 */
void printStatistics()
{
    Print("\n\n================================================================================");
    Print("\n\t\t\t\tSTATISTICS:");
    Print("\n================================================================================\n");

    Print("\nSuccessfully dispatched buses on schedule: %d / %d",
          glob_total_amount_of_dispatched_buses - glob_amount_of_unsuccessfully_dispatched_buses,
          glob_total_amount_of_dispatched_buses);

    double totalTimeInTrafficJam = 0;
    for (int i = 0; i < glob_time_spent_in_traffic_jam.size(); i++) {
        totalTimeInTrafficJam += glob_time_spent_in_traffic_jam[i];
    }


    Print("\nAverage time in traffic jam: %f", totalTimeInTrafficJam <= 0 ? 0 : totalTimeInTrafficJam/static_cast<double>(glob_time_spent_in_traffic_jam.size()));

    if(glob_passenger_happiness < -10.0)
    {
        Print("\nPassenger happiness: \033[1;31mBelow Average\033[0m");
    } else if (glob_passenger_happiness > 10.0) {
        Print("\nPassenger happiness: \033[1;32mAbove Average\033[0m");
    } else {
        Print("\nPassenger happiness: Average");
    }

    Print("\nUnused buses: %d", glob_amount_of_buses - (glob_max_bus_number_used + 1));

    Print("\n");
}

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

    // Statistics
    printStatistics();
}
