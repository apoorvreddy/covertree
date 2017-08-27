CC = g++
IDIR = .
CFLAGS = -std=c++11 -lm -I$(IDIR)

knn: cli_main.cc utils.o point.o covertree.o node.o
	$(CC) -g -v -o knn cli_main.cc utils.o point.o covertree.o node.o $(CFLAGS)

utils.o: utils.cc utils.h
	$(CC) -g -c -o utils.o utils.cc $(CFLAGS)

point.o: point.cc point.h
	$(CC) -g -c -o point.o point.cc $(CFLAGS)

node.o: node.cc node.h
	$(CC) -g -c -o node.o node.cc $(CFLAGS)

covertree.o: covertree.cc covertree.h
	$(CC) -g -c -o covertree.o covertree.cc $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ knn