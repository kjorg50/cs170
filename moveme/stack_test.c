#include <stdio.h>
#include <string.h>  /* for strlen() */
#include "stack.h"

int main(void)
{
  stack my_stack;    /* A stack  */
  int nums[10];  
  nums[0]=2;
  nums[1]=4;
  nums[2]=8; 
  
  stackInit(&my_stack, 10);

  int i;
  for (i=0;i<3;i++) {
    push(&my_stack, nums[i]);
  }


  printf("\nPopped numbers are: ");

  while (!checkEmpty(&my_stack)) {
    printf("%d\n", pop(&my_stack));
  }

  printf("\n");

  stackDestroy(&my_stack);

  return 0;
}