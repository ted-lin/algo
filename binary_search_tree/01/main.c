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
struct node *search(struct node *root, int data);
void cleanUp(struct node *root);

/* impl. of traversal */
void inOrder(struct node *root);
void reverseInOrder(struct node *root);
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

void reverseInOrder(struct node *root)
{
	static int depth = 0;

	if (!depth)
		printf("%s: ", __func__);

	if (root) {
		++depth;
		reverseInOrder(root->right);
		printf("%d ", root->value);
		reverseInOrder(root->left);
		--depth;
	}

	if (!depth)
		printf("\n");
}
void cleanUp(struct node *root)
{
	static int depth = 0;

	if (!depth)
		printf("%s: ", __func__);

	if (root) {
		++depth;
		printf("(0x%p, %d) ", root, root->value);
		cleanUp(root->left);
		cleanUp(root->right);
		free(root);
		--depth;
	}

	if (!depth)
		printf("\n");
}

struct node *search(struct node *root, int data)
{
	if (root) {
		if (data == root->value)
			return root;
		else if (data < root->value)
			return search(root->left, data);
		return search(root->right, data);
	}
	return NULL;
}

int main() {
	unsigned int n, i;
	struct node *node;

	n = 10;
	for (i = 0; i < n; ++i)
		root = insert(root, test[i]);

	preOrder(root);
	inOrder(root);
	reverseInOrder(root);
	postOrder(root);

	node = search(root, 3);
	if (node)
		printf("Find 0x%p, %d\n", node, node->value);
	else
		printf("Not found\n");

	node = search(root, 8);
	if (node)
		printf("Find 0x%p, %d\n", node, node->value);
	else
		printf("Not found\n");

	cleanUp(root);
	return 0;
}

