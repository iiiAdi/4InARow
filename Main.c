#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include "Controls.h"
#include "AI.h"
#include "Board.h"


void LoadMenu() {
	printf("Welcome to 4 in A Row!\n");
	printf("1. PvP\n");
	printf("2. PvE\n");
	printf("3. Exit\n");
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


void PlayerVsComputer() {
	int playerTurn = 1, Winner = 0, Selection, isValid;
	int gameArray[ROWS][COLS] = {0};
	int difficulty;

	// בחירת רמת קושי
	printf("Select Difficulty:\n1. Easy\n2. Medium\n");
	getInputInt(1, 2, &difficulty);

	char msg[100] = "Game Started Good luck! :3";
	printBoard(gameArray, msg);


	while (Winner == 0) {
		if (playerTurn == 1) {
			do {
				getInputInt(1, COLS, &Selection);
				isValid = PlaceDisc(gameArray, Selection - 1, playerTurn, &Winner);
				if (!isValid) printf("Invalid move, try again.\n");
			} while (isValid == 0);
		}
		else {
			Selection = getComputerMove(gameArray, difficulty);
			PlaceDisc(gameArray, Selection, playerTurn, &Winner);
			sprintf(msg, "Computer chose column %d. Your Turn!", Selection + 1);
		}

		printBoard(gameArray, msg);

		if (Winner != 0) {
			if (Winner == 1) printf("You Won!\n");
			else printf("Computer Won!\n");


			printf("\nPress Enter to return to main menu...");
			enterToContinue();
			break;
		}

		playerTurn = (playerTurn == 1) ? 2 : 1;
	}
}


void PlayerVsPlayer() {
	int playerTurn = 1, Winner = 0, Selection, isValid;
	int gameArray[ROWS][COLS] = {0};
	//ResetBoard(gameArray);
	printBoard(gameArray, NULL);

	while (Winner == 0) {
		printf("Player %d turn!\n", playerTurn);

		//Validate and get the input from the player.
		do {
			getInputInt(0, 7, &Selection);
			isValid = PlaceDisc(gameArray, Selection - 1, playerTurn, &Winner);
		} while (isValid == 0);

		printBoard(gameArray, NULL);
		// Check for winning possibility.
		if (Winner != 0) {
			break;
		}
	
		playerTurn = (playerTurn == 1) ? 2 : 1;
	}

	printf("Player %d, won!\nPress [Enter] to return to the menu.", Winner);
	enterToContinue();

}



void main() {
	int choice = 0;

	srand(time(NULL));

	do {
		CleanConsole();
		LoadMenu();

		// Get the choice
		getInputInt(1, 3, &choice);

		//If valid choice, get the thing:
		switch (choice) {
		case 1:
			PlayerVsPlayer();
			break;
		case 2:
			PlayerVsComputer();
			break;
		case 3:
			printf("Goodbye!\n");
			break;
		default:
			printf("Invalid choice.\n");
		}

	} while (choice != 3);
}