#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Date
{
    int day;
    int month;
    int year;
} Date;

typedef struct Player
{
    long id;
    char first_name[100];
    char last_name[100];
    int age;
    int number;
    char role[100];
    int goals;
    Date registration_date;
    char status[100];
} Player;

#endif