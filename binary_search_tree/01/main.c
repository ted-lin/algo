#include <stdio.h>
#include <stdlib.h>

/* test data built-in */
int test[10] = {
	5, 2, 3, 1, 7, -1, 6, 4, 9, 0};

struct node
{
	int value;
	struct node *left;
	struct node *right;
};

struct node *root = NULL;

/* impl. of bst */
struct node *insert(struct node *root, int data);

/* impl. of traversal */
void inOrder(struct node *root);
void preOrder(struct node *root);
void postOrder(struct node *root);

struct node *insert(struct node *root, int data)
{
	if (root == NULL) {
		root = (struct node *) malloc (sizeof(struct node));
		root->left = NULL;
		root->right = NULL;
		root->value = data;
	} else if (data < root->value) {
		root->left = insert(root->left, data);
	} else
		root->right = insert(root->right, data);

	return root;
}

void preOrder(struct node *root)
{
	static int depth = 0;

	if (!depth)
		printf("%s: ", __func__);

	if (root) {
		++depth;
		printf("%d ", root->value);
		preOrder(root->left);
		preOrder(root->right);
		--depth;
	}

	if (!depth)
		printf("\n");
}

void postOrder(struct node *root)
{
	static int depth = 0;

	if (!depth)
		printf("%s: ", __func__);

	if (root) {
		++depth;
		postOrder(root->left);
		postOrder(root->right);
		printf("%d ", root->value);
		--depth;
	}

	if (!depth)
		printf("\n");
}

void inOrder(struct node *root)
{
	static int depth = 0;

	if (!depth)
		printf("%s: ", __func__);

	if (root) {
		++depth;
		inOrder(root->left);
		printf("%d ", root->value);
		inOrder(root->right);
		--depth;
	}

	if (!depth)
		printf("\n");
}
int main() {
	unsigned int n, i;
	int v;

	n = 10;

//	printf("How many node will you insert?\n");
//	scanf("%u", &n);

	for (i = 0; i < n; ++i) {
//		scanf("%d", &v);
		root = insert(root, test[i]);
	}

	preOrder(root);
	inOrder(root);
	postOrder(root);

	return 0;
}

