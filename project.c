#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define RESET "\033[0m"
#define RED "\033[4;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define CYAN "\033[1;36m"
#define ORANGE "\033[38;5;208m"

enum PrincipleMenu
{
    ADD = 1,
    DISPLAY,
    UPDATE,
    DELETE,
    SEARCH,
    STATISTICS,
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
    UPDATE_POST = 1,
    UPDATE_AGE,
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

typedef struct Date
{
    int day;
    int month;
    int year;
} Date;

char validRoles[][100] = {"gardien", "defenseur", "milieu", "attaquant"};
char validStatus[][100] = {"titulaire", "remplacant"};

#define MAX_ROLES 4
#define MAX_STATUS 2

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

int players_count = 0;

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

void isValid(const char *prompt, char validList[][100], int listSize, char *var, size_t size)
{
    int isValidInput = 0;
    do
    {
        handle_fgets_input(prompt, var, size);

        for (int i = 0; i < listSize; i++)
        {
            if (strcmp(var, validList[i]) == 0)
            {
                isValidInput = 1;
                break;
            }
        }
        if (!isValidInput)
        {
            printf(YELLOW "Invalid input! Please enter a valid option.\n" RESET);
        }
    } while (!isValidInput);
}

void saveToFile(const Player *arr)
{
    FILE *fp = fopen("./players.dat", "wb");
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
    FILE *fp = fopen("./players.dat", "rb");
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
    printf(ORANGE "Loaded %d players from file.\n" RESET, players_count);
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

void addPlayers(Player **arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        Player newPlayer;
        newPlayer.id = (long)time(NULL);

        setCurrentDate(&newPlayer.registration_date);

        handle_fgets_input("Enter player's first name: ", newPlayer.first_name, sizeof(newPlayer.first_name));

        handle_fgets_input("Enter player's last name: ", newPlayer.last_name, sizeof(newPlayer.last_name));

        inputNumber("Enter player's age: ", "%d", &newPlayer.age);

        inputNumber("Enter player's number: ", "%d", &newPlayer.number);

        isValid("Enter player's role (gardien, defenseur, milieu, attaquant): ", validRoles, MAX_ROLES, newPlayer.role, sizeof(newPlayer.role));

        inputNumber("Enter player's goals: ", "%d", &newPlayer.goals);

        isValid("Enter player's status (titulaire, remplacant): ", validStatus, MAX_STATUS, newPlayer.status, sizeof(newPlayer.status));

        *arr = realloc(*arr, (players_count + 1) * sizeof(Player));
        if (*arr == NULL)
        {
            printf(RED "Error: Memory allocation failed!\n" RESET);
            return;
        }

        (*arr)[players_count] = newPlayer;
        players_count++;

        if (newPlayer.goals >= 10)
        {
            printf(ORANGE "This player is a high scorer!\n" RESET);
        }

        printf(GREEN "Player added successfully!\n" RESET);
    }
    saveToFile(*arr);
}

void sortPlayers(Player **arr, const char attr[])
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to display!\n" RESET);
        return;
    }

    printf(ORANGE "Sorting players by %s...\n" RESET, attr);
    char direction[5];
    do
    {
        handle_fgets_input("Enter sorting direction (asc/desc): ", direction, sizeof(direction));

        if (strcmp(direction, "asc") != 0 && strcmp(direction, "desc") != 0)
        {
            printf(YELLOW "Invalid direction! Please enter 'asc' or 'desc'.\n" RESET);
        }
    } while (strcmp(direction, "asc") != 0 && strcmp(direction, "desc") != 0);

    Player temp;
    for (int i = 0; i < players_count - 1; i++)
    {
        for (int j = 0; j < players_count - i - 1; j++)
        {
            if (strcmp(direction, "asc") == 0)
            {
                if (strcmp(attr, "alpha") == 0)
                {
                    if (strcmp((*arr)[j].last_name, (*arr)[j + 1].last_name) > 0)
                    {
                        temp = (*arr)[j];
                        (*arr)[j] = (*arr)[j + 1];
                        (*arr)[j + 1] = temp;
                    }
                }
                else if (strcmp(attr, "age") == 0)
                {
                    if ((*arr)[j].age > (*arr)[j + 1].age)
                    {
                        temp = (*arr)[j];
                        (*arr)[j] = (*arr)[j + 1];
                        (*arr)[j + 1] = temp;
                    }
                }
            }
            else if (strcmp(direction, "desc") == 0)
            {
                if (strcmp(attr, "alpha") == 0)
                {
                    if (strcmp((*arr)[j].last_name, (*arr)[j + 1].last_name) < 0)
                    {
                        temp = (*arr)[j];
                        (*arr)[j] = (*arr)[j + 1];
                        (*arr)[j + 1] = temp;
                    }
                }
                else if (strcmp(attr, "age") == 0)
                {
                    if ((*arr)[j].age < (*arr)[j + 1].age)
                    {
                        temp = (*arr)[j];
                        (*arr)[j] = (*arr)[j + 1];
                        (*arr)[j + 1] = temp;
                    }
                }
            }
        }
    }

    saveToFile(*arr);
    printf(GREEN "Players sorted successfully!\n" RESET);
    displayPlayers(arr);
}

void displayPlayersByPost(Player **arr)
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to display!\n" RESET);
        return;
    }

    int found = 0;
    for (int i = 0; i < 4; i++)
    {
        printf(ORANGE "\n--- Players in role: %s ---\n" RESET, validRoles[i]);
        found = 0;
        for (int j = 0; j < players_count; j++)
        {
            if (strcmp((*arr)[j].role, validRoles[i]) == 0)
            {
                displayPlayer(&(*arr)[j], j + 1);
                found = 1;
            }
        }
        if (!found)
        {
            printf(YELLOW "No players found in this role.\n" RESET);
        }
    }
}

void updatePlayerPost(Player **arr)
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to update!\n" RESET);
        return;
    }

    long id;
    char newRole[100];
    inputNumber("Enter player ID: ", "%ld", &id);

    int found = 0;
    for (int i = 0; i < players_count; i++)
    {
        if ((*arr)[i].id == id)
        {
            isValid("Enter new role (gardien, defenseur, milieu, attaquant): ", validRoles, MAX_ROLES, newRole, sizeof(newRole));

            strcpy((*arr)[i].role, newRole);
            found = 1;
            break;
        }
    }

    if (found)
    {
        saveToFile(*arr);
        printf(GREEN "Player role updated successfully!\n" RESET);
    }
    else
    {
        printf(ORANGE "Player not found!\n" RESET);
    }
}

void updatePlayerAge(Player **arr)
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to update!\n" RESET);
        return;
    }

    int newAge;
    long id;
    inputNumber("Enter player ID: ", "%ld", &id);

    int found = 0;
    for (int i = 0; i < players_count; i++)
    {
        if ((*arr)[i].id == id)
        {
            inputNumber("Enter new age: ", "%d", &newAge);
            (*arr)[i].age = newAge;
            found = 1;
            break;
        }
    }

    if (found)
    {
        saveToFile(*arr);
        printf(GREEN "Player age updated successfully!\n" RESET);
    }
    else
    {
        printf(ORANGE "Player not found!\n" RESET);
    }
}

void updatePlayerGoals(Player **arr)
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to update!\n" RESET);
        return;
    }

    int newGoals;
    long id;
    inputNumber("Enter player ID: ", "%ld", &id);

    int found = 0;
    for (int i = 0; i < players_count; i++)
    {
        if ((*arr)[i].id == id)
        {
            inputNumber("Enter new goals: ", "%d", &newGoals);
            (*arr)[i].goals = newGoals;
            found = 1;
            break;
        }
    }

    if (found)
    {
        saveToFile(*arr);
        if (newGoals >= 10)
        {
            printf(ORANGE "This player is a high scorer!\n" RESET);
        }

        printf(GREEN "Player goals updated successfully!\n" RESET);
    }
    else
    {
        printf(ORANGE "Player not found!\n" RESET);
    }
}

void deletePlayer(Player **arr)
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to delete!\n" RESET);
        return;
    }

    long id;
    inputNumber("Enter player ID to delete: ", "%ld", &id);

    char confirmation;

    int found = 0;
    for (int i = 0; i < players_count; i++)
    {
        if ((*arr)[i].id == id)
        {
            do
            {
                printf(CYAN "Are you sure you want to delete this player? (y/n): " RESET);
                scanf(" %c", &confirmation);
                clear_buffer();

                if (confirmation != 'y' && confirmation != 'n')
                {
                    printf(YELLOW "Invalid input! Please enter 'y' or 'n'.\n" RESET);
                }
            } while (confirmation != 'y' && confirmation != 'n');

            if (confirmation == 'n')
            {
                printf(ORANGE "Deletion cancelled.\n" RESET);
                return;
            }
            for (int j = i; j < players_count - 1; j++)
            {
                (*arr)[j] = (*arr)[j + 1];
            }
            players_count--;
            *arr = realloc(*arr, players_count * sizeof(Player));
            found = 1;
            break;
        }
    }

    if (found)
    {
        saveToFile(*arr);
        printf(GREEN "Player deleted successfully!\n" RESET);
    }
    else
    {
        printf(ORANGE "Player not found!\n" RESET);
    }
}

void searchPlayerByAttr(Player **arr, const int attr)
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to search!\n" RESET);
        return;
    }

    switch (attr)
    {
    case SEARCH_BY_ID:
    {
        long id;
        inputNumber("Enter player's ID: ", "%ld", &id);

        int found = 0;
        for (int i = 0; i < players_count; i++)
        {
            if ((*arr)[i].id == id)
            {
                displayPlayer(&(*arr)[i], i + 1);
                found = 1;
                break;
            }
        }
        if (!found)
        {
            printf(ORANGE "Player not found!\n" RESET);
        }
        break;
    }
    case SEARCH_BY_FIRST_NAME:
    {
        char firstName[100];
        handle_fgets_input("Enter player's first name: ", firstName, sizeof(firstName));

        int found = 0;
        for (int i = 0; i < players_count; i++)
        {
            if (strcmp((*arr)[i].first_name, firstName) == 0)
            {
                displayPlayer(&(*arr)[i], i + 1);
                found = 1;
            }
        }
        if (!found)
        {
            printf(ORANGE "No players found with this first name!\n" RESET);
        }
        break;
    }
    case SEARCH_BY_LAST_NAME:
    {
        char lastName[100];
        handle_fgets_input("Enter player's last name: ", lastName, sizeof(lastName));

        int found = 0;
        for (int i = 0; i < players_count; i++)
        {
            if (strcmp((*arr)[i].last_name, lastName) == 0)
            {
                displayPlayer(&(*arr)[i], i + 1);
                found = 1;
            }
        }
        if (!found)
        {
            printf(ORANGE "No players found with this last name!\n" RESET);
        }
        break;
    }
    case SEARCH_BY_AGE:
    {
        int age;
        inputNumber("Enter player's age: ", "%d", &age);

        int found = 0;
        for (int i = 0; i < players_count; i++)
        {
            if ((*arr)[i].age == age)
            {
                displayPlayer(&(*arr)[i], i + 1);
                found = 1;
            }
        }
        if (!found)
        {
            printf(ORANGE "No players found with this age!\n" RESET);
        }
        break;
    }
    case SEARCH_BY_NUMBER:
    {
        int number;
        inputNumber("Enter player's number: ", "%d", &number);

        int found = 0;
        for (int i = 0; i < players_count; i++)
        {
            if ((*arr)[i].number == number)
            {
                displayPlayer(&(*arr)[i], i + 1);
                found = 1;
            }
        }
        if (!found)
        {
            printf(ORANGE "No players found with this number!\n" RESET);
        }
        break;
    }
    case SEARCH_BY_ROLE:
    {
        char role[100];
        isValid("Enter player's role (gardien, defenseur, milieu, attaquant): ", validRoles, MAX_ROLES, role, sizeof(role));

        int found = 0;
        for (int i = 0; i < players_count; i++)
        {
            if (strcmp((*arr)[i].role, role) == 0)
            {
                displayPlayer(&(*arr)[i], i + 1);
                found = 1;
            }
        }
        if (!found)
        {
            printf(ORANGE "No players found with this role!\n" RESET);
        }
        break;
    }
    case SEARCH_BY_GOALS:
    {
        int goals;
        inputNumber("Enter player's goals: ", "%d", &goals);

        int found = 0;
        for (int i = 0; i < players_count; i++)
        {
            if ((*arr)[i].goals == goals)
            {
                displayPlayer(&(*arr)[i], i + 1);
                found = 1;
            }
        }
        if (!found)
        {
            printf(ORANGE "No players found with this number of goals!\n" RESET);
        }
        break;
    }
    case SEARCH_BY_STATUS:
    {
        char status[100];
        isValid("Enter player's status (titulaire, remplacant): ", validStatus, MAX_STATUS, status, sizeof(status));

        int found = 0;
        for (int i = 0; i < players_count; i++)
        {
            if (strcmp((*arr)[i].status, status) == 0)
            {
                displayPlayer(&(*arr)[i], i + 1);
                found = 1;
            }
        }
        if (!found)
        {
            printf(ORANGE "No players found with this status!\n" RESET);
        }
        break;
    }
    case SEARCH_BY_AGE_RANGE:
    {
        int minAge, maxAge;
        inputNumber("Enter minimum age: ", "%d", &minAge);
        inputNumber("Enter maximum age: ", "%d", &maxAge);

        if (minAge > maxAge)
        {
            printf(YELLOW "Invalid range! Minimum age cannot be greater than maximum age.\n" RESET);
            return;
        }

        int found = 0;
        for (int i = 0; i < players_count; i++)
        {
            if ((*arr)[i].age >= minAge && (*arr)[i].age <= maxAge)
            {
                displayPlayer(&(*arr)[i], i + 1);
                found = 1;
            }
        }
        if (!found)
        {
            printf(ORANGE "No players found in this age range!\n" RESET);
        }
        break;
    }
    case 10:
        break;
    default:
        printf(YELLOW "Search by this attribute is not implemented yet.\n" RESET);
    }
}

void displayPlayersTotal()
{
    printf("Total number of players: %d\n", players_count);
}

void displayAvgAge(Player **arr)
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to calculate average age!\n" RESET);
        return;
    }

    int totalAge = 0;
    for (int i = 0; i < players_count; i++)
    {
        totalAge += (*arr)[i].age;
    }
    double avgAge = (double)totalAge / players_count;
    printf("Average age of players: %.2f\n", avgAge);
}

void displayPlayersWithNGoals(Player **arr)
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to display!\n" RESET);
        return;
    }

    int n;
    inputNumber("Enter minimum number of goals: ", "%d", &n);

    int found = 0;
    printf("Players with at least %d goals:\n", n);
    for (int i = 0; i < players_count; i++)
    {
        if ((*arr)[i].goals >= n)
        {
            displayPlayer(&(*arr)[i], i + 1);
            found = 1;
        }
    }

    if (!found)
    {
        printf(ORANGE "No players found with at least %d goals.\n" RESET, n);
    }
}

void displayBestScorer(Player **arr)
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to display!\n" RESET);
        return;
    }

    int maxGoals = -1;
    for (int i = 0; i < players_count; i++)
    {
        if ((*arr)[i].goals > maxGoals)
        {
            maxGoals = (*arr)[i].goals;
        }
    }

    printf("Best scorer(s) with %d goals:\n", maxGoals);
    for (int i = 0; i < players_count; i++)
    {
        if ((*arr)[i].goals == maxGoals)
        {
            displayPlayer(&(*arr)[i], i + 1);
        }
    }
}

void displayMinMaxAge(Player **arr)
{
    if (players_count == 0)
    {
        printf(ORANGE "No players to display!\n" RESET);
        return;
    }

    int minAge = (*arr)[0].age;
    int maxAge = (*arr)[0].age;
    int minIndex = 0, maxIndex = 0;

    for (int i = 1; i < players_count; i++)
    {
        if ((*arr)[i].age < minAge)
        {
            minAge = (*arr)[i].age;
            minIndex = i;
        }
        if ((*arr)[i].age > maxAge)
        {
            maxAge = (*arr)[i].age;
            maxIndex = i;
        }
    }

    printf("Youngest player age: %d\n", minAge);
    printf("Youngest player: ");
    displayPlayer(&(*arr)[minIndex], minIndex + 1);
    printf("Oldest player age: %d\n", maxAge);
    printf("Oldest player: ");
    displayPlayer(&(*arr)[maxIndex], maxIndex + 1);
}

void saveFakeDataToFile()
{
    Player fakeData[10] = {
        {1625152800, "lionel", "messi", 34, 10, "attaquant", 30, {1, 7, 2021}, "titulaire"},
        {1625239200, "cristiano", "ronaldo", 36, 7, "attaquant", 25, {2, 7, 2021}, "titulaire"},
        {1625325600, "neymar", "jr", 29, 11, "attaquant", 20, {3, 7, 2021}, "titulaire"},
        {1625412000, "kevin", "de bruyne", 30, 17, "milieu", 10, {4, 7, 2021}, "titulaire"},
        {1625498400, "virgil", "van dijk", 30, 4, "defenseur", 5, {5, 7, 2021}, "titulaire"},
        {1625584800, "manuel", "neuer", 35, 1, "gardien", 0, {6, 7, 2021}, "titulaire"},
        {1625671200, "kylian", "mbappe", 22, 7, "attaquant", 15, {7, 7, 2021}, "titulaire"},
        {1625757600, "luka", "modric", 36, 10, "milieu", 8, {8, 7, 2021}, "titulaire"},
        {1625844000, "sergio", "ramos", 35, 4, "defenseur", 6, {9, 7, 2021}, "titulaire"},
        {1625930400, "thibaut", "courtois", 29, 1, "gardien", 0, {10, 7, 2021}, "titulaire"}};

    FILE *fp = fopen("./players.dat", "wb");
    if (fp == NULL)
    {
        printf("Error: Unable to save fake data to file!\n");
        return;
    }
    fwrite(fakeData, sizeof(Player), 10, fp);
    fclose(fp);
    printf("Fake data saved to file successfully!\n");
}

int main()
{
    // saveFakeDataToFile();

    Player *Players = NULL;

    loadFromFile(&Players);

    while (1)
    {
        printf(RED "\n=== Player Management System ===\n" RESET);
        printf("Enter 1 to add a player\n");
        printf("Enter 2 to display players\n");
        printf("Enter 3 to update a player\n");
        printf("Enter 4 to delete a players\n");
        printf("Enter 5 to search for a player\n");
        printf("Enter 6 to display statistics\n");
        printf("Enter 7 to exit\n");

        int choice;
        inputNumber("Your choice: ", "%d", &choice);

        switch (choice)
        {
        case ADD:
        {
            printf(RED "\n=== Add Player Menu ===\n" RESET);
            printf("Enter 1 to add a player\n");
            printf("Enter 2 to add n players\n");
            printf("Enter 3 to return to main menu\n");

            int add_choice;
            inputNumber("Your choice: ", "%d", &add_choice);

            switch (add_choice)
            {
            case ADD_ONE:
                addPlayers(&Players, 1);
                break;
            case ADD_MULTIPLE:
                int n;
                inputNumber("Enter number of players to add: ", "%d", &n);

                addPlayers(&Players, n);
                break;
            case 3:
                break;
            default:
                printf(YELLOW "Invalid choice\n" RESET);
            }
            break;
        }
        case DISPLAY:
        {
            printf(RED "\n=== Display Player Menu ===\n" RESET);
            printf("Enter 1 to display all players\n");
            printf("Enter 2 to display players sorted alphabetically by last name\n");
            printf("Enter 3 to display players sorted by age\n");
            printf("Enter 4 to display players by post\n");
            printf("Enter 5 to return to main menu\n");

            int display_choice;

            inputNumber("Your choice: ", "%d", &display_choice);

            switch (display_choice)
            {
            case DISPLAY_ALL:
                displayPlayers(&Players);
                break;
            case ALPHABETIC_SORT:
                sortPlayers(&Players, "alpha");
                break;
            case AGE_SORT:
                sortPlayers(&Players, "age");
                break;
            case DISPLAY_BY_POST:
                displayPlayersByPost(&Players);
                break;
            case 5:
                break;
            default:
                printf(YELLOW "Invalid choice\n" RESET);
            }
            break;
        }
        case UPDATE:
        {
            printf(RED "\n=== Update Player Menu ===\n" RESET);
            printf("Enter 1 to update player's post\n");
            printf("Enter 2 to update player's age\n");
            printf("Enter 3 to update player's goals\n");
            printf("Enter 4 to return to main menu\n");

            int update_choice;
            inputNumber("Your choice: ", "%d", &update_choice);

            switch (update_choice)
            {
            case UPDATE_POST:
                updatePlayerPost(&Players);
                break;
            case UPDATE_AGE:
                updatePlayerAge(&Players);
                break;
            case UPDATE_GOALS:
                updatePlayerGoals(&Players);
                break;
            case 4:
                break;
            default:
                printf(YELLOW "Invalid choice\n" RESET);
            }
            break;
        }
        case DELETE:
            deletePlayer(&Players);
            break;
        case SEARCH:
        {
            printf(RED "\n=== Search Player Menu ===\n" RESET);
            printf("Enter 1 to search by ID\n");
            printf("Enter 2 to search by first name\n");
            printf("Enter 3 to search by last name\n");
            printf("Enter 4 to search by age\n");
            printf("Enter 5 to search by number\n");
            printf("Enter 6 to search by role\n");
            printf("Enter 7 to search by goals\n");
            printf("Enter 8 to search by status\n");
            printf("Enter 9 to search by age range\n");
            printf("Enter 10 to return to main menu\n");

            int search_choice;
            inputNumber("Your choice: ", "%d", &search_choice);

            searchPlayerByAttr(&Players, search_choice);
            break;
        }
        case STATISTICS:
        {
            printf(RED "\n=== Statistics Menu ===\n" RESET);
            printf("Enter 1 to display total number of players\n");
            printf("Enter 2 to display average age of players\n");
            printf("Enter 3 to display players with at least n goals\n");
            printf("Enter 4 to display best scorer(s)\n");
            printf("Enter 5 to display youngest and oldest player ages\n");
            printf("Enter 6 to return to main menu\n");

            int stats_choice;
            inputNumber("Your choice: ", "%d", &stats_choice);

            switch (stats_choice)
            {
            case TOTAL:
                displayPlayersTotal();
                break;
            case AVG_AGE:
                displayAvgAge(&Players);
                break;
            case GOALS:
                displayPlayersWithNGoals(&Players);
                break;
            case BEST_SCOORER:
                displayBestScorer(&Players);
                break;
            case MIN_MAX_AGE:
                displayMinMaxAge(&Players);
                break;
            case 6:
                break;
            default:
                printf(YELLOW "Invalid choice\n" RESET);
            }
            break;
        }
        case EXIT:
            if (Players)
                free(Players);
            printf(ORANGE "Goodbye!\n" RESET);
            exit(0);
        default:
            printf(YELLOW "Invalid choice\n" RESET);
        }
    }
    return 0;
}