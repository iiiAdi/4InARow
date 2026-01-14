//Imports
#include "Board.h"
#include "Colors.h"



// Clearing the console after a round
void CleanConsole() {
	system("cls");
}


// Resets the board
//void ResetBoard(int gameArr[][COLS]) {
//	int i, j;
//	for (i = 0; i < ROWS; i++) {
//		for (j = 0; j < COLS; j++) {
//			gameArr[i][j] = 0;
//		}
//	}
//	printBoard(gameArr);
//}


// Prints the current state of the game
void printBoard(int gameArr[][COLS]) {
	CleanConsole();
	int i, j, numberInPos;

	// Prints the current game Matrix!
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {
			numberInPos = gameArr[i][j];
			if (numberInPos > 0) {
				if (numberInPos == 1) {
					printf(YELLOW);
				}
				else
					printf(RED);

				printf("%2c" RESET, 'O');
				continue;
			}
			printf("%2c", 'X');
		}
		printf("\n");
	}

	// Prints the game Numbers:

	for (i = 0; i < COLS * 2; i++) {
		printf("-");
	}

	printf("\n");
	for (i = 0; i < COLS; i++) {
		printf("%2d", i + 1);
	}
	printf("\n");
}