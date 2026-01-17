#define _CRT_SECURE_NO_WARNINGS

// Main Imports
#include <stdio.h>
#include <stdlib.h>

// Imports
#include "Controls.h"

// a function that makes sure the user's input is within a certain range
void getInputInt(int min, int max, int* address) {
	int result;
	do {
		printf("Please enter your selection:\n");
		result = scanf("%d", address);
		while (getchar() != '\n');
	} while (*address < min || *address > max);
}

void enterToContinue() {
	getchar();
}
//checks the column[0] to see if it's full
int isColumnFull(int gameArr[][COLS], int colNumber) {
	return gameArr[0][colNumber] != 0;
}

int PlaceDisc(int gameArr[][COLS], int colNumber, int Player, int* Winner) {
	int i, isFull;
	if (colNumber < 0)
		return 0;

	isFull = isColumnFull(gameArr, colNumber);
	if (isFull)
		return 0;

	for (i = ROWS-1 ; i > -1; i--) {
		if (gameArr[i][colNumber] == 0) {
			gameArr[i][colNumber] = Player;
			*Winner = checkWinner(gameArr, Player, i, colNumber);
			return 1;
		}
	}
}

//function that checks if a player won after a move
int countDirection(int gameArr[][COLS], int row, int col, int dRow, int dCol, int player) {
	int count = 0;
	int r = row + dRow;
	int c = col + dCol;

	// the while loop makes sure we stay within the bounds of the array and not searching outside of it
	while (r >= 0 && r < ROWS && c >= 0 && c < COLS && gameArr[r][c] == player) {
		count++;
		r += dRow;
		c += dCol;
	}
	return count;
}

int checkDraw(int gameArr[][COLS]) {
	for (int i = 0; i < COLS; i++) {
		if (gameArr[0][i] == 0) {
			return 0; // מצאנו מקום פנוי בשורה העליונה -> המשחק ממשיך
		}
	}
	return 1; // השורה העליונה מלאה לגמרי -> תיקו
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


