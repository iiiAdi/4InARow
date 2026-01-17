#pragma once

//Imports
#include <time.h>
#include <stdlib.h>

// AI Functions
int getNextOpenRow(int gameArr[][COLS], int);
int getComputerMove(int gameArr[][COLS], int);