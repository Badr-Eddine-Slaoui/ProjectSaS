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
#include "../HeaderFiles/statistics.h"
#include "../HeaderFiles/display.h"
#include "../HeaderFiles/add.h"
#include "../HeaderFiles/delete.h"
#include "../HeaderFiles/search.h"
#include "../HeaderFiles/formation.h"
#include "../HeaderFiles/fakeData.h"

int main()
{
    // saveFakeDataToFile();

    Player *Players = NULL;

    loadFromFile(&Players);
    
    loadFormation();

    while (1)
    {
        printf(RED "\n=== Player Management System ===\n" RESET);
        printf("Enter 1 to add a player\n");
        printf("Enter 2 to display players\n");
        printf("Enter 3 to update a player\n");
        printf("Enter 4 to delete a players\n");
        printf("Enter 5 to search for a player\n");
        printf("Enter 6 to display statistics\n");
        printf("Enter 7 to update formation\n");
        printf("Enter 8 to exit\n");

        int choice;
        inputNumber("Your choice: ", "%d", &choice);

        switch (choice)
        {
          case ADD:
          {
              printf(RED "\n=== Add Player Menu ===\n" RESET);
              printf("Enter 1 to add a player\n");
              printf("Enter 2 to add n players\n");
              printf("Enter 3 to return to main menu\n");
  
              int add_choice;
              inputNumber("Your choice: ", "%d", &add_choice);
  
              switch (add_choice)
              {
              case ADD_ONE:
                  addPlayers(&Players, 1);
                  break;
              case ADD_MULTIPLE:{
                  int n;
                  inputNumber("Enter number of players to add: ", "%d", &n);
  
                  addPlayers(&Players, n);
                  break;
              }
              case 3:
                  break;
              default:
                  printf(YELLOW "Invalid choice\n" RESET);
              }
              break;
          }
          case DISPLAY:
          {
              printf(RED "\n=== Display Player Menu ===\n" RESET);
              printf("Enter 1 to display all players\n");
              printf("Enter 2 to display players sorted alphabetically by last name\n");
              printf("Enter 3 to display players sorted by age\n");
              printf("Enter 4 to display players by post\n");
              printf("Enter 5 to return to main menu\n");
  
              int display_choice;
  
              inputNumber("Your choice: ", "%d", &display_choice);
  
              switch (display_choice)
              {
              case DISPLAY_ALL:
                  displayPlayers(&Players);
                  break;
              case ALPHABETIC_SORT:
                  sortPlayers(&Players, "alpha");
                  break;
              case AGE_SORT:
                  sortPlayers(&Players, "age");
                  break;
              case DISPLAY_BY_POST:
                  displayPlayersByPost(&Players);
                  break;
              case 5:
                  break;
              default:
                  printf(YELLOW "Invalid choice\n" RESET);
              }
              break;
          }
          case UPDATE:
          {
              printf(RED "\n=== Update Player Menu ===\n" RESET);
              printf("Enter 1 to update player's first name\n");
              printf("Enter 2 to update player's last name\n");
              printf("Enter 3 to update player's age\n");
              printf("Enter 4 to update player's number\n");
              printf("Enter 5 to update player's post\n");
              printf("Enter 6 to update player's status\n");
              printf("Enter 7 to update player's goals\n");
              printf("Enter 8 to return to main menu\n");
  
              int update_choice;
              inputNumber("Your choice: ", "%d", &update_choice);
  
              switch (update_choice)
              {
              case UPDATE_FIRST_NAME:
                  updatePlayerFirstName(&Players);
                  break;
              case UPDATE_LAST_NAME:
                  updatePlayerLastName(&Players);
                  break;
              case UPDATE_AGE:
                  updatePlayerAge(&Players);
                  break;
              case UPDATE_NUMBER:
                  updatePlayerNumber(&Players);
                  break;
              case UPDATE_POST:
                  updatePlayerPost(&Players);
                  break;
              case UPDATE_STATUS:
                  updatePlayerStatus(&Players);
                  break;
              case UPDATE_GOALS:
                  updatePlayerGoals(&Players);
                  break;
              case 8:
                  break;
              default:
                  printf(YELLOW "Invalid choice\n" RESET);
              }
              break;
          }
          case DELETE:{
              deletePlayer(&Players);
              break;
          }
          case SEARCH:
          {
              printf(RED "\n=== Search Player Menu ===\n" RESET);
              printf("Enter 1 to search by ID\n");
              printf("Enter 2 to search by first name\n");
              printf("Enter 3 to search by last name\n");
              printf("Enter 4 to search by age\n");
              printf("Enter 5 to search by number\n");
              printf("Enter 6 to search by role\n");
              printf("Enter 7 to search by goals\n");
              printf("Enter 8 to search by status\n");
              printf("Enter 9 to search by age range\n");
              printf("Enter 10 to return to main menu\n");
  
              int search_choice;
              inputNumber("Your choice: ", "%d", &search_choice);
  
              searchPlayerByAttr(&Players, search_choice);
              break;
          }
          case STATISTICS:
          {
              printf(RED "\n=== Statistics Menu ===\n" RESET);
              printf("Enter 1 to display total number of players\n");
              printf("Enter 2 to display average age of players\n");
              printf("Enter 3 to display players with at least n goals\n");
              printf("Enter 4 to display best scorer(s)\n");
              printf("Enter 5 to display youngest and oldest player ages\n");
              printf("Enter 6 to return to main menu\n");
  
              int stats_choice;
              inputNumber("Your choice: ", "%d", &stats_choice);
  
              switch (stats_choice)
              {
              case TOTAL:
                  displayPlayersTotal();
                  break;
              case AVG_AGE:
                  displayAvgAge(&Players);
                  break;
              case GOALS:
                  displayPlayersWithNGoals(&Players);
                  break;
              case BEST_SCOORER:
                  displayBestScorer(&Players);
                  break;
              case MIN_MAX_AGE:
                  displayMinMaxAge(&Players);
                  break;
              case 6:
                  break;
              default:
                  printf(YELLOW "Invalid choice\n" RESET);
              }
              break;
          }
          case UPDATE_FORMATION:{
            updateFormation(&Players);
            break;
          }
          case EXIT:{
              if (Players)
                  free(Players);
              printf(ORANGE "Goodbye!\n" RESET);
              exit(0);
          }
          default:{
              printf(YELLOW "Invalid choice\n" RESET);
          }
        }
    }
    return 0;
}