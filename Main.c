#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Controls.h"
#include "AI.h"
#include "Board.h"

int PlayerVsComputer() {
	int playerTurn = 1, Winner = 0, Selection, isValid;
	int gameArray[ROWS][COLS] = {0};
	int difficulty;

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
			printf("Press [Enter] to see statistics...");
			enterToContinue();
			return Winner;
		}

		playerTurn = (playerTurn == 1) ? 2 : 1;
	}
	return 0;
}



	int PlayerVsPlayer() {
		int playerTurn = 1, Winner = 0, Selection, isValid;
		int gameArray[ROWS][COLS] = { 0 };
		printBoard(gameArray, NULL);

		while (Winner == 0) {
			printf("Player %d's turn!\n", playerTurn);

			do {
				getInputInt(1, COLS, &Selection);

				isValid = PlaceDisc(gameArray, Selection - 1, playerTurn, &Winner);
				if (!isValid) printf("Invalid move, try again.\n");

			} while (isValid == 0);

			printBoard(gameArray, NULL);

			if (Winner != 0) {
				printf("\nPlayer %d Won!\n", Winner);
				printf("Press [Enter] to see statistics...");
				enterToContinue();
				return Winner;
			}
			playerTurn = (playerTurn == 1) ? 2 : 1;
		}
		return 0;
	}



void main() {
	int choice = 0, winsP1 = 0 , winsP2 = 0, winsPC = 0 ;
	int lastGameResult = 0;

	srand(time(NULL));

	do {
		CleanConsole();
		LoadMenu();

		// Get the choice
		getInputInt(1, 3, &choice);

		//If valid choice, get the thing:
		switch (choice) {
		case 1:
			lastGameResult = PlayerVsPlayer();	
			if (lastGameResult == 1) winsP1++;
			else if (lastGameResult == 2) winsP2++;
			CleanConsole(); 
			printf("\nGame Over! Here are the updated standings:\n");
			printStats(winsP1, winsP2, winsPC); 
			printf("\nPress [Enter] to return to the main menu...");
			getchar();
			break;

		case 2:
			lastGameResult = PlayerVsComputer();
			if (lastGameResult == 1) winsP1++;
			else if (lastGameResult == 2) winsPC++;
			CleanConsole();
			printf("\nGame Over! Here are the updated standings:\n");
			printStats(winsP1, winsP2, winsPC);
			printf("\nPress [Enter] to return to the main menu...");
			getchar();
			break;

		case 3:
			printf("Goodbye!\n");
			break;
		default:
			printf("Invalid choice.\n");
		}

	} while (choice != 3);
}