/**
 * John KULOTH
 * Harsh SAHU
 */


#ifndef __GRAPH_H
#define __GRAPH_H

#include <stdlib.h>
#include "status.h"

/**
 * A linked list of neighbors
 */
typedef struct Neighbor {
    char *name;
    int distance;
    struct Neighbor *next;
} Neighbor;

/**
 * A type of City, containing a list of neighbors and a pointer to previous visited city
 */
typedef struct City {
    char *name;
    int latitude, longitude;
    int distFromStart, distToGoal;
    int neighborCount;
    struct Neighbor *neighbors;
    struct City *preCity;
} City;

/**
 * Function for adding neighbor to an existing city
 * @param city that needed to add neighbors
 * @param name the name of neighbor
 * @param distance the distance from the city to that neighbor
 */
status insertNeighborToCity(City *city, char *name, int distance);

/**
 * Function to create new city that identified by name, latitude, and longitude
 * @param name the name of city
 * @param latitude the latitude of city
 * @param longitude the longitude of city
 * @return a city with name, latitude, and longitude
 * @return NULL otherwise
 */
City* newCity(char *name, int latitude, int longitude);

/**
 * Function to create new neighbor
 * @param name the name of neighbor
 * @param distance the distance from the city to the neighbor
 * @return a neighbor with name and distance
 * @return NULL otherwise
 */
Neighbor* newNeighbor(char *name, int distance);

/**
 * destroy the city by deallocating used memory
 * @param city the city to be destroyed
 */
void delCity(City *city);

/**
 * destroy the neighbor by deallocating used memory
 * @param neighbor the neighbor to be destroyed
 */
void delNeighbor(Neighbor *neighbor);

#endif //__GRAPH_H
