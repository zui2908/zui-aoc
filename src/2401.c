#include <stdio.h>
#include <stdint.h>
#include <math.h>

void sort(int64_t* l);
void part1(char* file_name);
void part2(char* file_name);

int main(int argc, char** argv) {
	for (int i = 1; i < argc; i++) {
		printf("Input: %s\n", argv[i]);
		part1(argv[i]);
		part2(argv[i]);
	}
	return 0;
}

void sort(int64_t* l) {
	int64_t* ptr1 = &l[1022];
	int64_t* ptr2 = &l[1023];
	int64_t temp;
	for (int i = 1022; i > -1; i--) {
		if (*ptr1 < *ptr2) {
			temp = *ptr1;
			*ptr1 = *ptr2;
			*ptr2 = temp;
			ptr1--;
			ptr2--;
		} else {
			break;
		}
	}
}

void part1(char* file_name) {
	FILE* fp;
	char input[120];
	int64_t d = 0;
	int64_t l1[1024] = {0};
	int64_t l2[1024] = {0};
	int64_t sum = 0;
	int count = 0;
	fp = fopen(file_name, "r");
	if (fp) {
		while (fgets(input, sizeof input, fp)) {
			if (sscanf(input, "%d%d", &l1[1023], &l2[1023]) == 2) {
				count++;
				sort(l1);
				sort(l2);
			} else {
				printf("Error while scanning line\n");
				break;
			}
		}
		for (int i = 0; i < count; i++) {
			sum += abs(l1[i] - l2[i]);
		}
		printf("Part 1 result: %d\n", sum);
	} else {
		printf("No such file found\n");
	}
	fclose(fp);
}

void part2(char* file_name) {
	FILE* fp;
	char input[120];
	int64_t d = 0;
	int64_t i1 = 0;
	int64_t i2 = 0;
	int64_t l1[100000] = {0};
	int64_t l2[100000] = {0};
	int64_t sum = 0;
	int count = 0;
	fp = fopen(file_name, "r");
	if (fp) {
		while (fgets(input, sizeof input, fp)) {
			if (sscanf(input, "%d%d", &i1, &i2) == 2) {
				count++;
				l1[i1]++;
				l2[i2]++;
			} else {
				printf("Error while scanning line\n");
				break;
			}
		}
		for (int i = 10000; i < 100000; i++) {
			sum += i * l1[i] * l2[i];
		}
		printf("Part 2 result: %d\n", sum);
	} else {
		printf("No such file found\n");
	}
	fclose(fp);
}