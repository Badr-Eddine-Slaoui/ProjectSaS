#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "../HeaderFiles/structs.h"
#include "../HeaderFiles/enums.h"

char validRoles[][100] = {
    "goalkeeper", "right back", "left back", "center back",
    "right wing back", "left wing back", "defensive midfielder",
    "central midfielder", "attacking midfielder",
    "left midfielder", "right midfielder",
    "left winger", "right winger",
    "center forward", "striker"
};

int maxPlayersPerRole[MAX_ROLES] = {
    3,2,2,5,1,1,3,4,2,2,2,2,2,2,3
};

int countRoles[MAX_ROLES] = {0};

char validStatus[][100] = {"starting", "bench", "not summoned"};

int maxPlayersPerStatus[MAX_ROLES] = {11,7,23};

int countStatus[MAX_STATUS] = {0};

char formations[MAX_FORMATIONS][100] = {
    "4-3-3",
    "4-4-2",
    "4-2-3-1",
    "4-5-1",
    "3-5-2",
    "3-4-3",
    "5-3-2",
    "5-4-1"
};

char formationRoles[MAX_FORMATIONS][11][100] = {
    // ---- 4-3-3 ----
    {
        "goalkeeper",
        "right back", "left back", "center back", "center back",
        "defensive midfielder", "central midfielder", "central midfielder",
        "left winger", "right winger", "striker"
    },

    // ---- 4-4-2 ----
    {
        "goalkeeper",
        "right back", "left back", "center back", "center back",
        "left midfielder", "right midfielder",
        "central midfielder", "central midfielder",
        "striker", "striker"
    },

    // ---- 4-2-3-1 ----
    {
        "goalkeeper",
        "right back", "left back", "center back", "center back",
        "defensive midfielder", "defensive midfielder",
        "left midfielder", "attacking midfielder", "right midfielder",
        "striker"
    },

    // ---- 4-5-1 ----
    {
        "goalkeeper",
        "right back", "left back", "center back", "center back",
        "defensive midfielder", "central midfielder", "central midfielder",
        "left midfielder", "right midfielder",
        "striker"
    },

    // ---- 3-5-2 ----
    {
        "goalkeeper",
        "center back", "center back", "center back",
        "left wing back", "right wing back",
        "defensive midfielder", "central midfielder", "attacking midfielder",
        "striker", "striker"
    },

    // ---- 3-4-3 ----
    {
        "goalkeeper",
        "center back", "center back", "center back",
        "left midfielder", "right midfielder",
        "central midfielder", "central midfielder",
        "left winger", "right winger", "striker"
    },

    // ---- 5-3-2 ----
    {
        "goalkeeper",
        "right back", "left back",
        "center back", "center back", "center back",
        "central midfielder", "central midfielder", "central midfielder",
        "striker", "striker"
    },

    // ---- 5-4-1 ----
    {
        "goalkeeper",
        "right back", "left back",
        "center back", "center back", "center back",
        "left midfielder", "right midfielder",
        "central midfielder", "central midfielder",
        "striker"
    }
};

char formation[20];

int players_count = 0;