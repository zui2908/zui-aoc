#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void part1(char* file_name);
void part2(char* file_name);
int parse(char* input);
int parse_2(char* input);
int valid(char* input);

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
			// printf("Before: %s\n", input);
			if (!*input) {goto end;}
			result += parse(input);
			end = input;
			while (*end) {end++;}
			printf("%d\n", result);
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
		while (fgets(end, sizeof(input) - abs(end - input), fp)) {
			// printf("Before: %s\n", input);
			if (!*input) {goto end;}
			result += parse_2(input);
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

int parse(char* input) {
	char* start = input;
	int arg1 = 0, arg2 = 0;
	char end = 0;
	while (*start) {
		if (valid(start)) {
			if (sscanf(start, "mul(%3d,%3d%c", &arg1, &arg2, &end) == 3 || end == ')') {
				printf("%s | %d\n", start, arg1 * arg2);
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

int valid(char* input) {
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

int valid_dodont(char* input) {
	char d[] = "do()";
	char dn[] = "don't()";
}

int parse_2(char* input) {
	char* start = input;
	int arg1 = 0, arg2 = 0;
	char end = 0;
	int parse = 1;
	while (*start) {
		printf("%s\n", start);
		if (parse) {
			if (valid(start)) {
				if (sscanf(start, "mul(%3d,%3d%c", &arg1, &arg2, &end) == 3 || end == ')') {
					printf("%s | %d\n", start, arg1 * arg2);
					start++;
					while (*start != 'm' && *start != 'd' && *start) {
						start++;
					}
					end = 0;
				} else {
					arg1 = 0;
					arg2 = 0;
				}
				break;
			}
			if (sscanf(start, "don't(%c", &end) && end == ')') {
				parse = 0;
				end = 0;
			}
		} else {
			if (sscanf(start, "do(%c", &end) && end == ')') {
				parse = 1;
				end = 0;
			}
		}
		start++;
	}
	strcpy(input, start);
	return arg1 * arg2;
}