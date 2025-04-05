#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kota.h"

// Initialize cities array
void initializeCities(City cities[]) {
    for (int i = 0; i < MAX_CITIES; i++) {
        strcpy(cities[i].cityName, "");
        cities[i].personList = NULL;
    }
}

// Add a new city to the array
void addCity(City cities[], int* cityCount, const char* cityName) {
    if (*cityCount >= MAX_CITIES) {
        printf("Maximum number of cities reached!\n");
        return;
    }

    // Check if city already exists
    for (int i = 0; i < *cityCount; i++) {
        if (strcmp(cities[i].cityName, cityName) == 0) {
            printf("City already exists!\n");
            return;
        }
    }

    // Add new city
    strcpy(cities[*cityCount].cityName, cityName);
    cities[*cityCount].personList = NULL;
    (*cityCount)++;
    printf("City %s added successfully!\n", cityName);
}

// Add a person to a specific city's linked list
void addPersonToCity(City cities[], int cityIndex, const char* personName) {
    if (cityIndex < 0 || cityIndex >= MAX_CITIES || strlen(cities[cityIndex].cityName) == 0) {
        printf("Invalid city index!\n");
        return;
    }

    // Use insertFirst from linked.h
    insertFirst(&(cities[cityIndex].personList), personName);
    printf("Person %s added to %s\n", personName, cities[cityIndex].cityName);
}

// Display persons in a specific city
void displayCityPersons(City cities[], int cityIndex) {
    if (cityIndex < 0 || cityIndex >= MAX_CITIES || strlen(cities[cityIndex].cityName) == 0) {
        printf("Invalid city index!\n");
        return;
    }

    printf("Persons in %s:\n", cities[cityIndex].cityName);
    displayList(cities[cityIndex].personList);
}

// Display all cities
void displayAllCities(City cities[], int cityCount) {
    printf("Cities:\n");
    for (int i = 0; i < cityCount; i++) {
        printf("%d. %s\n", i+1, cities[i].cityName);
    }
}

// Delete a city and its persons
void deleteCityAndPersons(City cities[], int cityIndex, int* cityCount) {
    if (cityIndex < 0 || cityIndex >= *cityCount) {
        printf("Invalid city index!\n");
        return;
    }

    // Free all persons in the city using deleteAllNodes
    deleteAllNodes(&(cities[cityIndex].personList));

    // Shift remaining cities
    for (int i = cityIndex; i < *cityCount - 1; i++) {
        strcpy(cities[i].cityName, cities[i+1].cityName);
        cities[i].personList = cities[i+1].personList;
    }

    // Clear the last city
    strcpy(cities[*cityCount - 1].cityName, "");
    cities[*cityCount - 1].personList = NULL;
    (*cityCount)--;

    printf("City deleted successfully!\n");
}

// Free all resources
void freeAllResources(City cities[], int* cityCount) {
    for (int i = 0; i < *cityCount; i++) {
        // Use deleteAllNodes to free each city's person list
        deleteAllNodes(&(cities[i].personList));
    }
    *cityCount = 0;
}