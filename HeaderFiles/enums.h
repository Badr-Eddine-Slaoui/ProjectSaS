#ifndef ENUMS_H
#define ENUMS_H

enum Setings {
  MAX_ROLES = 15,
  MAX_STATUS = 3,
  MAX_PLAYERS = 23,
  MAX_FORMATIONS = 8
};

enum PrincipleMenu
{
    ADD = 1,
    DISPLAY,
    UPDATE,
    DELETE,
    SEARCH,
    STATISTICS,
    UPDATE_FORMATION,
    EXIT
};

enum AddMenu
{
    ADD_ONE = 1,
    ADD_MULTIPLE
};

enum DisplayMenu
{
    DISPLAY_ALL = 1,
    ALPHABETIC_SORT,
    AGE_SORT,
    DISPLAY_BY_POST
};

enum UpdateMenu
{
    UPDATE_FIRST_NAME = 1,
    UPDATE_LAST_NAME,
    UPDATE_AGE,
    UPDATE_NUMBER,
    UPDATE_POST,
    UPDATE_STATUS,
    UPDATE_GOALS
};

enum SearchMenu
{
    SEARCH_BY_ID = 1,
    SEARCH_BY_FIRST_NAME,
    SEARCH_BY_LAST_NAME,
    SEARCH_BY_AGE,
    SEARCH_BY_NUMBER,
    SEARCH_BY_ROLE,
    SEARCH_BY_GOALS,
    SEARCH_BY_STATUS,
    SEARCH_BY_AGE_RANGE
};

enum StatisticsMenu
{
    TOTAL = 1,
    AVG_AGE,
    GOALS,
    BEST_SCOORER,
    MIN_MAX_AGE
};

#endif