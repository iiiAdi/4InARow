#pragma once
#include <stdio.h>

// Defintion of Rows and Coloumns
#define ROWS 6
#define COLS 7

// Main User Functions
void getInputInt(int, int, int*);
void enterToContinue();


// Game Mechanics
int isColumnFull(int gameArr[][COLS], int);
int PlaceDisc(int gameArr[][COLS], int, int, int*);

// Game-Board Main Functions
