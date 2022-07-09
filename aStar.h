/**
 * John KULOTH
 * Harsh SAHU
 */

#ifndef __ASTAR_H
#define __ASTAR_H

#include "List.h"
#include "City.h"

/**
 * function to compare if current neighbor is a city in the .MAP file
 * @param c the city to be checked
 * @return 1 if current neighbor name is equal to the city name
 * @return 0 otherwise
 */
int isNamed(void * c);

/**
 * function to visit each neighbor of a city
 * @param cityList the list of cities read from the MAP file
 * @param openList the OPEN list
 * @param closeList the CLOSE list
 * @param city the current city
 */
void forEachNeighbor(List* cityList, List* openList, List* closeList, City* city);

/**
 * function to find shortest path between two cities using A* algorithm
 * @param cityList the list of cities read from the MAP file
 * @param openList the OPEN list
 * @param closeList the CLOSE list
 * @param startCity the start city
 * @param goalCity the destination city
 * @param res the final path that found by the algorithm
 * @return 1 if final path is found successfully
 * @return 0 otherwise
 */
int findShortestPath(List* cityList, List* openList, List* closeList, City* startCity, City* goalCity, List* res);

void printPath(List *l, City *city);

#endif //__ASTAR_H
