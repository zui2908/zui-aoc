#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void part1(char* file_name);
void part2(char* file_name);
int count1(char* input,  int cols, int rows);
int count2(char* input,  int cols, int rows);

int main(int argc, char** argv) {
	for (int i = 1; i < argc; i++) {
		printf("input: %s\n", argv[i]);
		part1(argv[i]);
		part2(argv[i]);
	}
	return 0;
}

void part1(char* file_name) {
	FILE* fp = fopen(file_name, "r");
	if (!fp) {printf("No such file found\n");return;}
	fseek(fp, 0l, SEEK_END);
	long fsize = ftell(fp);
	fseek(fp, 0l, SEEK_SET);
	char * input = malloc(fsize + 1);
	if (!input) {printf("Malloc failed\n"); return;}
	fread(input, sizeof(char), fsize, fp);
	char * ptr = input;
	while (*ptr != '\n') {ptr++;}
	int cols = ptr - input + 1;
	int rows = fsize / cols;
	input[fsize] = 0;
	int result = count1(input,  cols, rows);
	printf("Part 1 result: %d\n", result);
	free(input);
	fclose(fp);
}

void part2(char* file_name) {
	FILE* fp = fopen(file_name, "r");
	if (!fp) {printf("No such file found\n");return;}
	fseek(fp, 0l, SEEK_END);
	long fsize = ftell(fp);
	fseek(fp, 0l, SEEK_SET);
	char * input = malloc(fsize + 1);
	if (!input) {printf("Malloc failed\n"); return;}
	fread(input, sizeof(char), fsize, fp);
	char * ptr = input;
	while (*ptr != '\n') {ptr++;}
	int cols = ptr - input + 1;
	int rows = fsize / cols;
	input[fsize] = 0;
	int result = count2(input,  cols, rows);
	printf("Part 2 result: %d\n", result);
	free(input);
	fclose(fp);
}

int count1(char* input, int cols, int rows) {
	char f[] = "XMAS";
	char * ptr = f;
	int ret = 0;
	for (long y = 0; y < rows; y++) {
		for (long x = 0; x < cols; x++) {
			if (input[y * cols + x] != *ptr) {continue;}
			for (int dx = -1; dx < 2; dx++) {
				for (int dy = -1; dy < 2; dy++) {
					if (dx == 0 && dy ==0) {continue;}
					long x2 = x;
					long y2 = y;
					while (x2 < cols  && y2 < rows && x2 >= 0 && y2 >= 0 && input[y2 * cols + x2] == *ptr) {
						x2 += dx;
						y2 += dy;
						ptr++;
					}
					if (*ptr == 0) {
						ret++;
					}
					ptr = f;
				}
			}
		}
	}
	return ret;
}

int count2(char* input,  int cols, int rows) {
	int ret = 0;
	for (long y = 1; y < rows - 1; y++) {
		for (long x = 1; x < cols - 2; x++) {
			if (input[y * cols + x] != 'A') {continue;}
			if (
				(input[(y + 1) * cols + (x + 1)] + input[(y - 1) * cols + (x - 1)] == 'M' + 'S') &&
				(input[(y + 1) * cols + (x - 1)] + input[(y - 1) * cols + (x + 1)] == 'M' + 'S')
			) {
				ret++;
			}
		}
	}
	return ret;
}

