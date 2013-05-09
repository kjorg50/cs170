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

void StackDestroy(stack *stackP)
{
  /* Get rid of array. */
  free(stackP->contents);

  stackP->contents = NULL;
  stackP->size = 0;
  stackP->top = -1;  /* I.e., empty */
}
