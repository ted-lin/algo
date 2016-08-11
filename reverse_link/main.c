#include <stdio.h>
#include <stdlib.h>

struct Node {
	int index;
	struct Node *next;
};

struct Node list[6];

void list_dump(struct Node *root) {
	while(root) {
		printf("%d ", root->index);
		root = root->next;
	}
	printf("\n");
}

void init_list(void) {
	int index = 0;
	printf("init list\n");
	for (index = 0; index < sizeof(list) / sizeof(struct Node); ++index) {
		list[index].index = index;
		if (index == sizeof(list)/sizeof(struct Node) - 1) {
			list[index].next = NULL;
			break;
		}
		list[index].next = &list[index+1];
	}
}

struct Node *reverse(struct Node *root) {
	struct Node* new_root = NULL;
	while (root) {
		struct Node* next = root->next;
		root->next = new_root;
		new_root = root;
		root = next;
	}
	return new_root;
}

void divide_odd_even(struct Node *root, struct Node *odd, struct Node *even) {
	while (root) {
		if (root->index % 2) {
			/* goes odd */
			odd->next = root;
			odd = root;
		} else {
			/* goes even */
			even->next = root;
			even = root;
		}
		root = root->next;
	}
	odd->next = NULL;
	even->next = NULL;
}

int main(void) {
	struct Node odd, even;
	init_list();
	divide_odd_even(list, &odd, &even);
	list_dump(odd.next);
	list_dump(even.next);
	list_dump(reverse(&even));
	return 0;
}

