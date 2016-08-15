#include <stdio.h>
#include <stdlib.h>

/*
 * test data 1
 */
int test1[10] = {
	1, 3, 5, 7, 9, 2, 4, 6, 8, 10};

typedef struct Node Node;
struct Node {
	int key;
	unsigned int depth;
	Node *next;
	Node *prev;
};

typedef struct Stack Stack;
struct Stack {
	unsigned int count;
	Node *top;
};


Node *createNode(int key)
{
	Node *n = (Node *) malloc(sizeof(Node));

	if (n) {
		n->key = key;
		n->next = NULL;
		n->prev = NULL;
		return n;
	}
	return NULL;
}

void cleanNode(Node *n)
{
	if (n)
		free(n);
}

Stack *createStack()
{
	Stack *s = (Stack *) malloc(sizeof(Stack));

	if (s) {
		s->count = 0;
		s->top = NULL;
		return s;
	}
	return NULL;
}

void cleanStack(Stack *s)
{
	Node *n = s->top;
	Node *cur = n;

	while(n) {
		cur = n->prev;
		free(n);
		if (cur)
			n = cur;
	}
}

void push(Stack *s, Node *n)
{

	if (!s)
		return;

	if (!n)
		return;

	if (!s->top) {
		s->top = n;
		++(s->count);
		return;
	}

	s->top->next = n;
	n->prev = s->top;
	s->top = n;
	++(s->count);
}

Node *pop(Stack *s)
{
	Node *n = s->top;

	if (s->top) {
		s->top = s->top->prev;
		--(s->count);
		return n;
	}
	return NULL;
}

void dumpStack(Stack *s)
{
	Node *n = s->top;

	printf("count: %d: ", s->count);
	while(n) {
		printf("%d ", n->key);
		n = n->prev;
	}
	printf("\n");
}

int main()
{
	int size = sizeof(test1)/sizeof(int);
	int i;
	Stack *s = createStack();

	for (i = 0; i < size; ++i)
		push(s, createNode(test1[i]));

	dumpStack(s);
	for (i = 0; i < size; ++i) {
		free(pop(s));
		dumpStack(s);
	}
	return 0;
}
