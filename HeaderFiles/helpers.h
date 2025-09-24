#ifndef HELPERS_H
#define HELPERS_H

int getRoleIndex(const char *roleName);

int getStatusIndex(const char *status);

int getFormationIndex(const char *formation);

void clear_buffer();

void str_to_lower(char *str);

void handle_fgets_input(const char *prompt, char *var, size_t size);

void inputNumber(const char *prompt, const char *format, void *var);

void setCurrentDate(Date *date);

void displayPlayer(const Player *player, const int i);

void displayPlayers(Player **arr);

bool checkRegex(char *pattern, char *str);

#endif