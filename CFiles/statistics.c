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
#include "../HeaderFiles/statistics.h"

void displayPlayersTotal()
{
    printf("Total number of players: %d\n", players_count);
}

void displayAvgAge(Player **arr)
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to calculate average age!\n" RESET);
        return;
    }

    int totalAge = 0;
    for (int i = 0; i < players_count; i++)
    {
        totalAge += (*arr)[i].age;
    }
    double avgAge = (double)totalAge / players_count;
    printf("Average age of players: %.2f\n", avgAge);
}

void displayPlayersWithNGoals(Player **arr)
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to display!\n" RESET);
        return;
    }

    int n;
    
    do{
      inputNumber("Enter minimum number of goals: ", "%d", &n);
    }while(!validatePlayerGoals(n));

    int found = 0;
    printf("Players with at least %d goals:\n", n);
    for (int i = 0; i < players_count; i++)
    {
        if ((*arr)[i].goals >= n)
        {
            displayPlayer(&(*arr)[i], i + 1);
            found = 1;
        }
    }

    if (!found)
    {
        printf(ORANGE "No players found with at least %d goals.\n" RESET, n);
    }
}

void displayBestScorer(Player **arr)
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to display!\n" RESET);
        return;
    }

    int maxGoals = -1;
    for (int i = 0; i < players_count; i++)
    {
        if ((*arr)[i].goals > maxGoals)
        {
            maxGoals = (*arr)[i].goals;
        }
    }

    printf("Best scorer(s) with %d goals:\n", maxGoals);
    for (int i = 0; i < players_count; i++)
    {
        if ((*arr)[i].goals == maxGoals)
        {
            displayPlayer(&(*arr)[i], i + 1);
        }
    }
}

void displayMinMaxAge(Player **arr)
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to display!\n" RESET);
        return;
    }

    int minAge = (*arr)[0].age;
    int maxAge = (*arr)[0].age;
    int minIndex = 0, maxIndex = 0;

    for (int i = 1; i < players_count; i++)
    {
        if ((*arr)[i].age < minAge)
        {
            minAge = (*arr)[i].age;
            minIndex = i;
        }
        if ((*arr)[i].age > maxAge)
        {
            maxAge = (*arr)[i].age;
            maxIndex = i;
        }
    }

    printf("Youngest player age: %d\n", minAge);
    printf("Youngest player: ");
    displayPlayer(&(*arr)[minIndex], minIndex + 1);
    printf("Oldest player age: %d\n", maxAge);
    printf("Oldest player: ");
    displayPlayer(&(*arr)[maxIndex], maxIndex + 1);
}