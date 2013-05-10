#ifndef QUEUE_VEC_H__
#define QUEUE_VEC_H__

typedef struct node_ {
	int info;
	struct node_* next;
} node;

typedef struct queue_ {
	node* front;
	node* rear;
} queue;

void enqueue(queue*, int);
int dequeue(queue*);
void display(queue*);

typedef struct queue_vec_ {
	queue** data;
	int size;
	int count;
} queue_vec;

void Qvector_init(queue_vec*);
int Qvector_count(queue_vec*);
void Qvector_add(queue_vec*, queue*,int);
int Qvector_set(queue_vec*, int, queue*);
queue *Qvector_get(queue_vec*, int);
//void Qvector_delete(queue_vec*, int);
void Qvector_free(queue_vec*);

#endif
