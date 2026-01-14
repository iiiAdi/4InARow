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






void PlayerVsPlayer() {
	int playerTurn = 1, Winner = 0, Selection, isValid;
	int gameArray[ROWS][COLS] = {0};
	//ResetBoard(gameArray);
	printBoard(gameArray);

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