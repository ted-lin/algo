#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int test_data[16] = {
	13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, 4, 7};

struct solution {
	int left;
	int right;
	int sum;
};

struct solution *create_solution() {
	struct solution *sol = (struct solution *) malloc(sizeof(struct solution));

	if (sol) {
		sol->left = 0;
		sol->right = 0;
		sol->sum = 0;
		return sol;
	} else
		return NULL;
}

void delete_solution(struct solution *sol) {
	if (free)
		free(sol);
}

struct solution *find_maximum_crossing_subarray(int *array, int left, int mid, int right) {
	int left_sum = -INT_MAX;
	int right_sum = -INT_MAX;
	int left_max_idx = -1;
	int right_max_idx = -1;
	struct solution *sol = create_solution();
	int sum = 0, i;

	for(i = mid; i >= left; --i) {
		sum += array[i];
		if (sum > left_sum) {
			left_sum = sum;
			left_max_idx = i;
		}
	}

	sum = 0;

	for(i = mid + 1; i <= right; ++i) {
		sum += array[i];
		if (sum > right_sum) {
			right_sum = sum;
			right_max_idx = i;
		}
	}
	sol->left = left_max_idx;
	sol->right = right_max_idx;
	sol->sum = left_sum + right_sum;
	return sol;
}

struct solution *find_maximum_subarray(int *array, int left, int right) {
	struct solution *final_sol = NULL;
	static int depth = 0;
	printf("main  depth[%d]: left: %d, right: %d\n", depth++, left, right);

	if (left == right) {
		struct solution *sol = create_solution();
		sol->left = left;
		sol->right = right;
		sol->sum = array[left];
		final_sol = sol;
	} else {
		struct solution* left_sol = NULL; 
		struct solution* right_sol = NULL;
		struct solution* cross_sol = NULL;
		int mid = (left + right) / 2;

		left_sol = find_maximum_subarray(array, left, mid);
		right_sol = find_maximum_subarray(array, mid + 1, right);		
		cross_sol = find_maximum_crossing_subarray(array, left, mid, right);

		if (left_sol->sum >= right_sol->sum && left_sol->sum >= cross_sol->sum) {
			delete_solution(right_sol);
			delete_solution(cross_sol);
			final_sol = left_sol;
		} else if (right_sol->sum >= left_sol->sum && right_sol->sum >= cross_sol->sum) {
			delete_solution(left_sol);
			delete_solution(cross_sol);	
			final_sol = right_sol;
		} else {
			delete_solution(left_sol);
			delete_solution(right_sol);
			final_sol = cross_sol;
		}
	}
	--depth;
	return final_sol; 
}

int main() {
	struct solution *sol = NULL;

	sol = find_maximum_subarray(test_data, 0, (sizeof(test_data) / sizeof(int)) - 1);
	printf("left: %d, right: %d, sum: %d\n",
		sol->left, sol->right, sol->sum);
	delete_solution(sol);

	return 0;
}
