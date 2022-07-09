/**
 * John KULOTH
 * Harsh SAHU
 */

#include "aStar.h"
#include <string.h>
#include <stdio.h>

static Neighbor *currentNeighbor = NULL;

/** compare if current neighbor is a city in the .MAP file */
int isNamed(void * c) {
    City *city = c;
    return strcasecmp(city->name, currentNeighbor->name) == 0;
}

/** visit each neighbor of a city */
void forEachNeighbor(List* cityList, List* openList, List* closeList, City* city) {
    currentNeighbor = city->neighbors;
    while (currentNeighbor) {
        /* find if current neighbor is a city in the .MAP file and store to a city type */
        City* c = firstThat(cityList, isNamed);
        if (c!=0) {
            /* compute g(n) + c(n,si) */
            int g = city->distFromStart + currentNeighbor->distance;
            /* if si is in OPEN or CLOSED list and g(n) + c(n,si) > g(si) */
            if ((isInList(openList, c) || isInList(closeList, c)) && g>c->distFromStart) {
                /* skip to next neighbor */
                currentNeighbor = currentNeighbor->next;
                continue;
            }
            /* if si is in OPEN or CLOSED, remove si from list */
            if (isInList(openList, c)) remFromList(openList, c);
            if (isInList(closeList, c)) remFromList(closeList, c);
            /* update g(si) and back-path pointer then insert si in OPEN */
            c->distFromStart = g;
            c->preCity = city;
            addList(openList, c);
        }
        currentNeighbor = currentNeighbor->next;
    }
}

/** find shortest path between two cities using A* algorithm */
int findShortestPath(List* cityList, List* openList, List* closeList, City* startCity, City* goalCity, List* res) {
    /* add start city in OPEN */
    addList(openList, startCity);
    City* currentCity = startCity;
    /* if goal city has not been found */
    while (currentCity != goalCity) {
        /* if OPEN is empty -> failure */
        if (lengthList(openList) == 0) {
            return 0;
        }
        /* remove the city with minimal F from OPEN list */
        remFromListAt(openList, 1, &currentCity);
        /* add that city to CLOSED list */
        addList(closeList, currentCity);
        /* if goal city is found */
        if (currentCity == goalCity) {
            while (currentCity->preCity) {
                /* add city and its back-path to result list */
                addListAt(res, 1, currentCity);
                currentCity = currentCity->preCity;
            }
            addListAt(res, 1, currentCity);
            return 1;
        }
        /* visit each neighbor */
        forEachNeighbor(cityList, openList, closeList, currentCity);
    }
}

/* find distance between each city */
void printPath(List *l, City *city){
    City *current = city;
    List *path = newList(l->comp, l->pr);
    if (!path){
        return;
    }
    status res = addList(path, current);
    if (res != OK){
        delList(path);
        return;
    }
    while (current){
        current = current->preCity;
        if (current){
            res = addListAt(path, 1, current);
            if (res != OK){
                delList(path);
                return;
            }
        }
    }
    Node *node = path->head;
    /* to print the city with the total distance upto */
    while (node){
        City *city = node->val;
        printf("%s : (", city->name);
        printf("%d km)\n", city->distFromStart);
        node = node->next;
    }
}