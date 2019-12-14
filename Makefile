%.o: %.c network.h parse.h
	gcc -c -o $@ $<

server: network.o parse.o
	gcc network.o parse.o -o server

run: server
	./server

clean:
	rm *.o server

test:
	make run
	make clean

.PHONY: run clean test
