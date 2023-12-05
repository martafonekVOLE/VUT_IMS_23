/**
 * @project Model logistiky - hromadná osobní přeprava, IMS
 * @brief Argument parsing
 *
 * @file arg_parse.cpp
 * @date 21.11.2023
 *
 * @author Martin Pech (xpechm00)
 * @author xxx
 */

#include "arg_parse.h"
#include <getopt.h>
#include <iostream>
#include <cstdlib>
#include <string>

/**
 * Constants definition
 */
const char TIME = 't';
const char ACCIDENT_RATE = 'a';
const char AMOUNT_OF_BUSES = 'b';
const char AMOUNT_OF_STOPS = 's';
const char TIME_BETWEEN_STOPS = 'l';
const char TRAFFIC_JAM_RATE = 'j';
const char TIME_BETWEEN_BUS_STARTS = 'g';
const char WAIT_TIME_IN_TRAFFIC_JAM = 'w';
const char CAPACITY = 'c';

/**
 * Global variables initialization
 */
double glob_time_to = 300;

double glob_accident_rate = 20.0;

double glob_traffic_jam_rate = 15.0;

double glob_traffic_jam_wait_time = 5.0;

int glob_amount_of_buses = 5;

int glob_amount_of_bus_stops = 5;

double glob_time_between_stops = 15.0;

double glob_time_between_bus_starts = 30.0;

int glob_bus_capacity = 75;

// todo add optarg
int glob_max_amount_of_people_waiting_for_bus = 15;
int glob_max_amount_of_people_leaving_bus_before_final_stop = 5;

double glob_passenger_happiness = 0;

Facility glob_bus_facility[MAX_AMOUNT_OF_BUSES];

Facility glob_bus_stops_facility[MAX_AMOUNT_OF_STOPS];

std::vector<Queue*> glob_bus_stop_queues_vector;

std::vector<Facility*> glob_bus_stops_vector;

Queue waitingForBusDispatch;

Queue waitingForBusDispatchWithPriority;

/**
 * Constructor
 *
 * Handles argument parsing, sets global variables
 *
 * @param argc
 * @param argv
 */
void arg_parse(int argc, char *argv[]) {
    int option = 0;

    while ((option = getopt(argc, argv, "t:a:b:s:l:j:g:w:c")) != -1)
    {
        switch (option) {
            case TIME:
            {
                double newTimeTo = std::stof(optarg);
                if (newTimeTo < 0)
                {
                    std::cerr << "Argument TIME vyžaduje kladné číslo. Argument reprezentuje simulační čas." << std::endl;
                    exit(1);
                }

                glob_time_to = newTimeTo;
                break;
            }

            case ACCIDENT_RATE:
            {
                double newFailureRate = std::stof(optarg);
                if (newFailureRate > 1 || newFailureRate < 0)
                {
                    std::cerr << "Argument FAILURE RATE vyžaduje číslo z intervalu <0,1>. Číslo reprezentuje pravděpodobnost výskytu chyby." << std::endl;
                    exit(1);
                }

                glob_accident_rate = newFailureRate;
                break;
            }

            case AMOUNT_OF_BUSES:
            {
                int newBusAmount = std::stoi(optarg);
                if (newBusAmount < 1)
                {
                    std::cerr << "Argument AMOUNT OF MAX_AMOUNT_OF_BUSES vyžaduje celé kladné číslo (kromě nuly). Číslo reprezentuje počet autobusů." << std::endl;
                    exit(1);
                }

                glob_amount_of_buses = newBusAmount;
                break;
            }

            case AMOUNT_OF_STOPS:
            {
                int newStopsAmount = std::stoi(optarg);
                if(newStopsAmount < 1)
                {
                    std::cerr << "Argument AMOUNT OF BUS STOPS vyžaduje celé kladné číslo (kromě nuly). Číslo reprezentuje počet autobusových zastávek na trase." << std::endl;
                    exit(1);
                }

                glob_amount_of_bus_stops = newStopsAmount;
                break;
            }

            case TIME_BETWEEN_STOPS:
            {
                double newTimeBetweenStops = std::stof(optarg);
                if (newTimeBetweenStops < 0)
                {
                    std::cerr << "Argument TIME BETWEEN STOPS vyžaduje číslo větší než nula. Číslo reprezentuje dobu přejezdu mezi zastávkami." << std::endl;
                    exit(1);
                }

                glob_time_between_stops = newTimeBetweenStops;
                break;
            }

            case TIME_BETWEEN_BUS_STARTS:
            {
                double newTimeBetweenBusStarts = std::stof(optarg);
                if (newTimeBetweenBusStarts < 0.0)
                {
                    std::cerr << "Argument TIME BETWEEN BUS STARTS vyžaduje číslo větší než nula. Číslo reprezentuje dobu, po které je vyslán nový autobus." << std::endl;
                    exit(1);
                }

                glob_time_between_bus_starts = newTimeBetweenBusStarts;
                break;
            }

            case WAIT_TIME_IN_TRAFFIC_JAM:
            {
                double newTimeInTrafficJam = std::stof(optarg);
                if (newTimeInTrafficJam < 0.0)
                {
                    std::cerr << "Argument TIME IN TRAFFIC JAM vyžaduje číslo větší nebo rovno nule. Číslo reprezentuje dobu, po kterou stojí autobus v zácpě." << std::endl;
                    exit(1);
                }

                glob_traffic_jam_wait_time = newTimeInTrafficJam;
                break;
            }

            case CAPACITY:
            {
                int newCapacity = std::stoi(optarg);
                if(newCapacity < 1)
                {
                    std::cerr << "Argument CAPACITY vyžaduje číslo větší nebo rovno jedné. Číslo reprezentuje kapacitu autobusu." << std::endl;
                    exit(1);
                }
                std::cerr << "TEST" << std::endl;

                glob_bus_capacity = newCapacity;
                break;
            }

            default:
            {
                exit(1);
            }
        }
    }

    for (int i = 0; i < glob_amount_of_bus_stops; i++)
    {
        glob_bus_stops_vector.push_back(new Facility);
        glob_bus_stop_queues_vector.push_back(new Queue);
    }
}