#include <unistd.h>
#include <lib.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	int CONTROL_SEM = sem_init(0);  // controls access to the pizza
	int GRAD_SEM = sem_init(0);     // controls access to the graduate line
	int UNDER_SEM = sem_init(0);    // controls access to the undergrad line
	int START_SEM = sem_init(0);    // controls when the serving of pizza starts
	
	printf("Grad sem # is %d\n",GRAD_SEM);
	printf("Undergrad sem # is %d\n",UNDER_SEM);
	printf("Start sem is %d (second argument)\n",START_SEM);
	printf("enter these in two separate terminal windows:\n");
	printf("./grad %d %d\n",GRAD_SEM,START_SEM);
	printf("./undergrad %d %d\n",UNDER_SEM,START_SEM);

	
    // We call down twice to place two items on the waiting queue.
    // They will block until up is called twice
	sem_down(START_SEM);
	sem_down(START_SEM);
	
    // Once the grad and undergrad files have indicated that they are ready to start,
    //   then we begin the serving of pizza. 
	printf("grad and undergrad signalled a start\n");
	
	
	int looper = 3;
	//start the pizza dispatch loop
	while(looper-- >= 0){
        sem_up(GRAD_SEM);
	    sem_up(GRAD_SEM);

		int k;
		for(k=0;k<2;k++){
			pid_t child = fork();
			if(child < 0){
				printf("ERROR in child process, dispatch grads");
				exit(1);
			}else if(child==0){
				//put a fake grad student in their pizza line
				//once he gets to the pizza, signal the control sem
				printf("Fake grad entering line\n");
				sem_down(GRAD_SEM);  // wait and enter pizza room
				sem_up(CONTROL_SEM); // increment free pizza spaces
				exit(0);
			}
		}
		
		//wait for the two pizza spots to open, then we signal the undergrads
		sem_down(CONTROL_SEM);
		sem_down(CONTROL_SEM);
		
		sem_up(UNDER_SEM);
		sem_up(UNDER_SEM);
        // now the undergrads waiting in line know that the room is free to eat pizza
		
		int j;
		for(j=0;j<2;j++){
			pid_t child = fork();
			if(child < 0){
				printf("ERROR in child process, dispatch undergrads");
				exit(1);
			}else if(child==0){
				//put a fake undergrad student in their pizza line
				//once he gets to the pizza, signal the control sem
				printf("Fake undergrad entering line\n");
				sem_down(UNDER_SEM); // wait and enter pizza room
				sem_up(CONTROL_SEM); // increment free pizza spaces
				exit(0);
			}
		}
		
        // wait for the two pizza spots to open again, before the grads can enter
		sem_down(CONTROL_SEM);
		sem_down(CONTROL_SEM);
		
	}// end while

    // the program should never get here, but if it does, it will exit and the 
    // grad and undergrad programs will keep running.
	
	exit(0);


}


