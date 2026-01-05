#pragma once
#include <stdio.h>

void getInputInt(int min, int max, int* address) {
	int result;
	do {
		printf("Please enter your selection:\n");
		result = scanf("%d", address);
	} while (*address < min || *address > max);
}