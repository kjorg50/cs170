#ifndef _DS_PROTO_H
#define _DS_PROTO_H

/* Function prototypes. */

/* main.c */
int main(int argc, char **argv);
int sem_init(int start_val);
int sem_release(int sem_num);
int sem_down(int sem_num,endpoint_t);
int sem_up(int sem_num);

/* Global Vars 
	(These should maybe go in the include file for the whole directory? */
vector sem_list;        // vector of semaphore values
stack sem_stack;        // stack of semaphores that have been released
queue_vec waiting_list; // vector of queues, with waiting_list[i] being the queue of 
                        //   waiting processes for the semaphore at sem_list[i]



#endif
