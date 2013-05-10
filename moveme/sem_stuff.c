// Kyle Jorgensen and Alex Mousavi, CS170, Proj 2, 5-9-13

#include <stdlib.h>
#include <stdio.h>

#include "vector.h"
#include "stack.h"
#include "queue_vec.h"
#include "errno.h"

/* Global Vars 
	(These should maybe go in the include file for the whole directory? */
vector sem_list;        // vector of semaphore values
stack sem_stack;        // stack of semaphores that have been released
queue_vec waiting_list; // vector of queues, with waiting_list[i] being the queue of 
                        //   waiting processes for the semaphore at sem_list[i]

int sem_init(int start_val)
{
	int init = -1;
	
	if(checkEmpty(&sem_stack)){
		init = vector_add(&sem_list, &start_val);
	}
	else{ 	// use top stack value
		init = pop(&sem_stack);
		vector_set(&sem_list, init, &start_val);
	}

	return init;

	// I'm not sure where we should return the ENOMEM error val..
	//   ..probably in the vector.c file
}

int sem_release(int sem_num)
{
	int* release = vector_get(&sem_list, sem_num);
	
	if(release == NULL){
		return EINVAL;	
	}

	// if there are processes waiting for this semaphore, then it is still in use
	if( (Qvector_get(&waiting_list, sem_num))->front != NULL){
		return EINUSE;
	}
	else{
		vector_set(&sem_list, sem_num, NULL); // set to inactive state
        (&sem_list)->count -= 1; // decrease vector count
		push(&sem_stack, sem_num); // add sem_num to stack
	}
	
	return OK;
}

// semaphore.P()
int sem_down(int sem_num)
{
    int* down = vector_get(&sem_list, sem_num);
    
	// if the semaphore is uninitialized
    if(down == NULL) return EINVAL;
    
    if((*down) > 0){ // resource available, decrement semaphore
        (*down)--;
        vector_set(&sem_list, sem_num, down);
        return OK;
    }
    else { // resource is taken, enqueue the caller and make it wait
        queue* temp = Qvector_get(&waiting_list, sem_num);

		// if there is no waiting Q yet, create one
        if(temp == NULL){ 
            /* enqueue(temp, m_ptr->m_source); // This is the line that should exist */
			enqueue(temp, 42); // 42 IS A STUB VALUE, IT SHOULD BE THE PROCESS ID
			Qvector_add(&waiting_list, temp, sem_num);
        }
		else{ 
			/* enqueue(temp, m_ptr->m_source); // This is the line that should exist */
			enqueue(temp, 42); // 42 IS A STUB VALUE, IT SHOULD BE THE PROCESS ID
			Qvector_set(&waiting_list, sem_num, temp);
		}
		
		return EDONTREPLY;
    }  
    
}

// semaphore.V()
int sem_up(int sem_num)
{
	int* up = vector_get(&sem_list, sem_num);

	// if the semaphore is uninitialized
	if(up == NULL) return EINVAL;

	// increment semaphore
	(*up)++;
	vector_set(&sem_list, sem_num, up);

	// if there is anything waiting, wake it up (check if the queue is not empty)
	queue* temp = Qvector_get(&waiting_list, sem_num);
	if( temp->front != NULL){
		/* ALEX, I DON'T KNOW WHAT TO DO HERE, so I copied the pdf example
		message m;
		m.m_source = dequeue(temp); // This is necessary, to get the process ID to wake up
		ipc_reply(m.m_source, m); // Idk what should actually be called
		*/
	}	
	return OK;
}



///////////////////////////////

int main(void)
{
	vector_init(&sem_list);
    Qvector_init(&waiting_list);
 	



    Qvector_free(&waiting_list);
	vector_free(&sem_list);
 
	return 0;
}
