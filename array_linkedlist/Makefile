CC=gcc
CFLAGS=-Wall -c -g -std=c11
LFLAGS=

LIBS=-lm 

OBJS=array_linkedlist.o array_freelist.o test_harness.o test_harness_helper.o array_list.o

SRCS=array_linkedlist.c array_freelist.c test_harness.c test_harness_helper.c 

copy_File: $(OBJS)
	$(CC) -o array_linkedlist $(LFLAGS) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f array_linkedlist array_freelist.o array_linkedlist.o test_harness.o test_harness_helper.o *~ core


