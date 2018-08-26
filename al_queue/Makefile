CC=gcc
CFLAGS=-Wall -c -g -std=c11
LFLAGS=

LIBS=-lm 

OBJS=al_queue.o array_list.o test_harness.o test_harness_helper.o 

SRCS=al_queue.c test_harness.c 


copy_File: $(OBJS)
	$(CC) -o al_queue $(LFLAGS) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f al_queue al_queue.o test_harness.o *~ core

