#include <sys/cdefs.h>
#include "namespace.h"
#include <lib.h>

#include <unistd.h>
#include <stdio.h>


void lsr(char * path)
{
	//printf("LSR begin\n");
	message m;
	_loadname(path, &m);
	return(_syscall(VFS_PROC_NR, LSR, &m));
}
