// Kyle Jorgensen and Alex Mousavi, CS170, Proj 2
// The following code is based on:
//   http://www.cs.bu.edu/teaching/c/stack/array/

#ifndef STACK_H__
#define STACK_H__

typedef int stackElementT; // give it a generic name type, in this case they will be ints

typedef struct stack_ {
	stackElementT *contents;
	int top;
	int size;
} stack;

void stackInit(stack *stackP, int size);
void stackDestroy(stack *stackP);
int checkEmpty(stack *stackP);
int checkFull(stack *stackP);
void push(stack *stackP, stackElementT element);
stackElementT pop(stack *stackP);

#endif