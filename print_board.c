#include <stdio.h>
#include <assert.h>
#include "start.h"

void print_board(int board[]) {
	printf("point: %d\n", point);
	printf("\n\n\n");
	for (int y = 0; y < height; ++y) {
		printf("      ");
		for (int x = 0; x < width; ++x) {
			int value = board[y * width + x];
			if (value < 10) {
				printf("%d     ", value);
			}
			else if (value < 100) {
				printf("%d    ", value);
			}
			else if (value < 1000) {
				printf("%d   ", value);
			}
			else if (value < 10000) {
				printf("%d  ", value);
			}
			else if (value < 100000) {
				printf("%d ", value);
			}
			else {
				printf("%d", value);
			}
			if ((x + 1) % 4) {
				printf("   ");
			}
			else {
				printf("\n\n\n\n");
			}
		}
	}
}
