#ifndef GLOBALVAR_H
#define GLOBALVAR_H

extern char validRoles[][100];

extern int maxPlayersPerRole[MAX_ROLES];

extern int countRoles[MAX_ROLES];

extern char validStatus[][100];

extern int maxPlayersPerStatus[MAX_ROLES];

extern int countStatus[MAX_STATUS];

extern char formations[MAX_FORMATIONS][100];

extern char formationRoles[MAX_FORMATIONS][11][100];

extern char formation[20];

extern int players_count;

#endif