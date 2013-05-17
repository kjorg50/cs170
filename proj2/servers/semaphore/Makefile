# Makefile for Data Store Server (DS)
PROG=	semaphore
SRCS=	main.c queue_vec.c sem_stuff.c stack.c vector.c

DPADD+=	${LIBSYS}
LDADD+=	-lsys

MAN=

BINDIR?= /usr/sbin

.include <minix.bootprog.mk>
