#pragma once
#include <stdio.h>

// Defintion of Rows and Coloumns
#define ROWS 6
#define COLS 7

// Main User Functions
void getInputInt(int, int, int*);


// Game-Board Main Functions
void ResetBoard(int gameArr[][COLS]);
void printBoard(int gameArr[][COLS]);