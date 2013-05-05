#include <sys/cdefs.h>
#include "namespace.h"
#include <lib.h>

#include <unistd.h>
// [modify]

int sem_init(int start_value)
{
	message m;
	
	return(_syscall(SEM_PROC_NR, SEM_INIT, &m));
}
