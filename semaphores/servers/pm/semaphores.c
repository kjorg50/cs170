#include "pm.h"
#include <minix/callnr.h>
#include <minix/com.h>
#include <minix/config.h>
#include <lib.h>

#include <unistd.h>
#include <stdio.h>

// ****************************************************************
// 				do_sem_init
// ****************************************************************
int do_sem_init(int start_value)
{
	printf("*** I am the sem init call\n");
	return(OK);

}
