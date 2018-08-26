CC=gcc
CFLAGS=-Wall -c -g -std=c11
LFLAGS=

LIBS=-lm 

OBJS=al_stack.o array_list.o test_harness.o test_harness_helper.o 

SRCS=al_stack.c test_harness.c 


copy_File: $(OBJS)
	$(CC) -o al_stack $(LFLAGS) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f al_stack al_stack.o test_harness *~ core

