#include <stdlib.h>
#include <stdio.h>

#include "vector.h"
#include "stack.h"
#include "errno.h"

/* Global Vars 
	(These should maybe go in the include file for the whole directory? */
vector sem_list;
stack sem_stack;
//vector waiting_Q;  // This will eventually hold a vector of queues

int sem_init(int start_val)
{
	int init = -1;
	
	if(checkEmpty(&sem_stack){
		init = vector_add(&sem_list, start_val);
	}
	else{ 	// use top stack value
		init = pop(&sem_stack);
		vector_set(&sem_list, init, start_val);
	}

	return init;

	// I'm not sure where we should return the ENOMEM error val..
	//   ..probably in the vector.c file
}

int sem_release(int sem_num)
{
	int release = vector_get(&sem_list, sem_num);
	
	if(release == NULL){
		return EINVAL;	
	}
	/***** Pseudo-code ******
	if( vector_get(&waiting_Q, sem_num != empty){
		return EINUSE
	}
	*/
	else{
		vector_set(&sem_list, sem_num, NULL); // set to inactive state
		push(&sem_stack, sem_num); // add sem_num to stack
	}
	
	return OK;
}




///////////////////////////////

int main(void)
{
	vector_init(&sem_list);
 	
	/*
	vector_add(&v, "emil");
	vector_add(&v, "hannes");
	vector_add(&v, "lydia");
	vector_add(&v, "olle");
	vector_add(&v, "erik");
 
	int i;
	printf("first round:\n");
	for (i = 0; i < vector_count(&v); i++) {
		printf("%s\n", vector_get(&v, i));
	}
 
	vector_delete(&v, 1);
	vector_delete(&v, 3);
 
	printf("second round:\n");
	for (i = 0; i < vector_count(&v); i++) {
		printf("%s\n", vector_get(&v, i));
	}
 	*/


	vector_free(&v);
 
	return 0;
}
