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
#include "../HeaderFiles/update.h"

void updatePlayerFirstName(Player **arr)
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to update!\n" RESET);
        return;
    }

    long id;
    char firstName[100];
    
    inputNumber("Enter player ID: ", "%ld", &id);

    int found = 0;
    for (int i = 0; i < players_count; i++)
    {
        if ((*arr)[i].id == id)
        {
            do{
              handle_fgets_input("Enter player's new first name: ", firstName, sizeof(firstName));
            }while(!validatePlayerFirstName(firstName));
            
            strcpy((*arr)[i].first_name, firstName);
            found = 1;
            break;
        }
    }

    if (found)
    {
        saveToFile(*arr);
        printf(GREEN "Player first name updated successfully!\n" RESET);
    }
    else
    {
        printf(ORANGE "Player not found!\n" RESET);
    }
}

void updatePlayerLastName(Player **arr)
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to update!\n" RESET);
        return;
    }

    long id;
    char lastName[100];
    
    inputNumber("Enter player ID: ", "%ld", &id);

    int found = 0;
    for (int i = 0; i < players_count; i++)
    {
        if ((*arr)[i].id == id)
        {
            do{
              handle_fgets_input("Enter player's new last name: ", lastName, sizeof(lastName));
            }while(!validatePlayerLastName(lastName));
            
            strcpy((*arr)[i].last_name, lastName);
            found = 1;
            break;
        }
    }

    if (found)
    {
        saveToFile(*arr);
        printf(GREEN "Player last name updated successfully!\n" RESET);
    }
    else
    {
        printf(ORANGE "Player not found!\n" RESET);
    }
}

void updatePlayerPost(Player **arr)
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to update!\n" RESET);
        return;
    }

    long id;
    char newRole[100];
    inputNumber("Enter player ID: ", "%ld", &id);

    int found = 0;
    for (int i = 0; i < players_count; i++)
    {
        if ((*arr)[i].id == id)
        {
            isValid("Enter new role (Goalkeeper, Right Back, Left Back, Center Back, Right Wing Back, Left Wing Back, Defensive Midfielder, Central Midfielder, Attacking Midfielder, Left Midfielder, Right Midfielder, Left Winger, Right Winger, Center Forward, Striker): ", validRoles, MAX_ROLES, newRole, sizeof(newRole));
            
            int newRoleIndex = getRoleIndex(newRole);
            if(countRoles[newRoleIndex] == maxPlayersPerRole[newRoleIndex]){
              printf(YELLOW "This role is not available please choose a diffrent one!" RESET);
              return;
            }else{
              if(strcmp((*arr)[i].status, "starting") == 0){
                if(!checkStartingPlayerRoleAvailability(arr, newRole)){
                  return;
                }
              }
              countRoles[newRoleIndex]++;
              int oldRoleIndex = getRoleIndex((*arr)[i].role);
              countRoles[oldRoleIndex]--;
            }
            strcpy((*arr)[i].role, newRole);
            found = 1;
            break;
        }
    }

    if (found)
    {
        saveToFile(*arr);
        printf(GREEN "Player role updated successfully!\n" RESET);
    }
    else
    {
        printf(ORANGE "Player not found!\n" RESET);
    }
}

void updatePlayerStatus(Player **arr)
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to update!\n" RESET);
        return;
    }

    long id;
    char newStatus[100];
    inputNumber("Enter player ID: ", "%ld", &id);

    int found = 0;
    for (int i = 0; i < players_count; i++)
    {
        if ((*arr)[i].id == id)
        {
            isValid("Enter player's status (starting, bench, not summoned): ", validStatus, MAX_STATUS, newStatus, sizeof(newStatus));
            
            int newStatusIndex = getStatusIndex(newStatus);
            if(countStatus[newStatusIndex] == maxPlayersPerStatus[newStatusIndex]){
              printf(YELLOW "This status is not available please choose a diffrent one!" RESET);
              return;
            }else{
              if(strcmp(newStatus, "starting") == 0){
                if(!checkStartingPlayerRoleAvailability(arr, (*arr)[i].role)){
                  return;
                }
              }
              countStatus[newStatusIndex]++;
              int oldStatusIndex = getStatusIndex((*arr)[i].status);
              countStatus[oldStatusIndex]--;
            }
            strcpy((*arr)[i].status, newStatus);
            found = 1;
            break;
        }
    }

    if (found)
    {
        saveToFile(*arr);
        printf(GREEN "Player status updated successfully!\n" RESET);
    }
    else
    {
        printf(ORANGE "Player not found!\n" RESET);
    }
}

void updatePlayerAge(Player **arr)
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to update!\n" RESET);
        return;
    }

    int newAge;
    long id;
    inputNumber("Enter player ID: ", "%ld", &id);

    int found = 0;
    for (int i = 0; i < players_count; i++)
    {
        if ((*arr)[i].id == id)
        {
            do{
              inputNumber("Enter new age: ", "%d", &newAge);
            }while(!validateAge(newAge));
            
            (*arr)[i].age = newAge;
            found = 1;
            break;
        }
    }

    if (found)
    {
        saveToFile(*arr);
        printf(GREEN "Player age updated successfully!\n" RESET);
    }
    else
    {
        printf(ORANGE "Player not found!\n" RESET);
    }
}

void updatePlayerGoals(Player **arr)
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to update!\n" RESET);
        return;
    }

    int newGoals;
    long id;
    inputNumber("Enter player ID: ", "%ld", &id);

    int found = 0;
    for (int i = 0; i < players_count; i++)
    {
        if ((*arr)[i].id == id)
        {
            inputNumber("Enter new goals: ", "%d", &newGoals);
            (*arr)[i].goals = newGoals;
            found = 1;
            break;
        }
    }

    if (found)
    {
        saveToFile(*arr);
        if (newGoals >= 10)
        {
            printf(ORANGE "This player is a high scorer!\n" RESET);
        }

        printf(GREEN "Player goals updated successfully!\n" RESET);
    }
    else
    {
        printf(ORANGE "Player not found!\n" RESET);
    }
}

void updatePlayerNumber(Player **arr)
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to update!\n" RESET);
        return;
    }

    int newNumber;
    long id;
    inputNumber("Enter player ID: ", "%ld", &id);

    int found = 0;
    for (int i = 0; i < players_count; i++)
    {
        if ((*arr)[i].id == id)
        {
            do{
              inputNumber("Enter new number: ", "%d", &newNumber);
            }while(!validatePlayerNumber(arr, newNumber));
            
            (*arr)[i].number = newNumber;
            found = 1;
            break;
        }
    }

    if (found)
    {
        saveToFile(*arr);

        printf(GREEN "Player number updated successfully!\n" RESET);
    }
    else
    {
        printf(ORANGE "Player not found!\n" RESET);
    }
}