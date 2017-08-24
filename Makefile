CC = g++
IDIR = .
CFLAGS = -std=c++11 -lm -I$(IDIR)

knn: cli_main.cc utils.o point.o
	$(CC) -g -v -o knn cli_main.cc utils.o point.o $(CFLAGS)

utils.o: utils.cc utils.h
	$(CC) -c -o utils.o utils.cc $(CFLAGS)

point.o: point.cc point.h
	$(CC) -c -o point.o point.cc $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ knn