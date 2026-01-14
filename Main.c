#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "MainFunctions.h"
#include "Colors.h"

#define ROWS 6
#define COLS 7


void CleanConsole(){
	system("cls");
}

void LoadMenu() {
	printf("Welcome to 4 in A Row!\n");
	printf("1. PvP\n");
	printf("2. PvE\n");
	printf("3. Exit\n");
}

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

int countDirection(int gameArr[][COLS], int row, int col, int dRow, int dCol, int player) {
	int count = 0;
	int r = row + dRow;
	int c = col + dCol;

	while (r >= 0 && r < ROWS && c >= 0 && c < COLS && gameArr[r][c] == player) {
		count++;
		r += dRow;
		c += dCol;
	}
	return count;
}

// General Function to check if someone won
int checkWinner(int gameArr[][COLS], int Player, int rowNum, int colNum) {
	int count;

	// Horizontal Check
	count = 1 + countDirection(gameArr, rowNum, colNum, 0, -1, Player)
		+ countDirection(gameArr, rowNum, colNum, 0, 1, Player);
	if (count >= 4) return Player;

	// Vertial Check
	count = 1 + countDirection(gameArr, rowNum, colNum, 1, 0, Player);
	if (count >= 4) return Player;

	// Diagonal (\)
	count = 1 + countDirection(gameArr, rowNum, colNum, -1, -1, Player)
		+ countDirection(gameArr, rowNum, colNum, 1, 1, Player);
	if (count >= 4) return Player;
	
	// Diagonal (/)
	count = 1 + countDirection(gameArr, rowNum, colNum, 1, -1, Player)
		+ countDirection(gameArr, rowNum, colNum, -1, 1, Player);
	if (count >= 4) return Player;

	return 0;
}


int PlaceDisc(int gameArr[][COLS], int colNumber, int Player, int* Winner) {
	int i;
	if (colNumber < 0)
		return 0;
	for (i = ROWS; i > -1; i--) {
		if (gameArr[i][colNumber] == 0) {
			gameArr[i][colNumber] = Player;
			*Winner = checkWinner(gameArr, Player, i, colNumber);
			return 1;
		}
	}
	return 0;
}

void ResetBoard(int gameArr[][COLS]) {
	int i, j;
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {
			gameArr[i][j] = 0;
		}
	}
	printBoard(gameArr);
}

void PlayerVsPlayer() {
	int playerTurn = 1, Winner = 0, Selection, isValid;
	int gameArray[ROWS][COLS];
	ResetBoard(gameArray);

	while (Winner == 0) {
		printf("Player %d turn!\n", playerTurn);

		//Validate and get the input from the player.
		do {
			getInputInt(0, 7, &Selection);
			isValid = PlaceDisc(gameArray, Selection - 1, playerTurn, &Winner);
		} while (isValid == 0);
		


		printBoard(gameArray);
		// Check for winning possibility.
		if (Winner != 0) {
			break;
		}
	
		if (playerTurn == 2) {
			playerTurn -= 1;
		}else
			playerTurn++;
	}

	printf("Player %d, won!", Winner);
}



void main() {
	//LoadMenu();
	//LoadBoard();
	PlayerVsPlayer();

}