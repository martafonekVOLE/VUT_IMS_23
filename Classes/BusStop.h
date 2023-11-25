#include <simlib.h>
#ifndef DOPRAVA_BUSSTOP_H
#define DOPRAVA_BUSSTOP_H

class BusStop: public Process
{
public:
    int busNumber;

    explicit BusStop(int bus);

    void ReleasePassengers();

    void CollectNewPassengers();
};


#endif //DOPRAVA_BUSSTOP_H
