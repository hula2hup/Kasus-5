#ifndef KOTA_H
#define KOTA_H

#include "linked.h"

#define MAX_CITIES 20
#define MAX_NAME_LENGTH 50

// City structure with a pointer to linked list of persons
typedef struct {
    char cityName[MAX_NAME_LENGTH];
    Node* personList;  // Changed from Person* to Node*
} City;

// Function prototypes for city and person management
void initializeCities(City cities[]);
void addCity(City cities[], int* cityCount, const char* cityName);
void addPersonToCity(City cities[], int cityIndex, const char* personName);
void displayCityPersons(City cities[], int cityIndex);
void displayAllCities(City cities[], int cityCount);
void deleteCityAndPersons(City cities[], int cityIndex, int* cityCount);
void freeAllResources(City cities[], int* cityCount);

#endif // KOTA_H