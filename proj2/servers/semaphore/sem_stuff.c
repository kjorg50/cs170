// Kyle Jorgensen and Alex Mousavi, CS170, Proj 2, 5-9-13

#include <stdlib.h>
#include <stdio.h>
#include "inc.h"
#include "vector.h"
#include "stack.h"
#include "queue_vec.h"
#include "errno.h"




int sem_init(int start_val)
{
	int init = -1;
	//printf("sem_init: started\n");
	int * add = malloc(sizeof(int));
	*add = start_val;
	queue * q = freshQ();
	if(checkEmpty(&sem_stack)){
		init = vector_add(&sem_list,add);
		Qvector_add(&waiting_list, q, init);
	}
	else{ 	// use top stack value
		init = pop(&sem_stack);
		vector_set(&sem_list, init,add);
		Qvector_set(&waiting_list, init, q);
	}
	
	
	//printf("sem_init: created semaphore %d\n",init);
	return init;

	// I'm not sure where we should return the ENOMEM error val..
	//   ..probably in the vector.c file
}

int sem_release(int sem_num)
{
	int* release = vector_get(&sem_list, sem_num);
	
	if(release == NULL || (*release)<0){
		//should be an error		
		return EINVAL;	
	}
	//printf("let's release semaphore number %d with value %d\n",sem_num,*release);
	//relase the allocated pointer
	free(release);
	
	// if there are processes waiting for this semaphore, then it is still in use
	if( (Qvector_get(&waiting_list, sem_num))->front != NULL){
		return EINUSE;
	}
	
	else{
		int * released_flag = malloc(sizeof(int));
		*released_flag = -1;
		vector_set(&sem_list, sem_num, released_flag); // set to inactive state
        //(&sem_list)->count -= 1; // decrease vector count
		//printf("sem_list item removed, count is %d\n",(&sem_list)->count);
		push(&sem_stack, sem_num); // add sem_num to stack
		// TODO - release the waiting Q
	}
	
	//printf("sem_release complete\n");
	
	return OK;
}

// semaphore.P()
int sem_down(int sem_num, endpoint_t source)
{
	//cast is needed or shit gets bad
    int* down = (int *)vector_get(&sem_list, sem_num);
	//printf("in sem_down: semaphore: %d value:%d\n",sem_num,(*down));
	//return OK;

	// if the semaphore is uninitialized
    if(down == NULL || (*down) < 0) return EINVAL;
    
    if((*down) > 0){ // resource available, decrement semaphore
        (*down)--;
        vector_set(&sem_list, sem_num, down);
		//printf("sem_down: resources available, returning OK\n");        
		return OK;
    }
    else { // resource is taken, enqueue the caller and make it wait
        queue* temp = Qvector_get(&waiting_list, sem_num);
		
		// if there is no waiting Q yet, create one
        if(temp == NULL){ 
			//printf("Got Queue, is NULL\n");
			queue * q = freshQ();
			enqueue(q, source);
			display(q);
			Qvector_add(&waiting_list, q, sem_num);
        }
		else{ 
			//printf("Got Queue, not NULL\n");
			enqueue(temp, source); 
			Qvector_set(&waiting_list, sem_num, temp);
		}
		//printf("sem_down: not replying, busy");
		return EDONTREPLY;
    }

    
}

// semaphore.V()
int sem_up(int sem_num)
{
	int* up = vector_get(&sem_list, sem_num);

	// if the semaphore is uninitialized
	if(up == NULL || (*up) < 0) return EINVAL;

	

	// if there is anything waiting, wake it up (check if the queue is not empty)
	queue* temp = Qvector_get(&waiting_list, sem_num);
	if( temp != NULL && temp->front != NULL){
		//printf("attempting to dequeue pointer and send message\n");
		message m;
		m.m_source = dequeue(temp); // This is necessary, to get the process ID to wake up
		m.m_type = OK;
		send(m.m_source, &m); // Idk what should actually be called
		//printf("message supposedly sent\n");
	} else {
		// increment semaphore
		(*up)++;
		vector_set(&sem_list, sem_num, up);
	}
	//printf("sem_up: complete, up = %d\n",(*up));	
	return OK;
}



///////////////////////////////
//sample main
/*
int main(void)
{
	vector_init(&sem_list);
    Qvector_init(&waiting_list);
 	



    Qvector_free(&waiting_list);
	vector_free(&sem_list);
 
	return 0;
}

*/
