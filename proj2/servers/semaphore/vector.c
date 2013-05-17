// Kyle Jorgensen and Alex Mousavi, CS170, Proj 2
// This code is based on this gist:
//   https://gist.github.com/EmilHernvall/953968

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include "vector.h"
#include "errno.h"
#include "inc.h"
#include "proto.h"
 
void vector_init(vector *v)
{
	v->data = NULL;
	v->size = 0;
	v->count = 0;
}
 
int vector_count(vector *v)
{
	return v->count;
}
 
int vector_add(vector *v, void* e)
{
	int added_index = -1;	

	if (v->size == 0) {
		v->size = 10;
		v->data = malloc(sizeof(int) * v->size);
		memset(v->data, '\0', sizeof(void) * v->size);
	}
 
	// condition to increase v->data:
	// last slot exhausted
	if (v->size == v->count) {
		v->size *= 2;
		v->data = realloc(v->data, sizeof(void*) * v->size);
	}
 	
	v->data[v->count] = e;
	int * printme = (int *)v->data[v->count];
	added_index = v->count;
	v->count++;
	//printf("sem added with count %d at %d\n",*printme, v->count);
	return added_index;
}
 
int vector_set(vector *v, int index, void *e)
{
	
	if (index >= v->count) { 
		// I don't think we need these printf statements, but I just left them for now
		//printf("Vector set failed\n");
		fprintf(stderr, "EINVAL: semaphore number is out of bounds.\n");
		return EINVAL;
	}
 	//printf("Vector set setting %d\n",*(int*)e);
	v->data[index] = e;
	return OK;
}
 
void *vector_get(vector *v, int index)
{
	if (index >= v->count) {
		fprintf(stderr, "EINVAL: semaphore number is out of bounds.\n");
		return NULL;
	}
 	int * ret = (int *)v->data[index];
	//printf("Vector get returning %d size :%d\n", *ret,v->size);
	return v->data[index];
}
 
void vector_delete(vector *v, int index)
{
	if (index >= v->count) {
		return;
	}
 
	v->data[index] = NULL;
 
	int i, j;
	void **newarr = (void**)malloc(sizeof(void*) * v->count * 2);
	for (i = 0, j = 0; i < v->count; i++) {
		if (v->data[i] != NULL) {
			newarr[j] = v->data[i];
			j++;
		}		
	}
 
	free(v->data);
 
	v->data = newarr;
	v->count--;
}
 
void vector_free(vector *v)
{
	free(v->data);
}
 

