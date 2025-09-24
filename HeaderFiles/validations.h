#ifndef VALIDATIONS_H
#define VALIDATIONS_H

void isValid(const char *prompt, char validList[][100], int listSize, char *var, size_t size);

bool validatePlayerFirstName(char *firstName);

bool validatePlayerLastName(char *lastName);

bool validateAge(int age);

bool validatePlayerNumber(Player **arr, int number);

bool validatePlayerGoals(int goals);

bool checkStartingPlayerRoleAvailability(Player **arr, char role[100]);

#endif