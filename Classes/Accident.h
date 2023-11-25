#include <simlib.h>

#ifndef DOPRAVA_ACCIDENT_H
#define DOPRAVA_ACCIDENT_H


class Accident: public Process
{
public:
    int busNumber;
    int busStop;

    /**
     * Construct
     *
     * @param bus
     * @param stop
    */
    Accident(int bus, int stop);

    /**
     * Behavior describes behavior of Accident
     */
    void Behavior() override;
};


#endif //DOPRAVA_ACCIDENT_H
