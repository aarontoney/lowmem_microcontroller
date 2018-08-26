CC=gcc
CFLAGS=-Wall -c -g -std=c11
LFLAGS=

LIBS=-lm 

OBJS=array_list.o test_harness.o test_harness_helper.o 

SRCS=array_list.c test_harness.c test_harness_helper.c 

copy_File: $(OBJS)
	$(CC) -o array_list $(LFLAGS) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f array_list *.o *~ core
