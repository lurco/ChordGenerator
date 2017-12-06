OBJECTS = $(P).c
CFLAGS = -g -Wall -Wextra -Wpedantic -std=c11
LDFLAGS =
LDLIBS = -lm -lgsl -lgslcblas -lncurses
CC = gcc

$(P): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(P).c $(LDLIBS)

clean:
	rm $(P)
