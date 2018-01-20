#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include"my_play.h"
#include "start.h"
#include "print_board.h"

static void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}


static void up_push(int board[]) {
	for (int x = 0; x < width; ++x) {
		int build = 0;
		while (build < height) {
			if (board[build * width + x] == 0) {
				break;
			}
			else {
				++build;
			}
		}
		for (int trace = build; trace < height; ++trace) {
			int *tracing = &board[trace * width + x];
			int *building = &board[build * width + x];
			if ((*tracing != 0) && (*building == 0)) {
				swap(tracing, building);
				++build;
			}
		}
	}
}

static void w_up(int board[], int *point) {
	up_push(board);
	for (int x = 0; x < width; ++x) {
		for (int change = 0; change < height - 1;) {
			int *current = &board[change * width + x];
			int *next = &board[(change + 1) * width + x];
			if ((*current != 0) && (*current == *next)) {
				*current *= 2;
				*point += *current;
				*next = 0;
				change += 2;
			}
			else {
				change += 1;
			}
		}
	}
	up_push(board);
}

static void right_push(int board[]) {
	for (int y = 0; y < height; ++y) {
		int build = 3;
		while (build >= 0) {
			if (board[y * width + build] == 0) {
				break;
			}
			else {
				--build;
			}
		}
		for (int trace = build; trace >= 0; --trace) {
			int *tracing = &board[y * width + trace];
			int *building = &board[y * width + build];
			if ((*tracing != 0) && (*building == 0)) {
				swap(tracing, building);
				--build;
			}
		}
	}
}

static void d_right(int board[], int *point) {
	right_push(board);
	for (int y = 0; y < height; ++y) {
		for (int change = 3; change > 0;) {
			int *current = &board[y * width + change];
			int *next = &board[y * width + (change - 1)];
			if ((*current != 0) && (*current == *next)) {
				*current *= 2;
				*point += *current;
				*next = 0;
				change -= 2;
			}
			else {
				change -= 1;
			}
		}
	}
	right_push(board);
}


static void down_push(int board[]) {
	for (int x = 0; x < width; ++x) {
		int build = 3;
		while (build >= 0) {
			if (board[build * width + x] == 0) {
				break;
			}
			else {
				--build;
			}
		}
		for (int trace = build; trace >= 0; --trace) {
			int *tracing = &board[trace * width + x];
			int *building = &board[build * width + x];
			if ((*tracing != 0) && (*building == 0)) {
				swap(tracing, building);
				--build;
			}
		}
	}
}

static void s_down(int board[], int *point) {
	down_push(board);
	for (int x = 0; x < width; ++x) {
		for (int change = height - 1; change > 0;) {
			int *current = &board[change * width + x];
			int *next = &board[(change - 1) * width + x];
			if ((*current != 0) && (*current == *next)) {
				*current *= 2;
				*point += *current;
				*next = 0;
				change -= 2;
			}
			else {
				change -= 1;
			}
		}
	}
	down_push(board);
}


static void left_push(int board[]) {
	for (int y = 0; y < height; ++y) {
		int build = 0;
		while (build < width) {
			if (board[y * width + build] == 0) {
				break;
			}
			else {
				++build;
			}
		}
		for (int trace = build; trace < width; ++trace) {
			int *tracing = &board[y * width + trace];
			int *building = &board[y * width + build];
			if ((*tracing != 0) && (*building == 0)) {
				swap(tracing, building);
				++build;
			}
		}
	}
}

static void a_left(int board[], int *point) {
	left_push(board);
	for (int y = 0; y < height; ++y) {
		for (int change = 0; change < width - 1;) {
			int *current = &board[y * width + change];
			int *next = &board[y * width + (change + 1)];
			if ((*current != 0) && (*current == *next)) {
				*current *= 2;
				*point += *current;
				*next = 0;
				change += 2;
			}
			else {
				change += 1;
			}
		}
	}
	left_push(board);
}



static int count_free(int board[]) {
	int num_free = 0;
	for (int i = 0; i < height * width; ++i) {
		if (board[i] == 0) {
			++num_free;
		}
	}
	return num_free;
}

static void put_new(int value, int pos) {
	for (int i = 0; i < height * width; ++i) {
		if (board[i] != 0) {
			continue;
		}
		else {
			if (pos) {
				--pos;
			}
			else {
				board[i] = value;
				break;
			}
		}
	}
}


static bool check_lose(int board[]) {
	if (count_free(board) != 0) {
		return false;
	}
	else {
		bool check = true;
		int len = height * width;
		int *temp = malloc(len * sizeof(int));
		int temp_point = 0;
		for (int i = 0; i < len; ++i) {
			temp[i] = board[i];
		}
		w_up(temp, &temp_point);
		//printf("move up\n");
		if (temp_point != 0) {
			//printf("move up no problem\n");
			check = false;
		}
		else {
			d_right(temp, &temp_point);
			//printf("move right\n");
			if (temp_point) {
				//printf("move right no problem\n");
				check = false;
			}
			else {
				//printf("lost\n");
				check = true;
			}
		}
		free(temp);
		return check;
	}
}

static bool check_identical(int a[], int b[]) {
	for (int i = 0; i < 16; ++i) {
		if (a[i] != b[i]) {
			return false;
		}
	}
	return true;
}

static int *copy_board(int board[]) {
	int len = height * width;
	int *new = malloc(len * sizeof(int));
	for (int i = 0; i < len; ++i) {
		new[i] = board[i];
	}
	return new;
}



void m_play(void) {
	char cmd = '\0';
	while (1) {
		if (check_lose(board)) {
			printf("Game Over!\n\n");
			break;
		}
		int k = scanf_s(" %c", &cmd);
		if (k == 1) {
			if ((cmd == 'w') || (cmd == 'W')) {
				system("cls");
				int *copied = copy_board(board);
				w_up(board, &point);
				if (check_identical(copied, board)) {
					print_board(board);
					instruction();
					free(copied);
					continue;
				}
				else {
					free(copied);
				}
			}
			else if ((cmd == 'd') || (cmd == 'D')){
				system("cls");
				int *copied = copy_board(board);
				d_right(board, &point);
				if (check_identical(copied, board)) {
					print_board(board);
					instruction();
					free(copied);
					continue;
				}
				else {
					free(copied);
				}
			}
			else if ((cmd == 's') || (cmd == 'S')) {
				system("cls");
				int *copied = copy_board(board);
				s_down(board, &point);
				if (check_identical(copied, board)) {
					print_board(board);
					instruction();
					free(copied);
					continue;
				}
				else {
					free(copied);
				}
			}
			else if ((cmd == 'a') || (cmd == 'A')) {
				system("cls");
				int *copied = copy_board(board);
				a_left(board, &point);
				if (check_identical(copied, board)) {
					print_board(board);
					instruction();
					free(copied);
					continue;
				}
				else {
					free(copied);
				}
			}
			else {
				printf("Invalid command. Please re-enter.\n\n");
				continue;
			}
			int available = count_free(board);
			srand(time(NULL));
			int new_pos = rand() % available;
			int new_value = (rand() % 2) * 2 + 2;
			put_new(new_value, new_pos);
			print_board(board);
			instruction();
		}
		else {
			printf("Invalid command. Please re-enter.\n\n");
		}
	}
}



