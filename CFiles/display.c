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
#include "../HeaderFiles/display.h"

void sortPlayers(Player **arr, const char attr[])
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to display!\n" RESET);
        return;
    }

    printf(ORANGE "Sorting players by %s...\n" RESET, attr);
    char direction[5];
    do
    {
        handle_fgets_input("Enter sorting direction (asc/desc): ", direction, sizeof(direction));

        if (strcmp(direction, "asc") != 0 && strcmp(direction, "desc") != 0)
        {
            printf(YELLOW "Invalid direction! Please enter 'asc' or 'desc'.\n" RESET);
        }
    } while (strcmp(direction, "asc") != 0 && strcmp(direction, "desc") != 0);

    Player temp;
    for (int i = 0; i < players_count - 1; i++)
    {
        for (int j = 0; j < players_count - i - 1; j++)
        {
            if (strcmp(direction, "asc") == 0)
            {
                if (strcmp(attr, "alpha") == 0)
                {
                    if (strcmp((*arr)[j].last_name, (*arr)[j + 1].last_name) > 0)
                    {
                        temp = (*arr)[j];
                        (*arr)[j] = (*arr)[j + 1];
                        (*arr)[j + 1] = temp;
                    }
                }
                else if (strcmp(attr, "age") == 0)
                {
                    if ((*arr)[j].age > (*arr)[j + 1].age)
                    {
                        temp = (*arr)[j];
                        (*arr)[j] = (*arr)[j + 1];
                        (*arr)[j + 1] = temp;
                    }
                }
            }
            else if (strcmp(direction, "desc") == 0)
            {
                if (strcmp(attr, "alpha") == 0)
                {
                    if (strcmp((*arr)[j].last_name, (*arr)[j + 1].last_name) < 0)
                    {
                        temp = (*arr)[j];
                        (*arr)[j] = (*arr)[j + 1];
                        (*arr)[j + 1] = temp;
                    }
                }
                else if (strcmp(attr, "age") == 0)
                {
                    if ((*arr)[j].age < (*arr)[j + 1].age)
                    {
                        temp = (*arr)[j];
                        (*arr)[j] = (*arr)[j + 1];
                        (*arr)[j + 1] = temp;
                    }
                }
            }
        }
    }

    saveToFile(*arr);
    printf(GREEN "Players sorted successfully!\n" RESET);
    displayPlayers(arr);
}

void displayPlayersByPost(Player **arr)
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to display!\n" RESET);
        return;
    }

    int found = 0;
    for (int i = 0; i < MAX_ROLES; i++)
    {
        printf(ORANGE "\n--- Players in role: %s ---\n" RESET, validRoles[i]);
        found = 0;
        for (int j = 0; j < players_count; j++)
        {
            if (strcmp((*arr)[j].role, validRoles[i]) == 0)
            {
                displayPlayer(&(*arr)[j], j + 1);
                found = 1;
            }
        }
        if (!found)
        {
            printf(YELLOW "No players found in this role.\n" RESET);
        }
    }
}