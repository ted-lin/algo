#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

#define msg(s ...) \
	do { \
		fprintf(stdout, s); \
	} while (0);

#define errmsg(s ...) \
	do { \
		fprintf(stderr, s); \
	} while (0);

/*
 * test data 1
 * Non-sorted
 */
int test1[10] = {
	6, 2, 10, 7, 8, 1, 3, 5, 9, 0 };

void counting_sort (int *data, int size) {
	int max = -INT_MAX, min = INT_MAX;
	int i = 0, range = 0;
	int *tmp = NULL, *cache = NULL;

	cache = (int *) malloc(size * sizeof(int));
	if (cache) {
		for (i = 0; i < size; ++i) {
			if (data[i] > max)
				max = data[i];
			if (data[i] < min)
				min = data[i];
			cache[i] = data[i];
		}
	} else {
		errmsg("malloc error (%s)\n", strerror(errno));
		return;
	}

	if (max > min) {
		range = max - min + 1;
		tmp = (int *) calloc(range, sizeof(int));
		if (!tmp) {
			errmsg("malloc error (%s)\n", strerror(errno));
			if (cache)
				free(cache);
			return;
		}
	} else {
		errmsg("data are all the same\n");
		return;
	}

	for (i = 0; i < size; ++i)
		tmp[data[i]]++;

	for (i = 1; i < max - min + 1; ++i)
		tmp[i] += tmp[i - 1];

	for (i = 0; i < size; ++i)
		data[(tmp[cache[i]]--)-1] = cache[i];

	free(tmp);
	free(cache);
}

void dump_data(int *data, int size)
{
	int i = 0;

	for (i = 0; i < size; ++i)
		msg("%d ", data[i]);
	msg("\n");
}

int main() {
	int size = sizeof(test1)/sizeof(int);

	dump_data(test1, size);
	counting_sort(test1, size);
	dump_data(test1, size);

	return 0;
}
