

#include "inc.h"	/* include master header file */
#include <minix/endpoint.h>

/* Allocate space for the global variables. */
static endpoint_t who_e;	/* caller's proc number */
static int callnr;		/* system call number */


static void get_work(message *m_ptr);
static void reply(endpoint_t whom, message *m_ptr);
int ipc_status;

/*===========================================================================*
 *				main                                         *
 *===========================================================================*/
int main(int argc, char **argv)
{
/* This is the main routine of this service. The main loop consists of 
 * three major activities: getting new work, processing the work, and
 * sending the reply. The loop never terminates, unless a panic occurs.
 */
  message m_in;
  int result;                 
  
  sef_startup();

	vector_init(&sem_list);
    Qvector_init(&waiting_list);
	stackInit(&sem_stack,5);

  /* Main loop - get work and do it, forever. */         
  while (TRUE) {              


	
      /* Wait for incoming message, sets 'callnr' and 'who'. */
    get_work(&m_in);
	//printf("SEM recieved message %d\n",callnr);
      if (is_notify(callnr)) {
          printf("SEM: warning, got illegal notify from: %d\n", m_in.m_source);
          result = EINVAL;
          goto send_reply;
      }

	int arg = m_in.m1_i1;
	switch(callnr)
	{	
		case SEM_INIT:
			//printf("Sem_init called, semaphore size 3%d.\n",arg);			
			result = sem_init(arg);			
			break;
		case SEM_UP:
			//printf("Sem_up called on semaphore %d.\n",arg);
			result = sem_up(arg);
			break;
		case SEM_DOWN:
			//printf("Sem_down called on semaphore %d. source: %d\n",arg,who_e);
			result  = sem_down(arg,m_in.m_source);
			break;
		case SEM_RELEASE:
			//printf("Sem_release called on semaphore %d.\n",arg);
			result = sem_release(arg);
			break;
		default: 
          		printf("SEMAPHORE: warning, got illegal request from %d\n", m_in.m_source);
          		result = EINVAL;
	}	



send_reply:
    	/* Finally send reply message, unless disabled. */
    	if (result != EDONTREPLY) {
        	m_in.m_type = result;  		/* build reply message */
			reply(who_e, &m_in);		/* send it away */
      }
	}
	Qvector_free(&waiting_list);
	vector_free(&sem_list);
	return(OK);				/* shouldn't come here */
}



/*===========================================================================*
 *				get_work                                     *
 *===========================================================================*/
static void get_work(
  message *m_ptr			/* message buffer */
)
{
    int status = sef_receive_status(ANY, m_ptr, &ipc_status);   /* blocks until message arrives */
    if (OK != status)
        panic("failed to receive message!: %d", status);
    who_e = m_ptr->m_source;        /* message arrived! set sender */
    callnr = m_ptr->m_type;       /* set function call number */
}

/*===========================================================================*
 *				reply					     *
 *===========================================================================*/
static void reply(
  endpoint_t who_e,			/* destination */
  message *m_ptr			/* message buffer */
)
{
    int s = send(who_e, m_ptr);    /* send the message */
    if (OK != s)
        printf("DS: unable to send reply to %d: %d\n", who_e, s);
}

