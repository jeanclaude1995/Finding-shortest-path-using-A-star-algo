/**
 * John KULOTH
 * Harsh SAHU
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "City.h"
#include "aStar.h"
#include "status.h"

/** static to store filename, start and goal city and their names */
static char* fileName;
static char* startName;
static char* goalName;
static City* startCity = NULL;
static City* goalCity = NULL;

/**
 * function to compare city by name alphabetically
 * @param s1 the first city
 * @param s2 the second city
 * @return <0 if s1->name is less than s2->name
 * @return 0 if s1->name equals s2->name
 * @return >0 otherwise
 */
static int compCityByName (void * s1, void * s2) {
    City* c1 = s1;
    City* c2 = s2;
    return strcasecmp(c1->name, c2->name);
}

/**
 * function to compare cities by their F = G + H to sort the OPEN list
 * @param s1 the first city
 * @param s2 the second city
 * @return <0 if s1->f is less than s2->f
 * @return 0 if s1->f equals s2->f
 * @return >0 otherwise
 */
static int compCityByF (void * s1, void * s2) {
    City* c1 = s1;
    City* c2 = s2;
    return ((c1->distFromStart + c1->distToGoal) < (c2->distFromStart + c2->distToGoal)) ? -1 : ((c1->distFromStart + c1->distToGoal) > (c2->distFromStart + c2->distToGoal));
}

/**
 * function to display a list of city in details
 * @param s the city to be displayed
 */
static void prCity(void * s) {
    City* city = s;
    printf("\nCity: %s", city->name);
    printf("\nL1: %d, L2: %d", city->latitude, city->longitude);
    printf("\nG: %d, H: %d", city->distFromStart, city->distToGoal);
    Neighbor* neighbor = city->neighbors;
    printf("\nNeighbors: %d", city->neighborCount);
    while(neighbor!=NULL){
        printf("\nName: %s\tDistance: %d", neighbor->name, neighbor->distance);
        neighbor=neighbor->next;
    }
    printf("\n");
}

/**
 * function to display the final path
 * @param s the city in the final path
 */
static void prFinalPath(void * s) {
    City* city = s;
}

/**
 * function to find the start and goal city from MAP file depends on user input
 * @param city the city to be checked
 */
static void findStartAndGoalCity (City * city) {
    if (strcasecmp(city->name, startName) == 0) {
        startCity = city;
    } else if (strcasecmp(city->name, goalName) == 0) {
        goalCity = city;
    }
}

/**
 * function to calculate g(n0) and h(n0)
 * @param s the city to be calculated g and h
 */
static void calculateGAndH(void * s) {
    City* currentCity = s;
    if (currentCity == startCity) {
        currentCity->distFromStart = 0;
        /* h = (ABS(x1-x2) + ABS(y1-y2))/4 */
        currentCity->distToGoal = (abs(currentCity->latitude - goalCity->latitude) + abs(currentCity->longitude - goalCity->longitude))/4;
    } else if (currentCity == goalCity) {
        /* g = plus infinite */
        currentCity->distFromStart = 10000;
        currentCity->distToGoal = 0;
    } else {
        currentCity->distFromStart = 10000;
        currentCity->distToGoal = (abs(currentCity->latitude - goalCity->latitude) + abs(currentCity->longitude - goalCity->longitude))/4;
    }
}

/**
 * function to check if input city name is correct
 * @param cityName the name of city to be checked
 * @return 1 if input name is correct
 * @return 0 otherwise
 */
static int checkCityName(char* cityName) {
    char temp[100];
    const char delimiter[] = "\t\t";
    char *token, *line;

    FILE* file = fopen(fileName, "r");
    if (!file) {
        perror("\nError opening file");
        exit(2);
    }

    /* read each line of the MAP file */
    while((line = fgets(temp, 100, file)) != NULL) {
        /* tokenize the line by divide them using delimiter */
        token = strtok(line, delimiter);
        while(token) {
            /* compare the token with city name, ignore the UPPERCASE and LOWERCASE */
            if (strcasecmp(token, cityName) == 0) {
                while(token) {
                    token = strtok(NULL, delimiter);
                }
                fclose(file);
                return 1;
            }
            token = strtok(NULL, delimiter);
        }
    }

    printf("\nThe city with name \"%s\" is incorrect. Enter correct city name(s)\n", cityName);
    fclose(file);
    return 0;
}

int main(int argc, char *argv[]) {
    FILE *file;
    /* check program input argument */
    switch(argc) {
        case 1:
            fileName = "FRANCE.MAP";
            char start[20], goal[20];
            printf("\nPlease enter start city: ");
            scanf("%[^\n]%*c", start);
            printf("\nPlease enter destination city: ");
            scanf("%[^\n]%*c", goal);
            startName = strdup(start);
            goalName = strdup(goal);
            break;
        case 2:
            printf("\nMissing destination city. Please enter the destination city.\n");
            exit(1);
        case 3:
            fileName = "FRANCE.MAP";
            startName = argv[1];
            goalName = argv[2];
            break;
        default:
            printf("\nInvalid number of arguments. Please try again.\n");
            exit(1);
    }

    if (!checkCityName(startName) || !checkCityName(goalName)) {
        exit(1);
    };

    file = fopen(fileName, "r");
    if (!file) {
        perror("\nError opening file");
        exit(2);
    }

    char name[50];
    int x, y;
    int res;
    City* city = NULL;
    Neighbor* neighbor = NULL;
    List* cityList = newList(compCityByName, prCity);
    List* openList = newList(compCityByF, prCity);
    List* closeList = newList(compCityByName, prCity);

    /* read MAP file */
    while ((res = fscanf(file, "%s%d%d", name, &x, &y))) {
        /* if line contains a city */
        if (res == 3) {
            if (city) {
                findStartAndGoalCity(city);
                addList(cityList, city);
            }
            city = newCity(name, x, y);
        } else if (res == 2) { /* if line contains a neighbor */
            neighbor = newNeighbor(name, x);
            if (neighbor) {
                insertNeighborToCity(city, neighbor->name, neighbor->distance);
            }
        } else if (res == EOF) { /* end of file */
            findStartAndGoalCity(city);
            addList(cityList, city);
            break;
        }
    }

    fclose(file);
    /* first calculate g and h of each city */
    forEach(cityList, calculateGAndH);
    /* result list of final path */
    List* finalPath = newList(0, prFinalPath);
    /* start A* algorithm */
    findShortestPath(cityList, openList, closeList, startCity, goalCity, finalPath);
    printPath(cityList,goalCity);
    /* deallocating used memory */
    delNeighbor(neighbor);
    delCity(city);
    delList(cityList);
    delList(openList);
    delList(closeList);
    delList(finalPath);

    return 0;
}
