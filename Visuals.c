//Imports
#include "Board.h"
#include "Colors.h"

// Loads the menu
void LoadMenu() {
    printf(CYAN "=== MENU ===\n\n" RESET);
    printf("[1] Player Vs. Player\n");
    printf("[2] Player Vs. Computer\n");
    printf("[3] Exit Game\n");
}

// Clearing the console after a round
void CleanConsole() {
	system("cls");
}

// Prints the logo of the game
void printLogo() {
    CleanConsole();
    printf(CYAN "=======================================================\n" RESET);

    printf(YELLOW "   ___ ___  _  _  _  _  ___  ___  _____ \n");
    printf(YELLOW "  / __/ _ \\| \\| || \\| || __|/ __||_   _|\n");
    printf(YELLOW " | (_| (_) | .` || .` || _| | (__   | |  \n");
    printf(YELLOW "  \\___\\___/|_|\\_||_|\\_||___| \\___|  |_|  \n");

    printf(RED    "           ___ ___  _   _  ___            \n");
    printf(RED    "          | __/ _ \\| | | || _ \\           \n");
    printf(RED    "          | _| (_) | |_| ||   /           \n");
    printf(RED    "          |_| \\___/ \\___/ |_|_\\           \n");

    printf("\n" RESET);

    printf(CYAN "=======================================================\n" RESET);
    printf(CYAN "       Created by: [Adi Makmal] & [Idan]         \n" RESET);
    printf(CYAN "=======================================================\n" RESET);
    printf("\n");
}

// Prints the current game Matrix
void printBoard(int gameArr[][COLS], char* msg) {
    CleanConsole(); 

    int i, j;

    for (i = 0; i < ROWS; i++) {
        printf("  "); 
        for (int k = 0; k < COLS; k++) {
            printf("+---");
        }
        printf("+\n");

        printf("  ");
        for (j = 0; j < COLS; j++) {
            printf("|");

            int cellValue = gameArr[i][j];
            if (cellValue == 0) {
                printf("   ");
            }
            else if (cellValue == 1) {
                printf(" ");
                printf(YELLOW "O" RESET);
                printf(" ");
            }
            else if (cellValue == 2) {
                printf(" ");
                printf(RED "O" RESET);
                printf(" ");
            }
        }
        printf("|\n");
    }

    printf("  ");
    for (int k = 0; k < COLS; k++) {
        printf("+---");
    }
    printf("+\n");

    printf("    1   2   3   4   5   6   7\n\n");
    if (msg != NULL && msg[0] != '\0') {
        printf("  [GAME INFO]: %s \n", msg);
    }
}

// Prints the stats.
void printStats(int p1, int p2, int pc) {
    printf("\n" CYAN "=== Game Statistics ===" RESET "\n");
    printf("Player 1 Wins: %d\n", p1);
    printf("Player 2 Wins: %d\n", p2);
    printf("Computer Wins: %d\n", pc);
    printf("=======================\n\n");
}