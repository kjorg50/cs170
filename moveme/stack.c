// Kyle Jorgensen and Alex Mousavi, CS170, Proj 2
// The following code is based on:
//   http://www.cs.bu.edu/teaching/c/stack/array/

#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

void stackInit(stack *stackP, int size)
{
	stackElementT *newContents;

  	/* Allocate a new array to hold the contents. */

  	newContents = (stackElementT *)malloc(sizeof(stackElementT)* size);

  	if (newContents == NULL) {
   		fprintf(stderr, "Insufficient memory to initialize stack.\n");
    	exit(1);  /* Exit, returning error code. */
  	}

  	stackP->contents = newContents;
  	stackP->size = size;
  	stackP->top = -1;  /* I.e., empty */
}

void stackDestroy(stack *stackP)
{
  /* Get rid of array. */
  free(stackP->contents);

  stackP->contents = NULL;
  stackP->size = 0;
  stackP->top = -1;  /* I.e., empty */
}

int checkEmpty(stack *stackP)
{
  return stackP->top < 0;
}

int checkFull(stack *stackP)
{
  return stackP->top >= stackP->size - 1;
}

void push(stack *stackP, stackElementT element)
{
  if (checkFull(stackP)) {
    fprintf(stderr, "Can't push element on stack: stack is full.\n");
    exit(1);  /* Exit, returning error code. */
  }

  // top gets incremented before it is used as an index for the array
  stackP->contents[++stackP->top] = element; 
}

stackElementT pop(stack *stackP)
{
  if (checkEmpty(stackP)) {
    fprintf(stderr, "Can't pop element from stack: stack is empty.\n");
    exit(1);  /* Exit, returning error code. */
  }

  // this time, the value of top gets used as the index BEFORE it is decremented
  return stackP->contents[stackP->top--];
}
