#include <sys/cdefs.h>
#include "namespace.h"
#include <lib.h>

#include <unistd.h>
#include <stdio.h>
int sem_down(int num)
{
	message m;
	m.m1_i1 = num;
	//printf("Hello World from sem_down\n");
 	return(_syscall(SEMAPHORE_PROC_NR,SEM_DOWN , &m));
}
