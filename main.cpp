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
void printStatistics() {
    Print("\n\n================================================================================");
    Print("\n\t\t\t\tSTATISTICS:");
    Print("\n================================================================================\n");

    Print("\nSuccessfully dispatched buses on schedule: %d / %d",
          glob_total_amount_of_dispatched_buses - glob_amount_of_unsuccessfully_dispatched_buses,
          glob_total_amount_of_dispatched_buses);

    Print("\nUnused buses: %d\n", glob_amount_of_buses - (glob_max_bus_number_used + 1));

    double totalTimeInTrafficJam = 0;
    for (int i = 0; i < (int)glob_time_spent_in_traffic_jam.size(); i++) {
        totalTimeInTrafficJam += glob_time_spent_in_traffic_jam[i];
    }

    if (glob_passenger_happiness < -10.0) {
        Print("\nPassenger happiness: \033[1;31mBelow Average\033[0m");
    } else if (glob_passenger_happiness > 10.0) {
        Print("\nPassenger happiness: \033[1;32mAbove Average\033[0m");
    } else {
        Print("\nPassenger happiness: Average");
    }

    Print("\nAverage time in traffic jam: %f", totalTimeInTrafficJam <= 0 ? 0 : totalTimeInTrafficJam / (double)(glob_total_amount_of_dispatched_buses - glob_amount_of_unsuccessfully_dispatched_buses));
    Print("\n\nModel output: ");
    Print("\n================================================================================\n");
    // There is high amount of unused buses, but people are happy
    if ((glob_amount_of_buses - (glob_max_bus_number_used + 1)) > 1 && glob_passenger_happiness > -10.0) {
        Print("\033[1;33mSome buses could be omitted, but people are not unhappy.\033[0m");
    }
    // There is high amount of unused buses and people are unhappy
    else if ((glob_amount_of_buses - (glob_max_bus_number_used + 1)) > 1 && glob_passenger_happiness < -10.0) {
        Print("\03[1;31mNot optimal solution. There are some unused buses and people are unhappy, you should increase the intensity of bus dispatches.\033[0m");
    }
    // There is optimal amount of buses and people are happy
    else if ((glob_amount_of_buses - (glob_max_bus_number_used + 1)) <= 1 && glob_passenger_happiness > -10.0) {
        Print("\033[1;32mOptimal solution. There is just enough buses and people are not unhappy.\033[0m");
    }
    else {
        Print("\033[1;31mNot optimal solution. You should either increase a number of buses or decrease the intensity of bus dispatches. "
              "Optimal solution of this depends on current intensity and amount of traffic jams.\033[0m");
    }
    Print("\n================================================================================");
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

    if(glob_enable_random_seed) {
        RandomSeed(time(NULL));
    }

    Init(0, glob_time_to);
    (new BusDispatcher)->Activate();

    Run();

    // Statistics
    printStatistics();
}
