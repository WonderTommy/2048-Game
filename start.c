#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "instruction.h"
#include "print_board.h"
#include "start.h"
#include "my_play.h"


int width = 4;
int height = 4;
int board[16];
int x = 0;
int y = 0;
int num = 0;
int point = 0;


void my_start(void) {
	point = 0;
	int length = width * height;
	for (int i = 0; i < length; ++i) {
		board[i] = 0;
	}
	int start_times = 2;
	srand(time(NULL));
	while (start_times > 0) {
		x = rand() % width;
		y = rand() % height;
		++x;
		++y;
		if (board[(y - 1) * width + (x - 1)] == 0) {
			num = rand();
			if (num % 2) {
				num = 4;
			}
			else {
				num = 2;
			}
			board[(y - 1) * width + (x - 1)] = num;
			--start_times;
		}
	}
	print_board(board);
	instruction();
	m_play();
	printf("Do you want to start a new game?\n  Yes(y)\n  No(n)\n\n");
	while (1) {
		char choice = '\0';
		int k = scanf_s(" %c", &choice);
		if (k == 1) {
			if ((choice == 'y') || (choice == 'Y')) {
				system("cls");
				my_start();
			}
			else {
				printf("The program is stopped\n\n");
				exit(EXIT_SUCCESS);
			}
			break;
		}
		else {
			printf("Invalid choice. Please re-enter\n\n");
		}
	}
	/*for (int i = 0; i < 16; ++i) {
		printf("%d ", board[i]);
		if (!((i + 1) % 4)) {
			printf("\n");
		}
	}*/
}


