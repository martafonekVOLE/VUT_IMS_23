#include "Bus.h"
#include "../arg_parse.h"

/**
 * @inheritDoc
 */
Bus::Bus(int startStop, double waitTimeStop, int spareFor)
{
    startBusStop = startStop + 1;
    waitTimeToFirstStop = waitTimeStop;
    spareBusFor = spareFor;

    if(startStop != -1)
    {
        isSpareBus = true;
        Print("\n[Time: [%f]]\tNáhradní autobus číslo vyřáží do zastávky [%d]. Cesta mu zabere [%f].", Time, startStop+1, waitTimeStop);
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
        // todo exponential as global and separate
        Wait(waitTimeToFirstStop);
        Print("\n[Time: [%f]]\tAutobus číslo [%d] přeložil cestující a není ho již možné použít.", Time, spareBusFor + 1);
    }

    while(currentBusStop < (glob_amount_of_bus_stops - 1))
    {
        Print("\n[Time: [%f]]\tAutobus číslo [%d] vyřáží do další zastávky.", Time, (actualBus + 1));

        DecideAboutTrafficJam();

        // If bus is replacement bus, it will take some time to reach accident site
        double waitTime = (waitTimeToFirstStop != 0.0) ? waitTimeToFirstStop : Exponential(glob_time_between_stops);
        Wait(waitTime+20);
        waitTimeToFirstStop = 0.0;

        HandleBusStop(currentBusStop);

        // Accident happened at bus stop exit
        // todo test accident att last stop
        if(AccidentOccurred(currentBusStop))
        {
            return;
        }

        currentBusStop += 1;
    }

    Print("\n[Time: [%f]]\tAutobus číslo [%d] dokončil linku a vrací se zpět.", Time, (actualBus + 1));
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
        Print("\n[Time: [%f]]\tAutobus číslo [%d] je v zastávce [%d].", Time, (actualBus + 1), (currentBusStop + 1));
        Wait(Exponential(3));
        Release(glob_bus_stops_vector[currentBusStop][0]);

        if(glob_bus_stop_queues_vector[currentBusStop]->Length() > 0)
        {
            (glob_bus_stop_queues_vector[currentBusStop]->GetFirst())->Activate();
        }

        return;
    }
    Print("\n[Time: [%f]]\tAutobus číslo [%d] čeká na zastávku.", Time, (actualBus + 1));
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
        Print("\n[Time: [%f]]\tAutobus číslo [%d] se dostal do zácpy a zdrží se [%f].", Time, (actualBus + 1), waitTime);
        Wait(waitTime);
    }
}

/**
 * @inheritDoc
 */
bool Bus::AccidentOccurred(int currentBusStop)
{
    if(Random() <= (glob_accident_rate / 100.0))
    {
        (new Accident(actualBus, currentBusStop))->Activate();
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
        Print("\n[Time: [%f]]\tPožadavek na vyslání autobusu byl zařazen do fronty.", Time);
        Passivate();

        goto rerunAfterActivation;
    }

    Seize(glob_bus_facility[actualBus]);

    Print("\n[Time: [%f]]\tAutobus s číslem [%d] byl vyslán na linku.", Time, (actualBus + 1));

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