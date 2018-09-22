CC=gcc
CFLAGS=-Wall -c -g -std=c11
LFLAGS=

LIBS=-lm 

OBJS=all_pqueue.o ../array_linkedlist/array_linkedlist.o ../array_linkedlist/array_freelist.o test_harness.o
SRCS=all_pqueue.c test_harness.c 

copy_File: $(OBJS)
	$(CC) -o all_priority_queue $(LFLAGS) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f all_priority_queue all_priority_queue.o *~ core

