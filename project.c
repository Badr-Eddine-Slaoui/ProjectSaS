#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

typedef struct Date{
    int day;
    int month;
    int year;
} Date;

char validPosts[][100] = {"gardien", "defenseur", "milieu", "attaquant"};
char validStatus[][100] = {"titulaire", "remplacant"};

typedef struct Player {
    long id;
    char first_name[100];
    char last_name[100];
    int age;
    int number;
    char role[100];
    int goals;
    Date inscreption_date;
    char status[100];
} Player;

int players_count = 0;

void clear_buffer() {
    while (getchar() != '\n');
}

void clear_newline(char str[]) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    } else {
        clear_buffer();
    }
}

void saveToFile(Player *arr) {
    FILE *fp = fopen("./players.dat", "wb");
    if (fp == NULL) {
        printf("Error: Unable to save to file!\n");
        return;
    }
    if (players_count > 0) {
        fwrite(arr, sizeof(Player), players_count, fp);
    }
    fclose(fp);
}

void loadFromFile(Player **arr) {
    FILE *fp = fopen("./players.dat", "rb");
    if (fp == NULL) {
        printf("No existing data file found. Starting fresh.\n");
        players_count = 0;
        *arr = NULL;
        return;
    }

    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);
    
    if (fileSize == 0) {
        printf("Data file is empty. Starting fresh.\n");
        players_count = 0;
        *arr = NULL;
        fclose(fp);
        return;
    }

    players_count = fileSize / sizeof(Player);
    *arr = malloc(players_count * sizeof(Player));
    
    if (*arr == NULL) {
        printf("Error: Memory allocation failed!\n");
        players_count = 0;
        fclose(fp);
        return;
    }

    int items_read = fread(*arr, sizeof(Player), players_count, fp);
    if (items_read != players_count) {
        printf("Warning: Could not read all players from file!\n");
        players_count = items_read;
    }
    
    fclose(fp);
    printf("Loaded %d players from file.\n", players_count);
}

void setCurrentDate(Date *date){
    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    date->day = local->tm_mday;
    date->month = local->tm_mon + 1;
    date->year = local->tm_year + 1900;
}

void displayPlayer(Player player, int i) {
    printf("\nPlayer %d:\n", i);
    printf("  ID       : %ld\n", player.id);
    printf("  First Name: %s\n", player.first_name);
    printf("  Last Name : %s\n", player.last_name);
    printf("  Age      : %d\n", player.age);
    printf("  Number   : %d\n", player.number);
    printf("  Role     : %s\n", player.role);
    printf("  Goals    : %d\n", player.goals);
    printf("  Inscription Date: %02d/%02d/%04d\n", player.inscreption_date.day, player.inscreption_date.month, player.inscreption_date.year);
    printf("  Status   : %s\n", player.status);
}

void displayPlayers(Player **arr) {
    if (players_count == 0) {
        printf("No players to display!\n");
        return;
    }

    for (int i = 0; i < players_count; i++) {
        displayPlayer((*arr)[i], i + 1);
    }
}

void addPlayers(Player **arr, int n) {
    for (int i = 0; i < n; i++)
    {
        Player newPlayer;
        time_t id = time(NULL);
        newPlayer.id = id;
        setCurrentDate(&newPlayer.inscreption_date);

        printf("Enter player's first name: ");
        fgets(newPlayer.first_name, sizeof(newPlayer.first_name), stdin);
        clear_newline(newPlayer.first_name);

        printf("Enter player's last name: ");
        fgets(newPlayer.last_name, sizeof(newPlayer.last_name), stdin);
        clear_newline(newPlayer.last_name);

        printf("Enter player's age: ");
        scanf("%d", &newPlayer.age);
        clear_buffer();

        printf("Enter player's number: ");
        scanf("%d", &newPlayer.number);
        clear_buffer();

        int validRole = 0;
        do
        {
            printf("Enter player's role (gardien, defenseur, milieu, attaquant): ");
            fgets(newPlayer.role, sizeof(newPlayer.role), stdin);
            clear_newline(newPlayer.role);

            for (int i = 0; i < 4; i++) {
                if (strcmp(newPlayer.role, validPosts[i]) == 0) {
                    validRole = 1;
                    break;
                }
            }
            if (!validRole) {
                printf("Invalid role! Please enter a valid role.\n");
            }
        } while (!validRole);

        printf("Enter player's goals: ");
        scanf("%d", &newPlayer.goals);
        clear_buffer();

        int isValidStatus = 0;
        do
        {
            printf("Enter player's status (titulaire, remplacant): ");
            fgets(newPlayer.status, sizeof(newPlayer.status), stdin);
            clear_newline(newPlayer.status);

            for (int i = 0; i < 2; i++) {
                if (strcmp(newPlayer.status, validStatus[i]) == 0) {
                    isValidStatus = 1;
                    break;
                }
            }
            if (!isValidStatus) {
                printf("Invalid status! Please enter a valid status.\n");
            }
        } while (!isValidStatus);

        *arr = realloc(*arr, (players_count + 1) * sizeof(Player));
        if (*arr == NULL) {
            printf("Error: Memory allocation failed!\n");
            return;
        }
        
        (*arr)[players_count] = newPlayer;
        players_count++;

        saveToFile(*arr);
        if (newPlayer.goals >= 10)
        {
            printf("This player is a high scorer!\n");
        }
        
        printf("Player added successfully!\n");
    }
}

void sortPlayers(Player **arr, char attr[]) {
    if (players_count == 0) {
        printf("No players to display!\n");
        return;
    }

    Player temp;
    for (int i = 0; i < players_count - 1; i++) {   
        for (int j = 0; j < players_count - i - 1; j++) {   
            if (strcmp(attr, "alpha") == 0) {
                if (strcmp((*arr)[j].last_name, (*arr)[j+1].last_name) > 0) {
                    temp = (*arr)[j];
                    (*arr)[j] = (*arr)[j + 1];
                    (*arr)[j + 1] = temp;
                }
            } else if (strcmp(attr, "age") == 0) {
                if ((*arr)[j].age > (*arr)[j+1].age) {
                    temp = (*arr)[j];
                    (*arr)[j] = (*arr)[j + 1];
                    (*arr)[j + 1] = temp;
                }
            }
        }
    }

    saveToFile(*arr);
    printf("Players sorted successfully!\n");
    displayPlayers(arr);
}

void displayPlayersByPost(Player **arr) {
    if (players_count == 0) {
        printf("No players to display!\n");
        return;
    }

    int found = 0;
    for (int i = 0; i < 4; i++) {
        printf("\n--- Players in role: %s ---\n", validPosts[i]);
        found = 0;
        for (int j = 0; j < players_count; j++) {
            if (strcmp((*arr)[j].role, validPosts[i]) == 0) {
                displayPlayer((*arr)[j], j + 1);
                found = 1;
            }
        }
        if (!found) {
            printf("No players found in this role.\n");
        }
    }
}

void updatePlayerPost(Player **arr) {
    if (players_count == 0) {
        printf("No players to update!\n");
        return;
    }

    long id;
    char newRole[100];
    printf("Enter player ID: ");
    scanf("%ld", &id);
    clear_buffer();

    int found = 0;
    for (int i = 0; i < players_count; i++) {
        if ((*arr)[i].id == id) {
            int validRole = 0;
            do
            {
                printf("Enter new role (gardien, defenseur, milieu, attaquant): ");
                fgets(newRole, sizeof(newRole), stdin);
                clear_newline(newRole);

                for (int j = 0; j < 4; j++) {
                    if (strcmp(newRole, validPosts[j]) == 0) {
                        validRole = 1;
                        break;
                    }
                }
                if (!validRole) {
                    printf("Invalid role! Please enter a valid role.\n");
                }
            } while (!validRole);

            strcpy((*arr)[i].role, newRole);
            found = 1;
            break;
        }
    }

    if (found) {
        saveToFile(*arr);
        printf("Player role updated successfully!\n");
    } else {
        printf("Player not found!\n");
    }
}

void updatePlayerAge(Player **arr) {
    if (players_count == 0) {
        printf("No players to update!\n");
        return;
    }

    int newAge;
    long id;
    printf("Enter player ID: ");
    scanf("%ld", &id);
    clear_buffer();

    printf("Enter new age: ");
    scanf("%d", &newAge);
    clear_buffer();

    int found = 0;
    for (int i = 0; i < players_count; i++) {
        if ((*arr)[i].id == id) {
            (*arr)[i].age = newAge;
            found = 1;
            break;
        }
    }

    if (found) {
        saveToFile(*arr);
        printf("Player age updated successfully!\n");
    } else {
        printf("Player not found!\n");
    }
}

void updatePlayerGoals(Player **arr) {
    if (players_count == 0) {
        printf("No players to update!\n");
        return;
    }

    int newGoals;
    long id;
    printf("Enter player ID: ");
    scanf("%ld", &id);
    clear_buffer();

    printf("Enter new goals: ");
    scanf("%d", &newGoals);
    clear_buffer();

    int found = 0;
    for (int i = 0; i < players_count; i++) {
        if ((*arr)[i].id == id) {
            (*arr)[i].goals = newGoals;
            found = 1;
            break;
        }
    }

    if (found) {
        saveToFile(*arr);
        if (newGoals >= 10)
        {
            printf("This player is a high scorer!\n");
        }
        
        printf("Player goals updated successfully!\n");
    } else {
        printf("Player not found!\n");
    }
}

void deletePlayer(Player **arr) {
    if (players_count == 0) {
        printf("No players to delete!\n");
        return;
    }

    long id;
    printf("Enter player ID to delete: ");
    scanf("%ld", &id);
    clear_buffer();

    int found = 0;
    for (int i = 0; i < players_count; i++) {
        if ((*arr)[i].id == id) {
            for (int j = i; j < players_count - 1; j++) {
                (*arr)[j] = (*arr)[j + 1];
            }
            players_count--;
            *arr = realloc(*arr, players_count * sizeof(Player));
            found = 1;
            break;
        }
    }

    if (found) {
        saveToFile(*arr);
        printf("Player deleted successfully!\n");
    } else {
        printf("Player not found!\n");
    }
}

void searchPlayerByAttr(Player **arr, int attr) {
    if (players_count == 0) {
        printf("No players to search!\n");
        return;
    }

    switch (attr) {
        case SEARCH_BY_ID: {
            long id;
            printf("Enter player ID: ");
            if (scanf("%ld", &id) != 1) {
                printf("Invalid input! Please enter a number.\n");
                clear_buffer();
                return;
            }
            clear_buffer();

            int found = 0;
            for (int i = 0; i < players_count; i++) {
                if ((*arr)[i].id == id) {
                    displayPlayer((*arr)[i], i + 1);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("Player not found!\n");
            }
            break;
        }
        case SEARCH_BY_FIRST_NAME: {
            char firstName[100];
            printf("Enter player's first name: ");
            fgets(firstName, sizeof(firstName), stdin);
            clear_newline(firstName);

            int found = 0;
            for (int i = 0; i < players_count; i++) {
                if (strcmp((*arr)[i].first_name, firstName) == 0) {
                    displayPlayer((*arr)[i], i + 1);
                    found = 1;
                }
            }
            if (!found) {
                printf("No players found with this first name!\n");
            }
            break;
        }
        case SEARCH_BY_LAST_NAME: {
            char lastName[100];
            printf("Enter player's last name: ");
            fgets(lastName, sizeof(lastName), stdin);
            clear_newline(lastName);

            int found = 0;
            for (int i = 0; i < players_count; i++) {
                if (strcmp((*arr)[i].last_name, lastName) == 0) {
                    displayPlayer((*arr)[i], i + 1);
                    found = 1;
                }
            }
            if (!found) {
                printf("No players found with this last name!\n");
            }
            break;
        }
        case SEARCH_BY_AGE: {
            int age;
            printf("Enter player's age: ");
            if (scanf("%d", &age) != 1) {
                printf("Invalid input! Please enter a number.\n");
                clear_buffer();
                return;
            }
            clear_buffer();

            int found = 0;
            for (int i = 0; i < players_count; i++) {
                if ((*arr)[i].age == age) {
                    displayPlayer((*arr)[i], i + 1);
                    found = 1;
                }
            }
            if (!found) {
                printf("No players found with this age!\n");
            }
            break;
        }
        case SEARCH_BY_NUMBER: {
            int number;
            printf("Enter player's number: ");
            if (scanf("%d", &number) != 1) {
                printf("Invalid input! Please enter a number.\n");
                clear_buffer();
                return;
            }
            clear_buffer();

            int found = 0;
            for (int i = 0; i < players_count; i++) {
                if ((*arr)[i].number == number) {
                    displayPlayer((*arr)[i], i + 1);
                    found = 1;
                }
            }
            if (!found) {
                printf("No players found with this number!\n");
            }
            break;
        }
        case SEARCH_BY_ROLE: {
            char role[100];
            int validRole = 0;
            do
            {
                printf("Enter player's role (gardien, defenseur, milieu, attaquant): ");
                fgets(role, sizeof(role), stdin);
                clear_newline(role);

                for (int i = 0; i < 4; i++) {
                    if (strcmp(role, validPosts[i]) == 0) {
                        validRole = 1;
                        break;
                    }
                }
                if (!validRole) {
                    printf("Invalid role! Please enter a valid role.\n");
                }
            } while (!validRole);

            int found = 0;
            for (int i = 0; i < players_count; i++) {
                if (strcmp((*arr)[i].role, role) == 0) {
                    displayPlayer((*arr)[i], i + 1);
                    found = 1;
                }
            }
            if (!found) {
                printf("No players found with this role!\n");
            }
            break;
        }
        case SEARCH_BY_GOALS: {
            int goals;
            printf("Enter player's goals: ");
            if (scanf("%d", &goals) != 1) {
                printf("Invalid input! Please enter a number.\n");
                clear_buffer();
                return;
            }
            clear_buffer();

            int found = 0;
            for (int i = 0; i < players_count; i++) {
                if ((*arr)[i].goals == goals) {
                    displayPlayer((*arr)[i], i + 1);
                    found = 1;
                }
            }
            if (!found) {
                printf("No players found with this number of goals!\n");
            }
            break;
        }
        case SEARCH_BY_STATUS: {
            char status[100];
            int validStatusInput = 0;
            do
            {
                printf("Enter player's status (titulaire, remplacant): ");
                fgets(status, sizeof(status), stdin);
                clear_newline(status);

                for (int i = 0; i < 2; i++) {
                    if (strcmp(status, validStatus[i]) == 0) {
                        validStatusInput = 1;
                        break;
                    }
                }
                if (!validStatusInput) {
                    printf("Invalid status! Please enter a valid status.\n");
                }
            } while (!validStatusInput);

            int found = 0;
            for (int i = 0; i < players_count; i++) {
                if (strcmp((*arr)[i].status, status) == 0) {
                    displayPlayer((*arr)[i], i + 1);
                    found = 1;
                }
            }
            if (!found) {
                printf("No players found with this status!\n");
            }
            break;
        }
        case SEARCH_BY_AGE_RANGE: {
            int minAge, maxAge;
            printf("Enter minimum age: ");
            if (scanf("%d", &minAge) != 1) {
                printf("Invalid input! Please enter a number.\n");
                clear_buffer();
                return;
            }
            clear_buffer();

            printf("Enter maximum age: ");
            if (scanf("%d", &maxAge) != 1) {
                printf("Invalid input! Please enter a number.\n");
                clear_buffer();
                return;
            }
            clear_buffer();

            if (minAge > maxAge) {
                printf("Invalid range! Minimum age cannot be greater than maximum age.\n");
                return;
            }

            int found = 0;
            for (int i = 0; i < players_count; i++) {
                if ((*arr)[i].age >= minAge && (*arr)[i].age <= maxAge) {
                    displayPlayer((*arr)[i], i + 1);
                    found = 1;
                }
            }
            if (!found) {
                printf("No players found in this age range!\n");
            }
            break;
        }
        default:
            printf("Search by this attribute is not implemented yet.\n");
    }
}

void displayPlayersTotal() {
    printf("Total number of players: %d\n", players_count);
}

void displayAvgAge(Player **arr) {
    if (players_count == 0) {
        printf("No players to calculate average age!\n");
        return;
    }

    int totalAge = 0;
    for (int i = 0; i < players_count; i++) {
        totalAge += (*arr)[i].age;
    }
    double avgAge = (double)totalAge / players_count;
    printf("Average age of players: %.2f\n", avgAge);
}

void displayPlayersWithNGoals(Player **arr) {
    if (players_count == 0) {
        printf("No players to display!\n");
        return;
    }

    int n;
    printf("Enter the minimum number of goals: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input! Please enter a number.\n");
        clear_buffer();
        return;
    }
    clear_buffer();

    int found = 0;
    printf("Players with at least %d goals:\n", n);
    for (int i = 0; i < players_count; i++) {
        if ((*arr)[i].goals >= n) {
            displayPlayer((*arr)[i], i + 1);
            found = 1;
        }
    }

    if (!found) {
        printf("No players found with at least %d goals.\n", n);
    }
}

void displayBestScorer(Player **arr) {
    if (players_count == 0) {
        printf("No players to display!\n");
        return;
    }

    int maxGoals = -1;
    for (int i = 0; i < players_count; i++) {
        if ((*arr)[i].goals > maxGoals) {
            maxGoals = (*arr)[i].goals;
        }
    }

    printf("Best scorer(s) with %d goals:\n", maxGoals);
    for (int i = 0; i < players_count; i++) {
        if ((*arr)[i].goals == maxGoals) {
            displayPlayer((*arr)[i], i + 1);
        }
    }
}

void displayMinMaxAge(Player **arr) {
    if (players_count == 0) {
        printf("No players to display!\n");
        return;
    }

    int minAge = (*arr)[0].age;
    int maxAge = (*arr)[0].age;
    int minIndex = 0, maxIndex = 0;

    for (int i = 1; i < players_count; i++) {
        if ((*arr)[i].age < minAge) {
            minAge = (*arr)[i].age;
            minIndex = i;
        }
        if ((*arr)[i].age > maxAge) {
            maxAge = (*arr)[i].age;
            maxIndex = i;
        }
    }

    printf("Youngest player age: %d\n", minAge);
    printf("Youngest player: ");
    displayPlayer((*arr)[minIndex], minIndex + 1);
    printf("Oldest player age: %d\n", maxAge);
    printf("Oldest player: ");
    displayPlayer((*arr)[maxIndex], maxIndex + 1);
}

int main() {
    Player *Players = NULL;
    
    loadFromFile(&Players);

    while (1) {
        printf("\n=== Player Management System ===\n");
        printf("Enter 1 to add a player\n");
        printf("Enter 2 to display players\n");
        printf("Enter 3 to update a player\n");
        printf("Enter 4 to delete a players\n");
        printf("Enter 5 to search for a player\n");
        printf("Enter 6 to display statistics\n");
        printf("Enter 7 to exit\n");
        printf("Your choice: ");
        
        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clear_buffer();
            continue;
        }
        clear_buffer();

        switch (choice) {
            case ADD:{
                printf("\n=== Add Players Menu ===\n");
                printf("Enter 1 to add a player\n");
                printf("Enter 2 to add n player\n");
                printf("Your choice: ");

                int add_choice;
                if (scanf("%d", &add_choice) != 1) {
                    printf("Invalid input! Please enter a number.\n");
                    clear_buffer();
                    continue;
                }
                clear_buffer();
                switch (add_choice) {
                    case ADD_ONE:
                        addPlayers(&Players, 1);
                        break;
                    case ADD_MULTIPLE:
                        int n;
                        printf("Enter players number: ");
                        if (scanf("%d", &n) != 1) {
                            printf("Invalid input! Please enter a number.\n");
                            clear_buffer();
                            continue;
                        }
                        clear_buffer();
                        addPlayers(&Players, n);
                        break;
                    default:
                        printf("Invalid choice\n");
                }
                break;
            }
            case DISPLAY:{
                printf("\n=== Display Players Menu ===\n");
                printf("Enter 1 to display all players\n");
                printf("Enter 2 to display players sorted alphabetically by last name\n");
                printf("Enter 3 to display players sorted by age\n");
                printf("Enter 4 to display players by post\n");
                printf("Your choice: ");

                int display_choice;
                if (scanf("%d", &display_choice) != 1) {
                    printf("Invalid input! Please enter a number.\n");
                    clear_buffer();
                    continue;
                }
                clear_buffer();
                switch (display_choice) {
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
                    default:
                        printf("Invalid choice\n");
                }
                break;
            }
            case UPDATE:{
                printf("\n=== Update Player Menu ===\n");
                printf("Enter 1 to update player's post\n");
                printf("Enter 2 to update player's age\n");
                printf("Enter 3 to update player's goals\n");
                printf("Your choice: ");

                int update_choice;
                if (scanf("%d", &update_choice) != 1) {
                    printf("Invalid input! Please enter a number.\n");
                    clear_buffer();
                    continue;
                }
                clear_buffer();
                switch (update_choice) {
                    case UPDATE_POST:
                        updatePlayerPost(&Players);
                        break;
                    case UPDATE_AGE:
                        updatePlayerAge(&Players);
                        break;
                    case UPDATE_GOALS:
                        updatePlayerGoals(&Players);
                        break;
                    default:
                        printf("Invalid choice\n");
                }
                break;
            }
            case DELETE:
                deletePlayer(&Players);
                break;
            case SEARCH:{
                    printf("\n=== Search Player Menu ===\n");
                    printf("Enter 1 to search by ID\n");
                    printf("Enter 2 to search by first name\n");
                    printf("Enter 3 to search by last name\n");
                    printf("Enter 4 to search by age\n");
                    printf("Enter 5 to search by number\n");
                    printf("Enter 6 to search by role\n");
                    printf("Enter 7 to search by goals\n");
                    printf("Enter 8 to search by status\n");
                    printf("Enter 9 to search by age range\n");
                    printf("Your choice: ");

                    int search_choice;
                    if (scanf("%d", &search_choice) != 1) {
                        printf("Invalid input! Please enter a number.\n");
                        clear_buffer();
                        continue;
                    }
                    clear_buffer();

                    searchPlayerByAttr(&Players, search_choice);
                    break;
                }
            case STATISTICS:{
                printf("\n=== Statistics Menu ===\n");
                printf("Enter 1 to display total number of players\n");
                printf("Enter 2 to display average age of players\n");
                printf("Enter 3 to display players with at least n goals\n");
                printf("Enter 4 to display best scorer(s)\n");
                printf("Enter 5 to display youngest and oldest player ages\n");
                printf("Your choice: ");

                int stats_choice;
                if (scanf("%d", &stats_choice) != 1) {
                    printf("Invalid input! Please enter a number.\n");
                    clear_buffer();
                    continue;
                }
                clear_buffer();
                switch (stats_choice) {
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
                    default:
                        printf("Invalid choice\n");
                }
                break;
            }
            case EXIT:
                if (Players) free(Players);
                printf("Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}