/**
 * @project Model logistiky - hromadná osobní přeprava, IMS
 * @brief Main file with program logic
 *
 * @file main.cpp
 * @date 21.11.2023
 *
 * @author Martin Pech (xpechm00)
 * @author xxx
 */

#include <simlib.h>
#include <vector>

#include "arg_parse.h"
#include "Classes/Bus.h"

/**
 * New Bus Generator
 */
class BusDispatcher: public Event
{
    void Behavior() override
    {
        (new Bus())->Activate();

        Activate(Time + glob_time_between_bus_starts);
        Print("\n[Time: [%f]]\tAutobus by měl nyní vyjet podle jízdního řádu.", Time);
    }
};

/**
 * Main function
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    // Parsing arguments
    arg_parse(argc, argv);

    Init(0, glob_time_to);
    (new BusDispatcher)->Activate();

    Run();
    // pro každoou zastávku aktivovat příchody lidí

}
