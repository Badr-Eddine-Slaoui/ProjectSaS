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

int getRoleIndex(const char *roleName) {
    for (int i = 0; i < MAX_ROLES; i++) {
        if (strcmp(validRoles[i], roleName) == 0) return i;
    }
    return -1;
}

int getStatusIndex(const char *status) {
    for (int i = 0; i < MAX_STATUS; i++) {
        if (strcmp(validStatus[i], status) == 0) return i;
    }
    return -1;
}

int getFormationIndex(const char *formation) {
    for (int i = 0; i < MAX_FORMATIONS; i++) {
        if (strcmp(formations[i], formation) == 0) return i;
    }
    return -1;
}

void clear_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void str_to_lower(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower(str[i]);
    }
}

void handle_fgets_input(const char *prompt, char *var, size_t size)
{
    printf(CYAN "%s" RESET, prompt);
    fgets(var, size, stdin);
    str_to_lower(var);
    int len = strlen(var);
    if (len > 0 && var[len - 1] == '\n')
    {
        var[len - 1] = '\0';
    }
    else
    {
        clear_buffer();
    }
}

void inputNumber(const char *prompt, const char *format, void *var)
{
    printf(CYAN "%s" RESET, prompt);
    while (scanf(format, var) != 1)
    {
        printf(YELLOW "Invalid input. Try again: " RESET);
        clear_buffer();
    }
    clear_buffer();
}

void setCurrentDate(Date *date)
{
    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    date->day = local->tm_mday;
    date->month = local->tm_mon + 1;
    date->year = local->tm_year + 1900;
}

void displayPlayer(const Player *player, const int i)
{
    printf(YELLOW "\nPlayer %d:\n" RESET, i);
    printf("  " GREEN "ID" RESET "                : %ld\n", (*player).id);
    printf("  " GREEN "First Name" RESET "        : %s\n", (*player).first_name);
    printf("  " GREEN "Last Name" RESET "         : %s\n", (*player).last_name);
    printf("  " GREEN "Age" RESET "               : %d\n", (*player).age);
    printf("  " GREEN "Number" RESET "            : %d\n", (*player).number);
    printf("  " GREEN "Role" RESET "              : %s\n", (*player).role);
    printf("  " GREEN "Goals" RESET "             : %d\n", (*player).goals);
    printf("  " GREEN "Status" RESET "            : %s\n", (*player).status);
    printf("  " GREEN "Registration Date" RESET " : %02d/%02d/%04d\n", (*player).registration_date.day, (*player).registration_date.month, (*player).registration_date.year);
}

void displayPlayers(Player **arr)
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to display!\n" RESET);
        return;
    }

    for (int i = 0; i < players_count; i++)
    {
        displayPlayer(&(*arr)[i], i + 1);
    }
}

bool checkRegex(char *pattern, char *str){
  regex_t regex;
  int reti;
  
  regcomp(&regex, pattern, REG_EXTENDED);
  reti = regexec(&regex, str, 0, NULL, 0);
  if(reti){
    return false;
  }
  return true;
}