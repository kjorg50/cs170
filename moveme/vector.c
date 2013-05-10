// Kyle Jorgensen and Alex Mousavi, CS170, Proj 2
// This code is based on this gist:
//   https://gist.github.com/EmilHernvall/953968

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include "vector.h"
#include "errno.h"
 
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
 
int vector_add(vector *v, void *e)
{
	int added_index = -1;	

	if (v->size == 0) {
		v->size = 10;
		v->data = malloc(sizeof(void*) * v->size);
		memset(v->data, '\0', sizeof(void) * v->size);
	}
 
	// condition to increase v->data:
	// last slot exhausted
	if (v->size == v->count) {
		v->size *= 2;
		v->data = realloc(v->data, sizeof(void*) * v->size);
	}
 
	v->data[v->count] = e;
	added_index = v->count;
	v->count++;

	return added_index;
}
 
int vector_set(vector *v, int index, void *e)
{
	if (index >= v->size) { 
		// I don't think we need these printf statements, but I just left them for now
		fprintf(stderr, "EINVAL: semaphore number is out of bounds.\n");
		return EINVAL;
	}
 
	v->data[index] = e;
	return OK;
}
 
void *vector_get(vector *v, int index)
{
	if (index >= v->size) {
		fprintf(stderr, "EINVAL: semaphore number is out of bounds.\n");
		return NULL;
	}
 
	return v->data[index];
}
 
void vector_delete(vector *v, int index)
{
	if (index >= v->size) {
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
 

