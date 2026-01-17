#include "Controls.h"
#include "AI.h"
//tells the compter where its disk gonna be in the array when choosing a place
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

int evaluatePosition(int gameArr[][COLS], int row, int col, int player) {
    int score = 0;

    // בדיקת כל 4 הכיוונים: אופקי, אנכי, ו-2 אלכסונים
    // בכל כיוון אנחנו בודקים: כמה יש לי שם?

    // אופקי (-)
    int count = scoreDirection(gameArr, row, col, 0, -1, player) + scoreDirection(gameArr, row, col, 0, 1, player);
    if (count >= 3) score += 1000000; // ניצחון!
    else if (count == 2) score += 100; // יש לי 3 בשורה (כולל הנוכחי)
    else if (count == 1) score += 10;  // יש לי 2 בשורה

    // אנכי (|)
    count = scoreDirection(gameArr, row, col, 1, 0, player); // בודקים רק למטה
    if (count >= 3) score += 1000000;
    else if (count == 2) score += 100;
    else if (count == 1) score += 10;

    // אלכסונים
    // ... (אותו עיקרון לאלכסונים, אפשר להוסיף אם רוצים דיוק מושלם)

    return score;
}


int getComputerMove(int gameArr[][COLS], int difficulty) {
    int col, row, i;

    if (difficulty == 3) {

        int bestCol = -1;
        long long maxScore = -1000000000;
        int col, row;

        int strategies[COLS] = { 0 }; // מערך לשמירת ציונים לכל עמודה

        for (col = 0; col < COLS; col++) {
            if (isColumnFull(gameArr, col)) {
                strategies[col] = -9999999; // אי אפשר לשים פה
                continue;
            }

            row = getNextOpenRow(gameArr, col);
            int currentScore = 0;

            if (col == 3) currentScore += 40;
            else if (col == 2 || col == 4) currentScore += 20;

            gameArr[row][col] = 2; 
            if (checkWinner(gameArr, 2, row, col) == 2) currentScore += 1000000; // ניצחון מיידי
            else {
                // בונוס על יצירת רצפים
                // כאן אפשר להשתמש בפונקציית העזר evaluatePosition שיצרנו למעלה
                // או פשוט לתת ניקוד בסיסי אם countDirection מחזיר 2 או 3
                if (countDirection(gameArr, row, col, 1, 0, 2) >= 2) currentScore += 50; // רצף אנכי
                // ... וכן הלאה
            }
            gameArr[row][col] = 0; // ניקוי

            // 3. כמה המהלך הזה דופק את היריב? (הגנה)
            gameArr[row][col] = 1; // נניח שהשחקן היה שם פה
            if (checkWinner(gameArr, 1, row, col) == 1) currentScore += 500000; // חסימת ניצחון מיידית!!
            else {
                // חסימת רצפים של היריב
                if (countDirection(gameArr, row, col, 0, 1, 1) + countDirection(gameArr, row, col, 0, -1, 1) >= 2)
                    currentScore += 300; // חסימת רצף של 3 מסוכן
            }
            gameArr[row][col] = 0; // ניקוי

            // --- התיקון הקריטי: בדיקת "מלכודת" (Bad Move) ---
            // האם אם אני שם פה דסקית, אני נותן ליריב לנצח ישר מעליי?
            if (row > 0) { // אם אני לא בשורה הכי עליונה
                gameArr[row - 1][col] = 1; // נניח שהיריב שם מעליי בתור הבא
                if (checkWinner(gameArr, 1, row - 1, col) == 1) {
                    currentScore -= 100000; // עונש ענק! אל תשים פה!
                }
                gameArr[row - 1][col] = 0;
            }

            strategies[col] = currentScore;
        }

        // בחירת העמודה עם הציון הכי גבוה
        for (col = 0; col < COLS; col++) {
            if (strategies[col] > maxScore) {
                maxScore = strategies[col];
                bestCol = col;
            }
        }

        return bestCol;
    }
    

    else if (difficulty == 2) {
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