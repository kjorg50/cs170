// Kyle Jorgensen and Alex Mousavi, CS170, Proj 2
// The following code is based on:
//   http://www.cs.bu.edu/teaching/c/stack/array/

#ifndef VECTOR_H__
#define VECTOR_H__

typedef int stackElementT; // give the it a generic name type

typedef struct stack_ {
	stackElementT *contents;
	int top;
	int size;
} stack;

void stackInit(stack *stackP, int size);
void stackDestroy(stack *stackP);
int stackIsEmpty(stack *stackP);
int stackIsFull(stack *stackP);
