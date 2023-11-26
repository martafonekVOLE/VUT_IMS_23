#include "Bus.h"
#include "../arg_parse.h"

/**
 * @inheritDoc
 */
Bus::Bus(int startStop, double waitTimeStop)
{
    startBusStop = startStop;
    waitTimeToFirstStop = waitTimeStop;
}

/**
 * @inheritDoc
 */
void Bus::SetActualBusOrPutProcessInQueue()
{
    shouldBeQueued = true;

    // todo glob i < AMOUNT_OF_BUSES
    for (int i = 0; i < 4; i++) {
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

    while(currentBusStop < (glob_amount_of_bus_stops - 1))
    {
        Print("\n[Time: [%f]]\tAutobus číslo [%d] vyřáží do další zastávky.", Time, (actualBus + 1));

        // Traffic Jam occurred
        DecideAboutTrafficJam();

        // If bus is replacement bus, it will take some time to reach accident site
        double waitTime = (waitTimeToFirstStop != 0.0) ? waitTimeToFirstStop : Exponential(glob_time_between_stops);
        Wait(waitTime+20);
        waitTimeToFirstStop = 0.0;

        HandleBusStop();

        // Accident happened at bus stop exit
        if(AccidentOccurred(currentBusStop))
        {
            return;
        }

        currentBusStop++;
    }

    Print("\n[Time: [%f]]\tAutobus číslo [%d] dokončil linku a vrací se zpět.", Time, (actualBus + 1));
    Release(glob_bus_facility[actualBus]);
}

/**
 * @inheritDoc
 */
void Bus::HandleBusStop()
{
    rerunAfterActivation:

    if (! firstBusStopFacility[0].Busy()) {
        Seize(firstBusStopFacility[0]);
        Print("\n[Time: [%f]]\tAutobus číslo [%d] je v zastávce.", Time, (actualBus + 1));
        Wait(Exponential(3));
        Release(firstBusStopFacility[0]);

        return;
    }
    Print("\n[Time: [%f]]\tAutobus číslo [%d] čeká na zastávku.", Time, (actualBus + 1));
    firstBusStopQueue.Insert(this);
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
        Release(glob_bus_facility[actualBus]);
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
        waitingForBusDispatch.Insert(this);
        Print("\n[Time: [%f]]\tPožadavek na vyslání autobusu byl zařazen do fronty.", Time);
        Passivate();

        goto rerunAfterActivation;
    }

    Seize(glob_bus_facility[actualBus]);
    Print("\n[Time: [%f]]\tAutobus s číslem [%d] byl vyslán na linku.", Time, (actualBus + 1));

    BusMovement();

    if (waitingForBusDispatch.Length() > 0)
    {
        (waitingForBusDispatch.GetFirst())->Activate();
    }
}