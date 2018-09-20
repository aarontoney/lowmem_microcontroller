CC=gcc
CFLAGS=-Wall -c -g -std=c11
LFLAGS=

LIBS=-lm 

OBJS=all_pqueue.o array_linkedlist.o array_freelist.o test_harness.o test_harness_helper.o 

SRCS=all_pqueue.c array_freelist.c test_harness.c test_harness_helper.c 

copy_File: $(OBJS)
	$(CC) -o all_priority_queue $(LFLAGS) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f all_priority_queue all_priority_queue.o test_harness.o test_harness_helper.o *~ core

