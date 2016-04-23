CC=gcc
CFLAGS=-Wall -c -g
LFLAGS=

LIBS=-lm 

OBJS=ring_buffer.o test_harness.o

SRCS=ring_buffer.c test_harness.c


copy_File: $(OBJS)
	$(CC) -o ring_buffer $(LFLAGS) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f ring_buffer *.o *~ core
