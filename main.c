#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kota.h"

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void printMenu() {
    printf("\n--- City-Person Management System ---\n");
    printf("1.  Add City\n");
    printf("2.  Add Person to City\n");
    printf("3.  Display Persons in a City\n");
    printf("4.  Display All Cities\n");
    printf("5.  Delete City and its Persons\n");
    printf("6.  Total Number of Cities\n");
    printf("7.  Total Number of Persons in a City\n");
    printf("8.  Search Person in a City\n");
    printf("9.  Exit Program\n");
    printf("Enter your choice: ");
}

int main() {
    City cities[MAX_CITIES];
    int cityCount = 0;
    int choice, cityIndex;
    char cityName[MAX_NAME_LENGTH];
    char personName[MAX_NAME_LENGTH];

    // Initialize cities
    initializeCities(cities);

    while (1) {
        printMenu();
        
        // Input validation
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: // Add City
                printf("Enter city name: ");
                if (fgets(cityName, sizeof(cityName), stdin) != NULL) {
                    cityName[strcspn(cityName, "\n")] = 0; // Remove newline
                    if (strlen(cityName) > 0) {
                        addCity(cities, &cityCount, cityName);
                    } else {
                        printf("City name cannot be empty!\n");
                    }
                }
                break;

            case 2: // Add Person to City
                if (cityCount == 0) {
                    printf("No cities exist. Please add a city first.\n");
                    break;
                }
                
                displayAllCities(cities, cityCount);
                printf("Enter city index: ");
                if (scanf("%d", &cityIndex) != 1) {
                    printf("Invalid input!\n");
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer();
                
                cityIndex--; // Convert to 0-based index
                if (cityIndex < 0 || cityIndex >= cityCount) {
                    printf("Invalid city index!\n");
                    break;
                }

                printf("Enter person name: ");
                if (fgets(personName, sizeof(personName), stdin) != NULL) {
                    personName[strcspn(personName, "\n")] = 0; // Remove newline
                    if (strlen(personName) > 0) {
                        addPersonToCity(cities, cityIndex, personName);
                    } else {
                        printf("Person name cannot be empty!\n");
                    }
                }
                break;

            case 3: // Display Persons in a City
                if (cityCount == 0) {
                    printf("No cities exist.\n");
                    break;
                }
                
                displayAllCities(cities, cityCount);
                printf("Enter city index: ");
                if (scanf("%d", &cityIndex) != 1) {
                    printf("Invalid input!\n");
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer();
                
                cityIndex--; // Convert to 0-based index
                displayCityPersons(cities, cityIndex);
                break;

            case 4: // Display All Cities
                if (cityCount == 0) {
                    printf("No cities exist.\n");
                } else {
                    displayAllCities(cities, cityCount);
                }
                break;

            case 5: // Delete City and its Persons
                if (cityCount == 0) {
                    printf("No cities exist.\n");
                    break;
                }
                
                displayAllCities(cities, cityCount);
                printf("Enter city index to delete: ");
                if (scanf("%d", &cityIndex) != 1) {
                    printf("Invalid input!\n");
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer();
                
                cityIndex--; // Convert to 0-based index
                deleteCityAndPersons(cities, cityIndex, &cityCount);
                break;

            case 6: // Total Number of Cities
                printf("Total number of cities: %d\n", cityCount);
                break;

            case 7: // Total Number of Persons in a City
                if (cityCount == 0) {
                    printf("No cities exist.\n");
                    break;
                }
                
                displayAllCities(cities, cityCount);
                printf("Enter city index: ");
                if (scanf("%d", &cityIndex) != 1) {
                    printf("Invalid input!\n");
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer();
                
                cityIndex--; // Convert to 0-based index
                if (cityIndex < 0 || cityIndex >= cityCount) {
                    printf("Invalid city index!\n");
                    break;
                }
                
                printf("Total persons in %s: %d\n", 
                       cities[cityIndex].cityName, 
                       getListLength(cities[cityIndex].personList));
                break;

            case 8: // Search Person in a City
                if (cityCount == 0) {
                    printf("No cities exist.\n");
                    break;
                }
                
                displayAllCities(cities, cityCount);
                printf("Enter city index: ");
                if (scanf("%d", &cityIndex) != 1) {
                    printf("Invalid input!\n");
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer();
                
                cityIndex--; // Convert to 0-based index
                if (cityIndex < 0 || cityIndex >= cityCount) {
                    printf("Invalid city index!\n");
                    break;
                }

                printf("Enter person name to search: ");
                if (fgets(personName, sizeof(personName), stdin) != NULL) {
                    personName[strcspn(personName, "\n")] = 0; // Remove newline
                    
                    if (searchNode(cities[cityIndex].personList, personName)) {
                        printf("%s found in %s!\n", personName, cities[cityIndex].cityName);
                    } else {
                        printf("%s not found in %s.\n", personName, cities[cityIndex].cityName);
                    }
                }
                break;

            case 9: // Exit Program
                freeAllResources(cities, &cityCount);
                printf("Exiting program. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}