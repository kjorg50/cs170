// Kyle Jorgensen and Alex Mousavi, CS170, Proj 2
// Some of this code is based on:
//   http://www.cprogramto.com/queue-using-linked-list-in-c/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inc.h"
#include "queue_vec.h"


/****************************
*     Queue functions       *
*****************************/
queue * freshQ(){
	queue * q;
	q = malloc(sizeof(queue));
	queue newQ;
	newQ.front = NULL;
	newQ.rear = NULL;
	*q = newQ;
	return q;
}

void enqueue(queue* q, endpoint_t num)
{
    node* n;
    n = malloc(sizeof(node));
    n->info = num;
    n->next = NULL;

    if(q->front == NULL && q->rear == NULL){  // if the queue is empty
        q->front = q->rear = n;
    }
    else { // queue is non-empty
        q->rear->next = n;
        q->rear = n;
    }
    return;
}

endpoint_t dequeue(queue* q)
{
    endpoint_t result;
    node* temp;

    temp = q->front;
    result = temp->info; // get the information from the first node
    q->front = q->front->next;

    // free memory
    temp->next = NULL;
    free(temp);
    if(q->front == NULL)
        q->rear = NULL;

    return result;
}

void display(queue* q)
{
    node* iter;
    iter = q->front;
    
    //printf("Queue start ");
    while(iter != NULL){
        //printf("->%d", iter->info);
        iter = iter->next;
    }
    printf("\n");
    return;
}

/****************************
*     QVector functions     *
*****************************/
void Qvector_init(queue_vec *v)
{
	v->data = NULL;
	v->size = 0;
	v->count = 0;
}

int Qvector_count(queue_vec *v)
{
	return v->count;
}

void Qvector_add(queue_vec *v, queue *q, int index)
{
	if (v->size == 0) {
		v->size = 10;
		v->data = malloc(sizeof(queue*) * v->size);
		memset(v->data, '\0', sizeof(queue) * v->size);
	}
 
	// condition to increase v->data:
	// last slot exhausted
	if (v->size == v->count) {
		v->size *= 2;
		v->data = realloc(v->data, sizeof(queue*) * v->size);
	}
 
	v->data[index] = q;
	//added_index = v->count;
	v->count++;

	//return added_index;
}

int Qvector_set(queue_vec *v, int index, queue *q)
{
	if (index >= v->size) { 
		// I don't think we need these printf statements, but I just left them for now
		fprintf(stderr, "EINVAL: semaphore number is out of bounds.\n");
		return EINVAL;
	}
 
	v->data[index] = q;
	return OK;
}

queue *Qvector_get(queue_vec *v, int index)
{
	if (index >= v->size) {
		//fprintf(stderr, "EINVAL: semaphore number is out of bounds.\n");
		return NULL;
	}
 
	return v->data[index];
}

void Qvector_free(queue_vec *v)
{
	free(v->data);
}





