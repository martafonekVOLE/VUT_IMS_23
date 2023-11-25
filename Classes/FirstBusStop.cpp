//
// Created by martafonek on 22.11.23.
//

#include <iostream>

#include "FirstBusStop.h"
#include "Bus.h"

FirstBusStop::FirstBusStop(int bus) : BusStop(bus) {
}

void FirstBusStop::Behavior()
{
    rerunAfterActivation:
    int stop = -1;

    for (int i = 0; i < AMOUNT_OF_STOP_SPOTS; i++) {
        if(!firstBusStopFacility[i].Busy())
        {
            stop = i;
            break;
        }
    }
    if (stop == -1)
    {
        firstBusStopQueue.Insert(this);
        Passivate();
        goto rerunAfterActivation;
    }
    else
    {
        Wait(1);
    }

    if (firstBusStopQueue.Length() > 0)
    {
        (firstBusStopQueue.GetFirst())->Activate();
    }
}
