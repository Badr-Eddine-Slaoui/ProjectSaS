#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <regex.h>
#include "../HeaderFiles/structs.h"
#include "../HeaderFiles/enums.h"
#include "../HeaderFiles/helpers.h"
#include "../HeaderFiles/globalVar.h"
#include "../HeaderFiles/constants.h"
#include "../HeaderFiles/validations.h"
#include "../HeaderFiles/files.h"
#include "../HeaderFiles/search.h"

void searchPlayerByAttr(Player **arr, const int attr)
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to search!\n" RESET);
        return;
    }

    switch (attr)
    {
    case SEARCH_BY_ID:
    {
        long id;
        inputNumber("Enter player's ID: ", "%ld", &id);

        int found = 0;
        for (int i = 0; i < players_count; i++)
        {
            if ((*arr)[i].id == id)
            {
                displayPlayer(&(*arr)[i], i + 1);
                found = 1;
                break;
            }
        }
        if (!found)
        {
            printf(ORANGE "Player not found!\n" RESET);
        }
        break;
    }
    case SEARCH_BY_FIRST_NAME:
    {
        char firstName[100];
        
        do{
          handle_fgets_input("Enter player's first name: ", firstName, sizeof(firstName));
        }while(!validatePlayerFirstName(firstName));

        int found = 0;
        for (int i = 0; i < players_count; i++)
        {
            if (strcmp((*arr)[i].first_name, firstName) == 0)
            {
                displayPlayer(&(*arr)[i], i + 1);
                found = 1;
            }
        }
        if (!found)
        {
            printf(ORANGE "No players found with this first name!\n" RESET);
        }
        break;
    }
    case SEARCH_BY_LAST_NAME:
    {
        char lastName[100];
        
        do{
          handle_fgets_input("Enter player's last name: ", lastName, sizeof(lastName));
        }while(!validatePlayerLastName(lastName));

        int found = 0;
        for (int i = 0; i < players_count; i++)
        {
            if (strcmp((*arr)[i].last_name, lastName) == 0)
            {
                displayPlayer(&(*arr)[i], i + 1);
                found = 1;
            }
        }
        if (!found)
        {
            printf(ORANGE "No players found with this last name!\n" RESET);
        }
        break;
    }
    case SEARCH_BY_AGE:
    {
        int age;
        
        do{
          inputNumber("Enter player's age: ", "%d", &age);
        }while(!validateAge(age));

        int found = 0;
        for (int i = 0; i < players_count; i++)
        {
            if ((*arr)[i].age == age)
            {
                displayPlayer(&(*arr)[i], i + 1);
                found = 1;
            }
        }
        if (!found)
        {
            printf(ORANGE "No players found with this age!\n" RESET);
        }
        break;
    }
    case SEARCH_BY_NUMBER:
    {
        int number;
        do{
          inputNumber("Enter player's number: ", "%d", &number);
        }while(!validatePlayerNumber(arr, number));

        int found = 0;
        for (int i = 0; i < players_count; i++)
        {
            if ((*arr)[i].number == number)
            {
                displayPlayer(&(*arr)[i], i + 1);
                found = 1;
            }
        }
        if (!found)
        {
            printf(ORANGE "No players found with this number!\n" RESET);
        }
        break;
    }
    case SEARCH_BY_ROLE:
    {
        char role[100];
        isValid("Enter player's role (Goalkeeper, Right Back, Left Back, Center Back, Right Wing Back, Left Wing Back, Defensive Midfielder, Central Midfielder, Attacking Midfielder, Left Midfielder, Right Midfielder, Left Winger, Right Winger, Center Forward, Striker): ", validRoles, MAX_ROLES, role, sizeof(role));

        int found = 0;
        for (int i = 0; i < players_count; i++)
        {
            if (strcmp((*arr)[i].role, role) == 0)
            {
                displayPlayer(&(*arr)[i], i + 1);
                found = 1;
            }
        }
        if (!found)
        {
            printf(ORANGE "No players found with this role!\n" RESET);
        }
        break;
    }
    case SEARCH_BY_GOALS:
    {
        int goals;
        
        do{
          inputNumber("Enter player's goals: ", "%d", &goals);
        }while(!validatePlayerGoals(goals));

        int found = 0;
        for (int i = 0; i < players_count; i++)
        {
            if ((*arr)[i].goals == goals)
            {
                displayPlayer(&(*arr)[i], i + 1);
                found = 1;
            }
        }
        if (!found)
        {
            printf(ORANGE "No players found with this number of goals!\n" RESET);
        }
        break;
    }
    case SEARCH_BY_STATUS:
    {
        char status[100];
        isValid("Enter player's status (starting, bench, not summoned): ", validStatus, MAX_STATUS, status, sizeof(status));

        int found = 0;
        for (int i = 0; i < players_count; i++)
        {
            if (strcmp((*arr)[i].status, status) == 0)
            {
                displayPlayer(&(*arr)[i], i + 1);
                found = 1;
            }
        }
        if (!found)
        {
            printf(ORANGE "No players found with this status!\n" RESET);
        }
        break;
    }
    case SEARCH_BY_AGE_RANGE:
    {
        int minAge, maxAge;
        
        do{
          inputNumber("Enter minimum age: ", "%d", &minAge);
        }while(!validateAge(minAge));
        
        do{
          inputNumber("Enter maximum age: ", "%d", &maxAge);
        }while(!validateAge(maxAge));

        if (minAge > maxAge)
        {
            printf(YELLOW "Invalid range! Minimum age cannot be greater than maximum age.\n" RESET);
            return;
        }

        int found = 0;
        for (int i = 0; i < players_count; i++)
        {
            if ((*arr)[i].age >= minAge && (*arr)[i].age <= maxAge)
            {
                displayPlayer(&(*arr)[i], i + 1);
                found = 1;
            }
        }
        if (!found)
        {
            printf(ORANGE "No players found in this age range!\n" RESET);
        }
        break;
    }
    case 10:
        break;
    default:
        printf(YELLOW "Search by this attribute is not implemented yet.\n" RESET);
    }
}