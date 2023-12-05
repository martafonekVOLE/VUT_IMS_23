/**
 * @project Model logistiky - hromadná osobní přeprava, IMS
 * @brief Argument parsing
 *
 * @file arg_parse.h
 * @date 21.11.2023
 *
 * @author Martin Pech (xpechm00)
 * @author Josef Škorpík (xskorp07)
 */

#include <simlib.h>
#include <vector>

#ifndef DOPRAVA_ARG_PARSE_H
#define DOPRAVA_ARG_PARSE_H

#define MAX_AMOUNT_OF_BUSES 100
#define MAX_AMOUNT_OF_STOPS 100

class arg_parse {

};

// Global variable - end of sim time
extern double glob_time_to;

// Global variable - bus failure rate
extern double glob_accident_rate;

// Global variable - traffic jam rate
extern double glob_traffic_jam_rate;

// Global variable - traffic jam wait time
extern double glob_traffic_jam_wait_time;

// Global variable - amount of buses
extern int glob_amount_of_buses;

// Global variable - amount of bus stops
extern int glob_amount_of_bus_stops;

// Global variable - time between stops
extern double glob_time_between_stops;

// Global variable - time between bus starts
extern double glob_time_between_bus_starts;

// Global variable - how many buses can be in one station
extern int glob_amount_of_bus_spots_on_bus_stop;

extern double glob_passenger_happiness;

extern int glob_bus_capacity;

extern int glob_max_amount_of_people_waiting_for_bus;

extern int glob_max_amount_of_people_leaving_bus_before_final_stop;

extern Facility glob_bus_facility[MAX_AMOUNT_OF_BUSES];

extern Queue waitingForBusDispatch;

extern Queue waitingForBusDispatchWithPriority;

extern std::vector<Facility*> glob_bus_stops_vector;

extern std::vector<Queue*> glob_bus_stop_queues_vector;

extern Facility glob_bus_stops_facility[MAX_AMOUNT_OF_STOPS];

void arg_parse(int argc, char *argv[]);

#endif //DOPRAVA_ARG_PARSE_H
