CC=gcc
CFLAGS=-g
OBJS = DynamicString.o main.o

heap: $(OBJS) 
	$(CC) $(CFLAGS) $^ -o $@

DynamicString.o: DynamicString.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf heap *.o
