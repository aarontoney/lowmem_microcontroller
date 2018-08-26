CC=gcc
CFLAGS=-Wall -c -g -std=c11
LFLAGS=

LIBS=-lm 

OBJS=algorithms.o test_harness.o

SRCS=algorithms.c test_harness.c


copy_File: $(OBJS)
	$(CC) -o algorithms $(LFLAGS) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f algorithms *.o *~ core
