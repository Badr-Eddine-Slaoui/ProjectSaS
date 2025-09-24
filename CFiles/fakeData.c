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
#include "../HeaderFiles/fakeData.h"

void saveFakeDataToFile()
{
    Player fakeData[22] = {
        // ---- Starting XI (4-3-3) ----
        { 1694770000, "Marc-Andre", "ter Stegen", 32,  1, "goalkeeper",            0, {15,9,2025}, "starting" },
        { 1694770001, "Joao", "Cancelo",         30,  2, "right back",            0, {15,9,2025}, "starting" },
        { 1694770002, "Alejandro", "Balde",      21,  3, "left back",             0, {15,9,2025}, "starting" },
        { 1694770003, "Ronald", "Araujo",        25,  4, "center back",           0, {15,9,2025}, "starting" },
        { 1694770004, "Jules", "Kounde",         26, 23, "center back",           0, {15,9,2025}, "starting" },
        { 1694770005, "Oriol", "Romeu",          32, 18, "defensive midfielder",  0, {15,9,2025}, "starting" },
        { 1694770006, "Pedri", "Gonzalez",       22,  8, "central midfielder",    0, {15,9,2025}, "starting" },
        { 1694770007, "Frenkie", "de Jong",      28, 21, "central midfielder",    0, {15,9,2025}, "starting" },
        { 1694770008, "Ferran", "Torres",        25,  7, "left winger",           0, {15,9,2025}, "starting" },
        { 1694770009, "Raphinha", "Belloli",     28, 11, "right winger",          0, {15,9,2025}, "starting" },
        { 1694770010, "Robert", "Lewandowski",   37,  9, "striker",               0, {15,9,2025}, "starting" },
    
        // ---- Bench (7 players) ----
        { 1694770011, "Inaki", "Pena",           25, 13, "goalkeeper",            0, {15,9,2025}, "bench" },
        { 1694770012, "Pau", "Cubarsi",          18,  4, "center back",           0, {15,9,2025}, "bench" },
        { 1694770013, "Marcos", "Alonso",        34, 17, "left back",             0, {15,9,2025}, "bench" },
        { 1694770014, "Gavi", "Paez",            21,  6, "central midfielder",    0, {15,9,2025}, "bench" },
        { 1694770015, "Ilkay", "Gundogan",       34, 22, "attacking midfielder",  0, {15,9,2025}, "bench" },
        { 1694770016, "Anssumane", "Fati",       22, 10, "left winger",           0, {15,9,2025}, "bench" },
        { 1694770017, "Vitor", "Roque",          20, 19, "striker",               0, {15,9,2025}, "bench" },
    
        // ---- Not Summoned (4 players) ----
        { 1694770018, "Sergi", "Roberto",        33, 20, "right wing back",       0, {15,9,2025}, "not summoned" },
        { 1694770019, "Hector", "Fort",          19, 29, "left wing back",        0, {15,9,2025}, "not summoned" },
        { 1694770020, "Marc", "Casado",          21, 30, "defensive midfielder",  0, {15,9,2025}, "not summoned" },
        { 1694770021, "Lamine", "Yamal",         18, 27, "right midfielder",      0, {15,9,2025}, "not summoned" }
    };
    
    FILE *fp = fopen("./players.dat", "wb");
    if (fp == NULL)
    {
        printf("Error: Unable to save fake data to file!\n");
        return;
    }
    fwrite(fakeData, sizeof(Player), 22, fp);
    fclose(fp);
    printf("Fake data saved to file successfully!\n");
}