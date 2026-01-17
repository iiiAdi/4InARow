#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "Colors.h"

#define ROWS 6
#define COLS 7

// Game UI
void printBoard(int gameArr[][COLS], char*);
void printStats(int p1, int p2, int pc);

// Menu UI
void LoadMenu();
void printLogo();

// Utilities
void CleanConsole();