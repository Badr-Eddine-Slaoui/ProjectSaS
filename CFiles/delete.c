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
#include "../HeaderFiles/delete.h"

void deletePlayer(Player **arr)
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to delete!\n" RESET);
        return;
    }

    long id;
    inputNumber("Enter player ID to delete: ", "%ld", &id);

    char confirmation;

    int found = 0;
    for (int i = 0; i < players_count; i++)
    {
        if ((*arr)[i].id == id)
        {
            do
            {
                printf(CYAN "Are you sure you want to delete this player? (y/n): " RESET);
                scanf(" %c", &confirmation);
                clear_buffer();

                if (confirmation != 'y' && confirmation != 'n')
                {
                    printf(YELLOW "Invalid input! Please enter 'y' or 'n'.\n" RESET);
                }
            } while (confirmation != 'y' && confirmation != 'n');

            if (confirmation == 'n')
            {
                printf(ORANGE "Deletion cancelled.\n" RESET);
                return;
            }
            
            int roleIndex = getRoleIndex((*arr)[i].role);
            countRoles[roleIndex]--;
    
            int statusIndex = getStatusIndex((*arr)[i].status);
            countStatus[statusIndex]--;
            
            for (int j = i; j < players_count - 1; j++)
            {
                (*arr)[j] = (*arr)[j + 1];
            }
            players_count--;
            *arr = realloc(*arr, players_count * sizeof(Player));
            found = 1;
            break;
        }
    }

    if (found)
    {
        saveToFile(*arr);
        printf(GREEN "Player deleted successfully!\n" RESET);
    }
    else
    {
        printf(ORANGE "Player not found!\n" RESET);
    }
}