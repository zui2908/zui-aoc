#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void sort(int64_t* l);
void part1(char* file_name);
void part2(char* file_name);
int sign(int x);
int safe1(int levels[10], int count);
int safe2(int levels[10], int count);

int main(int argc, char** argv) {
	for (int i = 1; i < argc; i++) {
		printf("Input: %s\n", argv[i]);
		part1(argv[i]);
		part2(argv[i]);
	}
	return 0;
}

void part1(char* file_name) {
	FILE* fp = fopen(file_name, "r");
	if (!fp) {printf("Error opening file\n");return;}
	char input[120] = {0};
	int levels[10] = {0};
	int result;
	result = 0;
	while (fgets(input, sizeof input, fp)) {
		if (strlen(input) < 3) {break;}
		int count = sscanf(input, "%d%d%d%d%d%d%d%d%d%d", &levels[0], &levels[1], &levels[2], &levels[3], &levels[4], &levels[5], &levels[6], &levels[7], &levels[8], &levels[9]);
		result += safe1(levels, count);
	}
	printf("Part 1 result: %d\n", result);
	fclose(fp);
}

void part2(char* file_name) {
	FILE* fp = fopen(file_name, "r");
	if (!fp) {printf("Error opening file\n");return;}
	char input[120] = {0};
	int levels[10] = {0};
	int result;
	result = 0;
	while (fgets(input, sizeof input, fp)) {
		if (strlen(input) < 3) {break;}
		int count = sscanf(input, "%d%d%d%d%d%d%d%d%d%d", &levels[0], &levels[1], &levels[2], &levels[3], &levels[4], &levels[5], &levels[6], &levels[7], &levels[8], &levels[9]);
		result += safe2(levels, count);
	}
	printf("Part 2 result: %d\n", result);
	fclose(fp);
}

int sign(int x) {
    return (x > 0) - (x < 0);
}

int safe1(int levels[10], int count) {
	int s = 0;
	for (int i = 0; i < count; i++) {
		if (i == count - 1) {continue;}
		int diff = levels[i + 1] - levels[i];
		if (abs(diff) > 3 || abs(diff) < 1) {goto zero;}
		if (s) {
			if (sign(diff) ^ sign(s)) {goto zero;}
		} else {
			s = sign(diff);
		}
	}
	return 1;
	zero:
	return 0;
}

int safe2(int levels[10], int count) {
	int l[count - 1];
	for (int i = 0; i < count; i++) {
		for (int j = 0, k = 0; j < count; j++) {
			if (i == j) {continue;}
			l[k] = levels[j];
			k++;
		}
		if (safe1(l, count - 1)) {
			return 1;
		}
	}
	return 0;
}
