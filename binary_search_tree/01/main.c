#include <stdio.h>
#include <stdlib.h>

/*
 * test data 1
 * Not balanced.
 */
int test[10] = {
	5, 2, 3, 1, 7, -1, 6, 4, 9, 0};

/*
 * test data 2
 * test L rotation
 */
int test2[6] = {
	10, 5, 4, 8, 7, 9};

/*
 * test data 3
 * test R rotate
 */
int test3[6] = {
	10, 8, 9, 5, 4, 7};

/*
 * test data 4
 * test insert count
 */
int test4[5] = {
	10, 9, 8, 7, 6};

struct node
{
	int value;
	int height;
	struct node *left;
	struct node *right;
	struct node *parent;
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

/* impl. of helper */
void dumpRawData(int *data, int len);

struct node *insert(struct node *root, int data)
{
	if (root == NULL) {
		root = (struct node *) malloc (sizeof(struct node));
		root->left = NULL;
		root->right = NULL;
		root->parent = NULL;
		root->value = data;
		root->height = 0;
	} else if (data < root->value) {
		root->left = insert(root->left, data);
		if (root->height < root->left->height + 1)
			root->height = root->left->height + 1;
		root->left->parent = root;
	} else {
		root->right = insert(root->right, data);
		if (root->height < root->right->height + 1)
			root->height = root->right->height + 1;
		root->right->parent = root;
	}
	return root;
}

struct node *insert2(struct node *root, int data)
{
	struct node *target = NULL;
	struct node *cur = NULL;
	struct node *tree = root;

	/* search deeply */
	while (root) {
		cur = root; //keep current
		if (data < root->value)
			root = root->left;
		else
			root = root->right;
	}

	target = (struct node *) malloc(sizeof(struct node));
	target->left = NULL;
	target->right = NULL;
	target->parent = cur;
	target->height = 0;
	target->value = data;
	if (!target->parent)
		return target; /* root case */
	else if (data < cur->value)
		cur->left = target; /* left case */
	else
		cur->right = target; /* right case */

	/* update height */
	while (cur) {
		if (cur->height < target->height + 1) {
			cur->height = target->height + 1;
			target = cur;
			cur = cur->parent;
		} else
			break;
	}

	/* return root */
	return tree;
}

void preOrder(struct node *root)
{
	static int depth = 0;

	if (!depth)
		printf("%s: ", __func__);

	if (root) {
		++depth;
		printf("[%d(h:%d", root->value, root->height);
		if (root->parent)
			printf(", p:%d)]  ", root->parent->value);
		else
			printf(")]  ");
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
		printf("[%d(h:%d", root->value, root->height);
		if (root->parent)
			printf(", p:%d)]  ", root->parent->value);
		else
			printf(")]  ");
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
		printf("[%d(h:%d", root->value, root->height);
		if (root->parent)
			printf(", p:%d)]  ", root->parent->value);
		else
			printf(")]  ");
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
		printf("[%d(h:%d", root->value, root->height);
		if (root->parent)
			printf(", p:%d)]  ", root->parent->value);
		else
			printf(")]  ");
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

void dumpRawData(int *data, int len)
{
	int i;

	printf("Dump data: ");

	for(i = 0; i < len; ++i)
		printf("%d ", data[i]);

	printf("\n");
}

void dumpTree(struct node *root)
{
	int base = 0, offset = 0, height = 0;

	printf("Tree:\n");
	if (!root) {
		printf("Empty tree\n");
		return;
	}

	base = (1 << (root->height + 1)) - 1;
	height = root->height;
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

void LRotate(struct node *root, struct node *key)
{
	struct node *tmp = key->right;

	key->right = tmp->left;
	if (tmp->left)
		tmp->left->parent = key;
	tmp->parent = key->parent;
	if (!key->parent)
		root = tmp;
	else if (key == key->parent->left)
		key->parent->left = tmp;
	else
		key->parent->right = tmp;
	tmp->left = key;
	key->parent = tmp;
}

void RRotate(struct node *root, struct node *key)
{
	struct node *tmp = key->left;

	key->left = tmp->right;
	if (tmp->right)
		tmp->right->parent = key;
	tmp->parent = key->parent;
	if (!key->parent)
		root = tmp;
	else if (key == key->parent->left)
		key->parent->left = tmp;
	else
		key->parent->right = tmp;
	tmp->right = key;
	key->parent = tmp;
}

struct node *buildTree(struct node *root, int *data, int len)
{
	int i = 0;
	for (i = 0; i < len; ++i)
		root = insert(root, data[i]);
	return root;
}

struct node *buildTree2(struct node *root, int *data, int len)
{
	int i = 0;
	for (i = 0; i < len; ++i)
		root = insert2(root, data[i]);
	return root;
}

int main() {
	unsigned int len, i;
	struct node *node;

	/* test 1 */
	printf("test common binary search tree\n");

	len = sizeof(test)/sizeof(int);
	root = buildTree(root, test, len);

	dumpRawData(test, len);

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
	root = NULL;

	/* test 2 */
	printf("\ntest L rotate\n");

	len = sizeof(test2)/sizeof(int);
	root = buildTree(root, test2, len);

	dumpRawData(test2, len);
	preOrder(root);
	inOrder(root);
	postOrder(root);
	node = search(root, 5);
	if (node) {
		printf("LRotate key %d:\n", node->value);
		LRotate(root, node);
		preOrder(root);
		inOrder(root);
		postOrder(root);
	}
	cleanUp(root);
	root = NULL;

	/* test 3 */
	printf("\ntest R rotate\n");

	len = sizeof(test3)/sizeof(int);
	root = buildTree(root, test3, len);

	dumpRawData(test3, len);
	preOrder(root);
	inOrder(root);
	postOrder(root);
	node = search(root, 8);
	if (node) {
		printf("RRotate key %d:\n", node->value);
		RRotate(root, node);
		preOrder(root);
		inOrder(root);
		postOrder(root);
	}
	cleanUp(root);
	root = NULL;

	///* test 4 */
	//printf("\n test insert counting\n");

	//len = sizeof(test4)/sizeof(int);
	//root = buildTree(root, test4, len);

	//cleanUp(root);
	//root = NULL;

	/* test 5 */
	printf("\n test insert 2 \n");
	len = sizeof(test)/sizeof(int);
	root = buildTree(root, test, len);
	dumpRawData(test, len);
	preOrder(root);
	inOrder(root);
	postOrder(root);
	cleanUp(root);
	root = NULL;
	root = buildTree2(root, test, len);
	dumpRawData(test, len);
	preOrder(root);
	inOrder(root);
	postOrder(root);
	cleanUp(root);
	root = NULL;

	///* test 6 */
	//printf("\n test insert 2 counting\n");

	//len = sizeof(test4)/sizeof(int);
	//root = buildTree2(root, test4, len);

	//cleanUp(root);
	//root = NULL;

	return 0;
}

