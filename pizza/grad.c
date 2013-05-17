#include <unistd.h>
#include <lib.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	if(argc != 3){
		printf("enter the semaphore number as an argument\n");
		exit(0);
	}
	
	//sem will be the semaphore number we are using for grad students
	int sem = strtol(argv[1],NULL,10);

    // Uses another semaphore to signal to the dispatcher that it's ready
	int start_sem = strtol(argv[2],NULL,10);
	sem_up(start_sem);
	
	int i;
	for(i=0;i<6;i++){
        // we fork six children to represent the 6 grad students		
    
		pid_t child_p = fork();
		if(child_p < 0){
    		printf("ERROR in child process");
    		exit(1);
    	} else if (child_p==0){	
    	//in child process, run the loop
    		while(1){
				sem_down(sem);
				printf("grad #%d started eating\n",i);
				sleep(2);
				printf("grad #%d finished eating\n",i);
				sem_up(sem);
			}
    	}
		
	}
	
	
	return 0;
}
