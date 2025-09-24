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
#include "../HeaderFiles/files.h"

void saveToFile(const Player *arr)
{
    FILE *fp = fopen("../Data/players.dat", "wb");
    if (fp == NULL)
    {
        printf(RED "Error: Unable to save to file!\n" RESET);
        return;
    }
    if (players_count > 0)
    {
        fwrite(arr, sizeof(Player), players_count, fp);
    }
    fclose(fp);
}

void loadFromFile(Player **arr)
{
    FILE *fp = fopen("../Data/players.dat", "rb");
    if (fp == NULL)
    {
        printf(YELLOW "No existing data file found. Starting fresh.\n" RESET);
        players_count = 0;
        *arr = NULL;
        return;
    }

    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);

    if (fileSize == 0)
    {
        printf(ORANGE "Data file is empty. Starting fresh.\n" RESET);
        players_count = 0;
        *arr = NULL;
        fclose(fp);
        return;
    }

    players_count = fileSize / sizeof(Player);
    *arr = malloc(players_count * sizeof(Player));

    if (*arr == NULL)
    {
        printf(RED "Error: Memory allocation failed!\n" RESET);
        players_count = 0;
        fclose(fp);
        return;
    }

    int items_read = fread(*arr, sizeof(Player), players_count, fp);
    if (items_read != players_count)
    {
        printf(YELLOW "Warning: Could not read all players from file!\n" YELLOW);
        players_count = items_read;
    }

    fclose(fp);
    
    for(int i = 0; i < MAX_ROLES; i++){
      for(int j = 0; j < players_count; j++){
        if(strcmp(validRoles[i],(*arr)[j].role) == 0){
         countRoles[i]++;
        }
      }
    }
    
    for(int i = 0; i < MAX_STATUS; i++){
      for(int j = 0; j < players_count; j++){
        if(strcmp(validStatus[i],(*arr)[j].status) == 0){
         countStatus[i]++;
        }
      }
    }
    
    printf(ORANGE "Loaded %d players from file.\n" RESET, players_count);
}

void saveFormation(){
    FILE *fp = fopen("../Data/formation.dat", "wb");
    if (fp == NULL)
    {
        printf(RED "Error: Unable to save to file!\n" RESET);
        return;
    }
    
    if (strlen(formation) > 0)
    {
        fwrite(formation, sizeof(char), strlen(formation), fp);
    }
    
    fclose(fp);
}

void loadFormation()
{
    FILE *fp = fopen("../Data/formation.dat", "rb");
    if (fp == NULL)
    {
        printf(YELLOW "No existing data file found. Starting fresh.\n" RESET);
        strcpy(formation,"4-3-3");
        saveFormation();
        return;
    }

    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);

    if (fileSize == 0)
    {
        printf(ORANGE "Data file is empty. Starting fresh.\n" RESET);
        strcpy(formation,"4-3-3");
        saveFormation();
        return;
    }
    
    int str_len = fileSize / sizeof(char);

    fread(formation, sizeof(char), str_len, fp);

    fclose(fp);
    
    printf(ORANGE "Formation loaded, cutrent formation: %s\n" RESET, formation);
}