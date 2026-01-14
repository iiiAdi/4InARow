#define _CRT_SECURE_NO_WARNINGS

// Main Imports
#include <stdio.h>
#include <stdlib.h>

// Self Imports
#include "MainFunctions.h"
#include "Colors.h"

void getInputInt(int min, int max, int* address) {
	int result;
	do {
		printf("Please enter your selection:\n");
		result = scanf("%d", address);
	} while (*address < min || *address > max);
}

void CleanConsole() {
	system("cls");
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