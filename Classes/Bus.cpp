/**
 * @project Model logistiky - hromadná osobní přeprava, IMS
 * @brief Implementation of Bus.h, implements bus behavior and random events
 *
 * @file Bus.cpp
 * @date 21.11.2023
 *
 * @author Martin Pech (xpechm00)
 * @author Josef Škorpík (xskorp07)
 */

#include "Bus.h"
#include "../arg_parse.h"
#include <cmath>
#include <vector>
#include <algorithm>

/**
 * @inheritDoc
 */
Bus::Bus(int startStop, double waitTimeStop, int spareFor, int people)
{
    startBusStop = startStop + 1;
    waitTimeToFirstStop = waitTimeStop;
    spareBusFor = spareFor;
    capacity = glob_bus_capacity;

    if(startStop != -1)
    {
        isSpareBus = true;
        peopleInBus = people;
        Print("\n[Time: %f]\tNáhradní autobus vyřáží do zastávky [%d]. Cesta mu zabere [%f].", Time, startStop+1, waitTimeStop);
    }
    else
    {
        SetActualBusOrPutProcessInQueue();
        if(shouldBeQueued)
        {
            glob_amount_of_unsuccessfully_dispatched_buses++;
        }
    }
}

/**
 * @inheritDoc
 */
void Bus::SetActualBusOrPutProcessInQueue()
{
    shouldBeQueued = true;
    for (int i = 0; i < glob_amount_of_buses; i++) {
        if (! glob_bus_facility[i].Busy()) {
            actualBus = i;
            glob_max_bus_number_used = actualBus > glob_max_bus_number_used ? actualBus : glob_max_bus_number_used;

            shouldBeQueued = false;
            break;
        }
    }
}

/**
 * @inheritDoc
 */
void Bus::BusMovement()
{
    int currentBusStop = startBusStop;

    if(isSpareBus){
        Wait(waitTimeToFirstStop);
        Print("\n[Time: %f]\tAutobus číslo [%d] přeložil cestující a není ho již možné použít.", Time, spareBusFor + 1);
    }

    while(currentBusStop < (glob_amount_of_bus_stops - 1))
    {
        Print("\n[Time: %f]\tAutobus číslo [%d] vyřáží do další zastávky.", Time, (actualBus + 1));

        // Traffic Jam occurred
        DecideAboutTrafficJam();

        // If bus is replacement bus, it will take some time to reach accident site
        if(! isSpareBus)
        {
            double waitTime = (waitTimeToFirstStop != 0.0) ? waitTimeToFirstStop : Normal(glob_time_between_stops, 3);
            Wait(waitTime);
            waitTimeToFirstStop = 0.0;
        }
        else
        {
            isSpareBus = false;
        }

        HandleBusStop(currentBusStop);

        // Accident happened at bus stop exit
        if(AccidentOccurred(currentBusStop))
        {
            return;
        }

        currentBusStop += 1;
    }

    for (int i = 0; i < peopleInBus; i++) {
        glob_passenger_happiness += round(Uniform(1, 3));
    }

    Print("\n[Time: %f]\tAutobus číslo [%d] dokončil linku a vrací se zpět.", Time, (actualBus + 1));
    Release(glob_bus_facility[actualBus]);
}

/**
 * @inheritDoc
 */
void Bus::HandleBusStop(int currentBusStop)
{
    rerunAfterActivation:

    if (! glob_bus_stops_vector[currentBusStop][0].Busy()) {
        Seize(glob_bus_stops_vector[currentBusStop][0]);
        Print("\n[Time: %f]\tAutobus číslo [%d] je v zastávce [%d].", Time, (actualBus + 1), (currentBusStop + 1));

        int maxPeopleLeavingBus = glob_max_amount_of_people_leaving_bus_before_final_stop > peopleInBus ? peopleInBus : glob_max_amount_of_people_leaving_bus_before_final_stop;
        if(peopleInBus > 0)
        {
            peopleInBus -= round(Uniform(0, maxPeopleLeavingBus));
        }

        int peopleWaitingForBus = round(Uniform(0, glob_max_amount_of_people_waiting_for_bus));
        if (capacity >= (peopleInBus + peopleWaitingForBus))
        {
            peopleInBus += peopleWaitingForBus;
        }
        else
        {
            int peopleGettingIntoBus = capacity - peopleInBus;
            int peopleWaitingForNextBus = peopleWaitingForBus - peopleGettingIntoBus;
            Print("\n[Time: %f]\tDo autobusu se nevešlo [%d] lidí.", peopleWaitingForNextBus);

            for (int i = 0; i < peopleWaitingForNextBus; i++) {
                glob_passenger_happiness -= round(Uniform(1, 2));
            }
        }

        Wait(Exponential(3));
        Release(glob_bus_stops_vector[currentBusStop][0]);

        if(glob_bus_stop_queues_vector[currentBusStop]->Length() > 0)
        {
            (glob_bus_stop_queues_vector[currentBusStop]->GetFirst())->Activate();
        }

        return;
    }
    Print("\n[Time: %f]\tAutobus číslo [%d] čeká na zastávku.", Time, (actualBus + 1));
    glob_bus_stop_queues_vector[currentBusStop]->Insert(this);
    Passivate();
    goto rerunAfterActivation;
}

/**
 * @inheritDoc
 */
void Bus::DecideAboutTrafficJam()
{
    if(Random() <= (glob_traffic_jam_rate / 100.0))
    {
        double waitTime = Exponential(glob_traffic_jam_wait_time);

        Print("\n[Time: %f]\t\033[1;33mAutobus číslo [%d] se dostal do zácpy a zdrží se [%f].\033[0m", Time, (actualBus + 1), waitTime);
        glob_time_spent_in_traffic_jam.push_back(waitTime);
        Wait(waitTime);

        for (int i = 0; i < peopleInBus; ++i) {
            glob_passenger_happiness -= round(Uniform(0, 1));
        }
    }
}

/**
 * @inheritDoc
 */
bool Bus::AccidentOccurred(int currentBusStop)
{
    if(currentBusStop + 1 == glob_amount_of_bus_stops)
    {
        return false;
    }

    if(Random() <= (glob_accident_rate / 100.0))
    {
        (new Accident(actualBus, currentBusStop, peopleInBus))->Activate();
        return true;
    }
    return false;
}

/**
 * @inheritDoc
 */
void Bus::Behavior()
{
    rerunAfterActivation:
    SetActualBusOrPutProcessInQueue();
    if (shouldBeQueued) {
        if(isSpareBus) {
            waitingForBusDispatchWithPriority.Insert(this);
        } else {
            waitingForBusDispatch.Insert(this);
        }
        Print("\n[Time: %f]\t\033[1;35mPožadavek na vyslání autobusu byl zařazen do fronty.\033[0m", Time);
        Passivate();

        for (int i = 0; i < glob_amount_of_bus_stops * round(Uniform(0,glob_max_amount_of_people_waiting_for_bus)); i++) {
            glob_passenger_happiness -= round(Uniform(0,1));
        }

        goto rerunAfterActivation;
    }

    Seize(glob_bus_facility[actualBus]);

    Print("\n[Time: %f]\tAutobus s číslem [%d] byl vyslán na linku.", Time, (actualBus + 1));

    BusMovement();

    // Activates Spare Bus
    if(waitingForBusDispatchWithPriority.Length() > 0)
    {
        (waitingForBusDispatchWithPriority.GetFirst())->Activate();
    }

    if (waitingForBusDispatch.Length() > 0)
    {
        (waitingForBusDispatch.GetFirst())->Activate();
    }
}