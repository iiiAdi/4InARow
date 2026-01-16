#include "Controls.h"
#include "AI.h"
//tells the compter where its disk gonna be in the array when choosing a place
int getNextOpenRow(int gameArr[][COLS], int col) {
    for (int i = ROWS - 1; i >= 0; i--) {
        if (gameArr[i][col] == 0) return i;
    }
    return -1;
}

int getComputerMove(int gameArr[][COLS], int difficulty) {
    int col, row, i;

    if (difficulty == 2) {
      //checks if the computer can win by the next move and its its true executes the move
        for (i = 0; i < COLS; i++) {
            if (isColumnFull(gameArr, i)) continue; 

            row = getNextOpenRow(gameArr, i);
            gameArr[row][i] = 2; 
            if (checkWinner(gameArr, 2, row, i) == 2) {
                gameArr[row][i] = 0; 
                return i; 
            }
            gameArr[row][i] = 0;
        }
        //checks if it has to deffend against the other player to prevent a lose 
        for (i = 0; i < COLS; i++) {
            if (isColumnFull(gameArr, i)) continue;

            row = getNextOpenRow(gameArr, i);
            gameArr[row][i] = 1;
            if (checkWinner(gameArr, 1, row, i) == 1) {
                gameArr[row][i] = 0;
                return i;
            }
            gameArr[row][i] = 0;
        }
    }

    do {
        col = rand() % COLS;
    } while (isColumnFull(gameArr, col));

    return col;
}