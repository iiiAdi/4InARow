#define _CRT_SECURE_NO_WARNINGS

// Main Imports
#include <stdio.h>
#include <stdlib.h>

// Imports
#include "Controls.h"

void getInputInt(int min, int max, int* address) {
	int result;
	do {
		printf("Please enter your selection:\n");
		result = scanf("%d", address);
	} while (*address < min || *address > max);
}

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

	for (i = ROWS; i > -1; i--) {
		if (gameArr[i][colNumber] == 0) {
			gameArr[i][colNumber] = Player;
			*Winner = checkWinner(gameArr, Player, i, colNumber);
			return 1;
		}
	}
}



