#include <simlib.h>

#ifndef DOPRAVA_ACCIDENT_H
#define DOPRAVA_ACCIDENT_H


class Accident: public Process
{
public:
    int busNumber;
    int busStop;
    int people;

    /**
     * Construct
     *
     * @param bus
     * @param stop
    */
    Accident(int bus, int stop, int peopleInBus);

    /**
     * Behavior describes behavior of Accident
     */
    void Behavior() override;
};


#endif //DOPRAVA_ACCIDENT_H
