%.o: %.c network.h parse.h
	gcc -c -o $@ $<

server: network.o parse.o
	gcc network.o parse.o -o server

run: server
	./server

clean:
	rm *.o server

test: url.o request.o method.o test.c
	gcc *.o test.c

.PHONY: run clean test
