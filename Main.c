#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Controls.h"
#include "AI.h"
#include "Board.h"

int PlayerVsComputer() {
	int playerTurn = 1, Winner = 0, Selection, isValid;
	int gameArray[ROWS][COLS] = {0};
	int difficulty;
	printLogo();

	printf(CYAN"=== Select Difficulty ===\n"RESET);
	printf("\n[1] Easy\n[2] Medium\n[3] Hard\n[4] Back\n");

	getInputInt(1,4, &difficulty);	

	if (difficulty == 4) {
		return 4;
	}

	char msg[100] = "Game Started Good luck! :3";
	printBoard(gameArray, msg);


	while (Winner == 0) {
		if (playerTurn == 1) {
			do {
				getInputInt(1, COLS, &Selection);
				isValid = PlaceDisc(gameArray, Selection - 1, playerTurn, &Winner);
				if (!isValid) printf(RED "Invalid move, try again.\n");
			} while (isValid == 0);
		}
		else {
			Selection = getComputerMove(gameArray, difficulty);
			PlaceDisc(gameArray, Selection, playerTurn, &Winner);
			sprintf(msg, "Computer chose column %d. Your Turn!", Selection + 1);
		}

		printBoard(gameArray, msg);

		if (Winner != 0) {
			if (Winner == 1) printf(YELLOW "You Won!\n" RESET);
			else printf(RED "Computer Won!\n" RESET);
			printf("Press [Enter] to see statistics...");
			enterToContinue();
			return Winner;
		}

		if (checkDraw(gameArray)) {
			printf(YELLOW "\n It's a Draw! No one won.\n" RESET);
			printf("Press [Enter] to return to menu...");
			enterToContinue();
			return 3; 
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
				printf(CYAN"\nPlayer %d Won!\n" RESET, Winner);
				printf("Press [Enter] to see statistics...");
				enterToContinue();
				return Winner;
			}

			if (checkDraw(gameArray)) {
				printf(YELLOW "\n It's a Draw! No one won.\n" RESET);
				printf("Press [Enter] to return to menu...");
				enterToContinue();
				return 3; 
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
		printLogo();
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
			enterToContinue();
			break;

		case 2:
			lastGameResult = PlayerVsComputer();
			if (lastGameResult == 1) winsP1++;
			else if (lastGameResult == 2) winsPC++;
			else if (lastGameResult == 4) break;
			CleanConsole();
			printf("\nGame Over! Here are the updated standings:\n");
			printStats(winsP1, winsP2, winsPC);
			printf("\nPress [Enter] to return to the main menu...");
			enterToContinue();
			break;

		case 3:
			printf("Goodbye!\n");
			break;
		default:
			printf("Invalid choice.\n");
		}

	} while (choice != 3);
}