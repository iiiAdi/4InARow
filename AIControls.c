// Imports
#include "Controls.h"
#include "AI.h"
#include "Controls.h"

// tells the compter where its disk gonna be in the array when choosing a place
int getNextOpenRow(int gameArr[][COLS], int col) {
    for (int i = ROWS - 1; i >= 0; i--) {
        if (gameArr[i][col] == 0) return i;
    }
    return -1;
}

int scoreDirection(int gameArr[][COLS], int row, int col, int dRow, int dCol, int player) {
    int count = 0;
    // בודקים 3 צעדים קדימה לכיוון הזה
    for (int i = 1; i < 4; i++) {
        int r = row + dRow * i;
        int c = col + dCol * i;

        if (r < 0 || r >= ROWS || c < 0 || c >= COLS) break; // יצאנו מהלוח

        if (gameArr[r][c] == player) {
            count++; // מצאנו דיסקית שלנו
        }
        else if (gameArr[r][c] == 0) {
            // משבצת ריקה זה בסדר (זה פוטנציאל), אבל לא מעלה ניקוד ישיר כרגע
            // אפשר לתת חצי נקודה אם רוצים
        }
        else {
            break; // נתקענו בדיסקית של היריב - הכיוון הזה חסום
        }
    }
    return count;
}


// Checks all directions for scoring.
int evaluatePosition(int gameArr[][COLS], int row, int col, int player) {
    int score = 0;

    // Horizontal 
    int count = scoreDirection(gameArr, row, col, 0, -1, player) + scoreDirection(gameArr, row, col, 0, 1, player);
    if (count >= 3) score += 1000000;
    else if (count == 2) score += 100;
    else if (count == 1) score += 10;

    // Vertical
    count = scoreDirection(gameArr, row, col, 1, 0, player);
    if (count >= 3) score += 1000000;
    else if (count == 2) score += 100;
    else if (count == 1) score += 10;

    // Diagonal 1
    count = scoreDirection(gameArr, row, col, -1, -1, player) + scoreDirection(gameArr, row, col, 1, 1, player);
    if (count >= 3) score += 1000000;
    else if (count == 2) score += 100;
    else if (count == 1) score += 10;

    // Diagonal 2
    count = scoreDirection(gameArr, row, col, 1, -1, player) + scoreDirection(gameArr, row, col, -1, 1, player);
    if (count >= 3) score += 1000000;
    else if (count == 2) score += 100;
    else if (count == 1) score += 10;

    return score;
}

// Get the current computer move based on the difficulty.
int getComputerMove(int gameArr[][COLS], int difficulty) {
    int col, row, i;

    if (difficulty == 3) {
        int bestCol = -1;
        long long maxScore = -1000000000; 
        int strategies[COLS] = { 0 };

        for (col = 0; col < COLS; col++) {
            if (isColumnFull(gameArr, col)) {
                strategies[col] = -9999999;
                continue;
            }

            row = getNextOpenRow(gameArr, col);
            int currentScore = 0;

            if (col == 3) currentScore += 40;
            else if (col == 2 || col == 4) currentScore += 20;

            gameArr[row][col] = 2;
            currentScore += evaluatePosition(gameArr, row, col, 2);
            gameArr[row][col] = 0; 

            gameArr[row][col] = 1; 
            int enemyScore = evaluatePosition(gameArr, row, col, 1);

            if (enemyScore >= 1000000) currentScore += 500000;
            else {
                currentScore += (enemyScore / 2);
            }
            gameArr[row][col] = 0; 

           
            if (row > 0) {
                gameArr[row - 1][col] = 1; 
                if (checkWinner(gameArr, 1, row - 1, col) == 1) {
                    currentScore -= 2000000; 
                }
                gameArr[row - 1][col] = 0;
            }

            strategies[col] = currentScore;
        }
        for (col = 0; col < COLS; col++) {
            if (strategies[col] > maxScore) {
                maxScore = strategies[col];
                bestCol = col;
            }
        }
        return bestCol;
    }

    else if (difficulty == 2) {
      //checks if the computer can win by the next move and if its true executes the move
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
        //checks if it has to defend against the other player to prevent a lose 
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

