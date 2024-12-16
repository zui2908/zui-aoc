#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void part1(char* file_name);
void part2(char* file_name);
int parse1(char* input);
int parse2(char* input, int* enable);
int valid1(char* input);
int valid2(char* input);

int main(int argc, char** argv) {
	for (int i = 1; i < argc; i++) {
		printf("Input: %s\n", argv[i]);
		part1(argv[i]);
		part2(argv[i]);
	}
	return 0;
}

void part1(char* file_name) {
	FILE* fp;
	fp = fopen(file_name, "r");
	if (fp) {
		char input[13] = {0};
		char* end = input;
		int result = 0;
		while (fgets(end, sizeof(input) - abs(end - input), fp)) {
			if (!*input) {goto end;}
			result += parse1(input);
			end = input;
			while (*end) {end++;}
		}
		end:
		printf("Part 1 result: %d\n", result);
	} else {
		printf("No such file found\n");
	}
	fclose(fp);
}

void part2(char* file_name) {
	FILE* fp;
	fp = fopen(file_name, "r");
	if (fp) {
		char input[13] = {0};
		char* end = input;
		int result = 0;
		int enable = 1;
		while (fgets(end, sizeof(input) - abs(end - input), fp)) {
			if (!*input) {goto end;}
			result += parse2(input, &enable);
			end = input;
			while (*end) {end++;}
			printf("%d\n", result);
		}
		end:
		printf("Part 2 result: %d\n", result);
	} else {
		printf("No such file found\n");
	}
	fclose(fp);
}

int parse1(char* input) {
	char* start = input;
	int arg1 = 0, arg2 = 0;
	char end = 0;
	while (*start) {
		if (valid1(start)) {
			if (sscanf(start, "mul(%3d,%3d%c", &arg1, &arg2, &end) == 3 || end == ')') {
				start++;
				while (*start != 'm' && *start) {
					start++;
				}
				end = 0;
			} else {
				arg1 = 0;
				arg2 = 0;
			}
			break;
		}
		start++;
	}
	strcpy(input, start);
	return arg1 * arg2;
}

int valid1(char* input) {
	char f[] = "mul(#,#)";
	char* ip = input;
	char* fp = f;
	int dc = 0;
	check:
	while (*ip && *fp) {
		if (*fp == '#') {
			if (*ip >= '0' && *ip <= '9') {
				dc++;
				ip++;
			} else {
				if (dc) {
					dc = 0;
					fp++;
					goto check;
				} else {
					goto ret0;
				}
			}
			if (dc > 3) {
				goto ret0;
			}
		} else if (*fp == *ip) {
			if (*fp == ')') {
				goto ret1;
			} else {
				fp++;
				ip++;
			}
		} else {
			goto ret0;
		}
	}
	ret1:
	return 1;
	ret0:
	return 0;
}

int parse2(char* input, int* enable) {
	char* start = input;
	int arg1 = 0, arg2 = 0;
	char end = 0;
	while (*start) {
		switch (valid2(start)) {
			case 1: {
				if (*enable) {
					if (sscanf(start, "mul(%3d,%3d%c", &arg1, &arg2, &end) == 3 || end == ')') {
						end = 0;
					} else {
						arg1 = 0;
						arg2 = 0;
					}
				}
				do {
					start++;
				} while (*start && *start != 'm' && *start != 'd');
				goto ret;
			}
			break;
			case 2: {
				*enable = 1;
				end = 0;
				do {
					start++;
				} while (*start && *start != 'm' && *start != 'd');
				goto ret;
			}
			break;
			case 3: {
				*enable = 0;
				end = 0;
				do {
					start++;
				} while (*start && *start != 'm' && *start != 'd');
				goto ret;
			}
			break;
			case -1:
			case -2:
			case -3: {
				goto ret;
			}
			break;
			default: {
				start++;
			}
			break;
		}
	}
	ret:
	strcpy(input, start);
	return arg1 * arg2;
}

int valid2(char* input) {
	char f[][9] = {
		"mul(#,#)",
		"do()",
		"don't()"
	};
	char* ip;
	int dc, fi, fii;
	fi = 0;
	fii = 0;
	reset_check:
	ip = input;
	dc = 0;
	check:
	while (*ip && f[fi][fii]) {
		if (f[fi][fii] == '#') {
			if (*ip >= '0' && *ip <= '9') {
				dc++;
				ip++;
			} else {
				if (dc) {
					dc = 0;
					fii++;
					goto check;
				} else {
					return 0;
				}
			}
			if (dc > 3) {
				return 0;
			}
		} else if (f[fi][fii] == *ip) {
			if (f[fi][fii] == ')') {
				return fi + 1;
			} else {
				fii++;
				ip++;
			}
		} else {
			fi++;
			fii = 0;
			goto reset_check;
		}
	}
	return -1 * (fi + 1);
}