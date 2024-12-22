#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void part1(char* file_name);
void part2(char* file_name);
void insert(int hashtable[100][100], int index, int value);
void search(int hashtable[100][100], int index, int value);

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
	char input[70];
	int record[23] = {0};
	int result = 0;
	int n = 0, r_i = 0, i_i = 0;
	int index = 0, value = 0;
	int hash_tbl[100][100] = {0};
	while (fgets(input, 70, fp)) {
		if (strchr(input, '|')) {
			if (sscanf(input, "%d|%d", &index, &value) == 2) {
				hash_tbl[index][value] = 1;
			} else {
				printf("Error scanning line");
			}
		} else {
			while (sscanf(&input[i_i], "%d%n", &record[r_i], &n) == 1) {
				r_i++;
				i_i += n + 1;
			}
			for (int i = 0; i < r_i - 1; i++) {
				for (int j = i + 1; j < r_i; j++) {
					if (!hash_tbl[record[i]][record[j]]) {
						goto br;
					}
				}
			}
			if (r_i != 0) { 
				result += record[r_i / 2];
			}
			br:
			r_i = 0;
			i_i = 0;
		}
	}
	printf("Part 1 result: %d\n", result);
	fclose(fp);
}

void part2(char* file_name) {
	FILE* fp = fopen(file_name, "r");
	if (!fp) {printf("No such file found\n");return;}
	char input[70];
	int record[23] = {0};
	int result = 0;
	int n = 0, r_i = 0, i_i = 0;
	int index = 0, value = 0;
	int hash_tbl[100][100] = {0};
	while (fgets(input, 70, fp)) {
		if (strchr(input, '|')) {
			if (sscanf(input, "%d|%d", &index, &value) == 2) {
				hash_tbl[index][value] = 1;
			} else {
				printf("Error scanning line");
			}
		} else {
			while (sscanf(&input[i_i], "%d%n", &record[r_i], &n) == 1) {
				r_i++;
				i_i += n + 1;
			}
			int temp, x = 0;
			for (int i = 0; i < r_i - 1; i++) {
				for (int j = i + 1; j < r_i; j++) {
					if (hash_tbl[record[j]][record[i]]) {
						temp = record[j];
						record[j] = record[i];
						record[i] = temp;
						x++;
					}
				}
			}
			if (r_i != 0 && x > 0) { 
				result += record[r_i / 2];
			}
			r_i = 0;
			i_i = 0;
		}
	}
	printf("Part 2 result: %d\n", result);
	fclose(fp);
}
