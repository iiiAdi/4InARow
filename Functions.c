#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "MainFunctions.h"
#include <stdlib.h>

void getInputInt(int min, int max, int* address) {
	int result;
	do {
		printf("Please enter your selection:\n");
		result = scanf("%d", address);
	} while (*address < min || *address > max);
}

int* createMatrix(int ROW, int COL) {
	
}