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
#include "../HeaderFiles/formation.h"

void updateFormation(Player **arr){
  char new_formation[20];
  
  isValid("Enter new formation (4-3-3, 4-4-2, 4-2-3-1, 4-5-1, 3-5-2, 3-4-3, 5-3-2, 5-4-1): ", formations, MAX_FORMATIONS, new_formation, sizeof(new_formation));
  
  strcpy(formation, new_formation);
  saveFormation();
  
  for(int i = 0; i < players_count; i++){
    if(strcmp((*arr)[i].status, "not summoned") != 0){
      strcpy((*arr)[i].status, "not summoned");
    }
  }
  
  saveToFile(*arr);
  printf(GREEN "Formation updated successfully!\n" RESET);
}