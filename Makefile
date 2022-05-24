CC=gcc
CFLAGS=--std=c89

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

list_test: list.h list.o list_test.o
	$(CC) -o list_test list.h list.o  list_test.o $(CFLAGS)

.PHONY: clean

clean:
	rm *.o
	rm list_test
