//
// Created by martafonek on 22.11.23.
//
#include "BusStop.h"
#include "../arg_parse.h"
BusStop::BusStop(int bus)
{
    busNumber = bus;
}

void BusStop::ReleasePassengers()
{
    Wait(Exponential(1)); //todo glob
}

void BusStop::CollectNewPassengers()
{
    Wait(Exponential(1)); //todo glob
}