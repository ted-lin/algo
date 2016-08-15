#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*
 * test data 1
 * Not balanced.
 */
int test1[10] = {
	5, 2, 3, 1, 7, -1, 6, 4, 9, 0};

/*
 * test data 2
 */
int test2[10] = {
	8, 10, 14, 11, 16, 19, 18, 15, 17, 12};

typedef struct Node Node;
struct Node {
	int key;
	Node *left;
	Node *right;
	Node *parent;
};

typedef struct Tree Tree;
struct Tree {
	Node *root;
};

Node *createNode(int key)
{
	Node *n = (Node *) malloc(sizeof(Node));
	n->left = NULL;
	n->right = NULL;
	n->parent = NULL;
	n->key = key;
	return n;
}

void cleanUp(Node *n)
{
	if (n) {
		cleanUp(n->left);
		cleanUp(n->right);
		printf("(0x%p, %d) ", n, n->key);
		free(n);
	}
}

Tree *createTree(void)
{
	Tree *t = (Tree *) malloc(sizeof(Tree));

	t->root = NULL;
	return t;
}

void cleanTree(Tree *t)
{
	cleanUp(t->root);
	free(t);
}

void cleanNode(Node *n)
{
	if (n)
		free(n);
}

Node *treeMax(Node *n)
{
	while (n->right) {
		n = n->right;
	}
	return n;
}

Node *treeMin(Node *n)
{
	while (n->left)
		n = n->left;
	return n;
}

Node *searchNode(Node *n, int key)
{

	while(n) {
		if (key == n->key)
			return n;
		else if (key < n->key)
			n = n->left;
		else
			n = n->right;
	}
	return n;
}

void insertNode(Tree *t, Node *x)
{
	Node *pos = NULL;
	Node *cur = t->root;

	if (!x)
		return;

	while(cur) {
		pos = cur;
		if (x->key < cur->key)
			cur = cur->left;
		else
			cur = cur->right;
	}

	x->parent = pos;

	if (!pos)
		t->root = x;
	else if (x->key < pos->key)
		pos->left = x;
	else
		pos->right = x;
}

void postExtract(Tree *a, Node *x)
{
	if (x) {
		postExtract(a, x->left);
		postExtract(a, x->right);
		x->left = NULL;
		x->right = NULL;
		insertNode(a, x);
	}
}

void mergeTree(Tree *a, Tree *b)
{
	postExtract(a, b->root);
}

void preReverse(Node *x)
{
	if (x) {
		Node *tmp = x->left;
		x->left = x->right;
		x->right = tmp;
		preReverse(x->left);
		preReverse(x->right);
	}
}

void reverseTree(Tree *a)
{
	preReverse(a->root);
}

/* don't update x->left, x->right, caller should responsible */
void transplant(Tree *t, Node *x, Node *y)
{
	if (!x->parent)
		t->root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;

	if (y)
		y->parent = x->parent;
}

void deleteNode(Tree *t, Node *x)
{
	Node *y = NULL;

	if (!x)
		return;

	if (!x->left)
		transplant(t, x, x->right);
	else if (!x->right)
		transplant(t, x, x->left);
	else {
		y = treeMin(x->right);
		if (y->parent != x) {
			transplant(t, y, y->right);
			y->right = x->right;
			y->right->parent = y;
		}
		transplant(t, x, y);
		y->left = x->left;
		y->left->parent = y;
	}

	cleanNode(x);
}

void buildTree(Tree *t, int *data, unsigned int size)
{
	unsigned int i = 0;

	for(i = 0; i < size; ++i)
		insertNode(t, createNode(data[i]));
}

void inOrder(Node *n)
{
	static int depth = 0;

	if (n) {
		++depth;
		inOrder(n->left);
		printf("%d ", n->key);
		inOrder(n->right);
		--depth;
	}
	if (!depth)
		printf("\n");
}

void preOrder(Node *n)
{
	static int depth = 0;

	if (n) {
		++depth;
		printf("%d ", n->key);
		preOrder(n->left);
		preOrder(n->right);
		--depth;
	}
	if (!depth)
		printf("\n");
}

void postOrder(Node *n)
{
	static int depth = 0;

	if (n) {
		++depth;
		postOrder(n->left);
		postOrder(n->right);
		printf("%d ", n->key);
		--depth;
	}
	if (!depth)
		printf("\n");
}

void dumpData(int *data, unsigned int size)
{
	unsigned int i = 0;

	for(i = 0; i < size; ++i)
		printf("%d ", data[i]);
	printf("\n");
}

int main(int argc, char **argv)
{
	Tree *t = createTree();
	Tree *t2 = NULL;

	Node *n = NULL;

	printf("test 1: build tree, traversal and clean tree\n");

	dumpData(test1, sizeof(test1)/sizeof(int));
	buildTree(t, test1, sizeof(test1)/sizeof(int));
	preOrder(t->root);
	inOrder(t->root);
	postOrder(t->root);

	printf("test 2: find max & min\n");
	n = treeMax(t->root);
	printf("Max: %d\n", n->key);
	n = treeMin(t->root);
	printf("Min: %d\n", n->key);

	printf("test 3: delete\n");
	deleteNode(t, searchNode(t->root, 7));
	deleteNode(t, searchNode(t->root, 2));
	deleteNode(t, searchNode(t->root, INT_MAX));
	preOrder(t->root);
	inOrder(t->root);
	postOrder(t->root);
	cleanTree(t);

	printf("test 4: merge tree\n");
	t = createTree();
	t2 = createTree();
	buildTree(t, test1, sizeof(test1)/sizeof(int));
	buildTree(t2, test2, sizeof(test2)/sizeof(int));
	dumpData(test1, sizeof(test1)/sizeof(int));
	dumpData(test2, sizeof(test2)/sizeof(int));

	mergeTree(t, t2);
	inOrder(t->root);
	reverseTree(t);
	inOrder(t->root);
	cleanTree(t);

	printf("test 5: reverse tree\n");
	t = createTree();
	buildTree(t, test1, sizeof(test1)/sizeof(int));
	inOrder(t->root);
	reverseTree(t);
	inOrder(t->root);
	cleanTree(t);

	return 0;
}
