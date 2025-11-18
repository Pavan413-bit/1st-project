#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// first preview
struct Player {
    char name[30];
    int age;
    int speed;
    int power;
};

// create team menu
void createTeam(struct Player *team, int *n) {
    printf("Enter number of players (max 11): ");
    scanf("%d", n);

    for(int i = 0; i < *n; i++) {
        printf("\nEnter details for Player %d\n", i + 1);
        printf("Name: ");
        scanf("%s", team[i].name);
        printf("Age: ");
        scanf("%d", &team[i].age);
        printf("Speed (1-100): ");
        scanf("%d", &team[i].speed);
        printf("Power (1-100): ");
        scanf("%d", &team[i].power);
    }

    printf("\nTeam created successfully!\n");
}


// view team interface
void viewTeam(struct Player *team, int n) {
    printf("\n=== YOUR TEAM ===\n");
    for(int i = 0; i < n; i++) {
        printf("\nPlayer %d\n", i + 1);
        printf("Name: %s\n", team[i].name);
        printf("Age: %d\n", team[i].age);
        printf("Speed: %d\n", team[i].speed);
        printf("Power: %d\n", team[i].power);
    }
}

int calculateStrength(struct Player *team, int n) {
    int strength = 0;
    for(int i = 0; i < n; i++) {
        strength += team[i].speed + team[i].power;
    }
    return strength;
}

void playMatch(struct Player *team, int n) {
    if(n == 0) {
        printf("\nCreate your team first!\n");
        return;
    }

    srand(time(NULL));

    int yourStrength = calculateStrength(team, n);
    int oppStrength = (rand() % (yourStrength + 200)) + 100;  // Random opponent power
    int yourScore = (yourStrength / 50) + (rand() % 3);
    int oppScore = (oppStrength / 50) + (rand() % 3);

    printf("\n=== MATCH RESULT ===\n");
    printf("Your Strength: %d\nOpponent Strength: %d\n", yourStrength, oppStrength);
    printf("Score: YOU %d - %d OPPONENT\n", yourScore, oppScore);

    if(yourScore > oppScore)
        printf("\n YOU WIN!\n");
    else if(yourScore < oppScore)
        printf("\n YOU LOSE.\n");
    else
        printf("\n MATCH DRAW.\n");
}

void saveTeam(struct Player *team, int n) {
    FILE *fp = fopen("team.txt", "w");

    if(fp == NULL) {
        printf("\nError saving file.\n");
        return;
    }

    for(int i = 0; i < n; i++) {
        fprintf(fp, "%s %d %d %d\n", team[i].name, team[i].age, team[i].speed, team[i].power);
    }

    fclose(fp);
    printf("\nTeam saved to team.txt\n");
}

int main() {
    struct Player team[11];
    int n = 0;
    int choice;

    while(1) {
        printf("\n=== FOOTBALL MANAGER ===\n");
        printf("1. Create Team\n");
        printf("2. View Team\n");
        printf("3. Play Match\n");
        printf("4. Save Team\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: createTeam(team, &n); break;
            case 2: viewTeam(team, n); break;
            case 3: playMatch(team, n); break;
            case 4: saveTeam(team, n); break;
            case 5: exit(0);
            default: printf("\nInvalid choice!\n");
        }
    }
    return 0;
}
