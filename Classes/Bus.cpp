#include "Bus.h"
Bus::Bus(int startStop, double waitTimeStop)
{
    startBusStop = startStop;
    waitTimeToFirstStop = waitTimeStop;
}

void Bus::SetActualBusOrPutProcessInQueue()
{
    shouldBeQueued = true;

    for (int i = 0; i < AMOUNT_OF_BUSES; i++) {
        if (! busFacility[i].Busy()) {
            actualBus = i;
            shouldBeQueued = false;
            break;
        }
    }
}

void Bus::BusMovement()
{
    int currentBusStop = startBusStop;

    // Array of required bus stops
    FirstBusStop firstBusStop(actualBus);
    SecondBusStop secondBusStop(actualBus);
    BusStop* requiredBusStopsArray[2] = {&firstBusStop, &secondBusStop};

    while(currentBusStop < (glob_amount_of_bus_stops - 1))
    {
        Print("\n[Time: [%f]]\tAutobus číslo [%d] vyřáží do další zastávky.", Time, (actualBus + 1));

        // Traffic Jam occurred
        if(Random() <= (glob_traffic_jam_rate / 100))
        {
            double waitTime = Exponential(glob_traffic_jam_wait_time);
            Print("\n[Time: [%f]]\tAutobus číslo [%d] se dostal do zácpy a zdrží se [%f].", Time, (actualBus + 1), waitTime);
            Wait(waitTime);
        }

        // If bus is replacement bus, it will take some time to reach accident site
        double waitTime = (waitTimeToFirstStop != 0.0) ? waitTimeToFirstStop : Exponential(glob_time_between_stops);
        Wait(waitTime);
        waitTimeToFirstStop = 0.0;


        requiredBusStopsArray[currentBusStop]->Activate();
//        Passivate();



        // Accident happened at bus stop exit
        if(Random() <= (glob_accident_rate / 100.0))
        {
            (new Accident(actualBus, currentBusStop))->Activate();
            Release(busFacility[actualBus]);
            return;
        }

        currentBusStop++;
    }

    Release(busFacility[actualBus]);
}

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

    Seize(busFacility[actualBus]);
    Print("\n[Time: [%f]]\tAutobus s číslem [%d] byl vyslán na linku.", Time, (actualBus + 1));

    BusMovement();

    if (waitingForBusDispatch.Length() > 0)
    {
        (waitingForBusDispatch.GetFirst())->Activate();
    }
}