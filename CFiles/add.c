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
#include "../HeaderFiles/add.h"

void addPlayers(Player **arr, int n)
{
  if(players_count == MAX_PLAYERS){
    printf(YELLOW "You can't add more than 23 players in your team!\n" RESET);
    return;
  }
    for (int i = 0; i < n; i++)
    {
        Player newPlayer;
        newPlayer.id = (long)time(NULL);

        setCurrentDate(&newPlayer.registration_date);
        do{
          handle_fgets_input("Enter player's first name: ", newPlayer.first_name, sizeof(newPlayer.first_name));
        }while(!validatePlayerFirstName(newPlayer.first_name));
        
        do{
          handle_fgets_input("Enter player's last name: ", newPlayer.last_name, sizeof(newPlayer.last_name));
        }while(!validatePlayerLastName(newPlayer.last_name));

        do{
          inputNumber("Enter player's age: ", "%d", &newPlayer.age);
        }while(!validateAge(newPlayer.age));

        do{
          inputNumber("Enter player's number: ", "%d", &newPlayer.number);
        }while(!validatePlayerNumber(arr, newPlayer.number));
        
        isValid("Enter player's role (Goalkeeper, Right Back, Left Back, Center Back, Right Wing Back, Left Wing Back, Defensive Midfielder, Central Midfielder, Attacking Midfielder, Left Midfielder, Right Midfielder, Left Winger, Right Winger, Center Forward, Striker): ", validRoles, MAX_ROLES, newPlayer.role, sizeof(newPlayer.role));
        
        int roleIndex = getRoleIndex(newPlayer.role);
        if(countRoles[roleIndex] == maxPlayersPerRole[roleIndex]){
          printf(YELLOW "This role is not available please add a player with diffrent role!" RESET);
          return;
        }else{
          countRoles[roleIndex]++;
        }

        do{
          inputNumber("Enter player's goals: ", "%d", &newPlayer.goals);
        }while(!validatePlayerGoals(newPlayer.goals));

        isValid("Enter player's status (starting, bench, not summoned): ", validStatus, MAX_STATUS, newPlayer.status, sizeof(newPlayer.status));
        
        int statusIndex = getStatusIndex(newPlayer.status);
        if(countStatus[statusIndex] == maxPlayersPerStatus[statusIndex]){
          printf(YELLOW "This status is not available please add a player with diffrent status!" RESET);
          return;
        }else{
          countStatus[statusIndex]++;
        }
        
        if(strcmp(newPlayer.status, "starting") == 0){
          if(!checkStartingPlayerRoleAvailability(arr, newPlayer.role)){
            countRoles[roleIndex]--;
            countStatus[statusIndex]--;
            return;
          }
        }

        *arr = realloc(*arr, (players_count + 1) * sizeof(Player));
        if (*arr == NULL)
        {
            printf(RED "Error: Memory allocation failed!\n" RESET);
            return;
        }

        (*arr)[players_count] = newPlayer;
        players_count++;

        if (newPlayer.goals >= 10)
        {
            printf(ORANGE "This player is a high scorer!\n" RESET);
        }

        printf(GREEN "Player added successfully!\n" RESET);
    }
    saveToFile(*arr);
}