/**
 * @project Model logistiky - hromadná osobní přeprava, IMS
 * @brief Accident Process Header file
 *
 * @file Accident.h
 * @date 21.11.2023
 *
 * @author Martin Pech (xpechm00)
 * @author Josef Škorpík (xskorp07)
 */

#include <simlib.h>

#ifndef DOPRAVA_ACCIDENT_H
#define DOPRAVA_ACCIDENT_H

/**
 * Class Definition
 */
class Accident: public Process
{

/**
 * Public scope
 */
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
     * Describes behavior of Accident
     */
    void Behavior() override;
};


#endif
