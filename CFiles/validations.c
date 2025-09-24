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

void isValid(const char *prompt, char validList[][100], int listSize, char *var, size_t size)
{
    int isValidInput = 0;
    do
    {
        handle_fgets_input(prompt, var, size);

        for (int i = 0; i < listSize; i++)
        {
            if (strcmp(var, validList[i]) == 0)
            {
                isValidInput = 1;
                break;
            }
        }
        if (!isValidInput)
        {
            printf(YELLOW "Invalid input! Please enter a valid option.\n" RESET);
        }
    } while (!isValidInput);
}

bool validatePlayerFirstName(char *firstName){
  char *pattern = "^[A-Za-z]{3,15}( [A-Za-z]{3,15}){0,1}$";
  
  if(!checkRegex(pattern, firstName)){
    printf(YELLOW "The first name must contain only letters and be 3–30 characters long.\n" RESET);
    return false;
  }
  
  return true;
}

bool validatePlayerLastName(char *lastName){
  char *pattern = "^[A-Za-z]{3,15}( [A-Za-z]{3,15}){0,1}$";
  
  if(!checkRegex(pattern, lastName)){
    printf(YELLOW "The last name must contain only letters and be 3–30 characters long.\n" RESET);
    return false;
  }
  
  return true;
}

bool validateAge(int age){
  if(age < 14 || age > 41){
    printf(YELLOW "The age must be between 14 and 41.\n" RESET);
    return false;
  }
  
  return true;
}

bool validatePlayerNumber(Player **arr, int number){
  if(number < 1 || number > 99){
    printf(YELLOW "The number must be between 1 and 99.\n" RESET);
    return false;
  }
  
  for(int i = 0; i < players_count; i++){
    if((*arr)[i].number == number){
      printf(YELLOW "This number is already taken.\n" RESET);
      return false;
    }
  }
  
  return true;
}

bool validatePlayerGoals(int goals){
  if(goals < 0){
    printf(YELLOW "Goals must be positive.\n" RESET);
    return false;
  }
  
  return true;
}

bool checkStartingPlayerRoleAvailability(Player **arr, char role[100]){
  int formationIndex = getFormationIndex(formation);
  int found = 0;
  int roleCount = 0;
  
  for(int i = 0; i < 11; i++){
    if(strcmp(formationRoles[formationIndex][i], role) == 0){
      found = 1;
      roleCount++;
    }
  }
  
  if(!found){
    printf(YELLOW "The role '%s' is not available in your current formation (%s)" RESET, role, formation);
    return false;
  }
  
  int startingPlayerRoleCount = 0;
  
  for(int i = 0; i < players_count; i++){
    if(strcmp((*arr)[i].status, "starting") == 0){
      if(strcmp((*arr)[i].role, role) == 0){
        startingPlayerRoleCount++;
      }
    }
  }
  
  if(startingPlayerRoleCount >= roleCount){
    printf(YELLOW "The role '%s' is already taken in your current formation (%s)" RESET, role, formation);
    return false;
  }
  
  return true;
}