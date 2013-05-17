// Kyle Jorgensen and Alex Mousavi, CS170, Proj 2
// This code is based on this gist:
//   https://gist.github.com/EmilHernvall/953968


#ifndef VECTOR_H__
#define VECTOR_H__
 
typedef struct vector_ {
    void** data;
    int size;
    int count;
} vector;
 
void vector_init(vector*);
int vector_count(vector*);
int vector_add(vector*, void*);
int vector_set(vector*, int, void*);
void *vector_get(vector*, int);
void vector_delete(vector*, int);
void vector_free(vector*);
 
#endif
