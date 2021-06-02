# Created by Andrea Covre on 3/10/21.

CC=gcc
CFLAGS=-I. -lpthread
DEPS1 = chatserver.h
OBJ1 = chatserver.o

DEPS2 = chatclient.h
OBJ2 = chatclient.o

all: chatserver chatclient

%.o: %.c $(DEPS1)
	$(CC) -c -o $@ $< $(CFLAGS)

chatserver: $(OBJ1)
	$(CC) -o $@ $^ $(CFLAGS)
	rm chatserver.o

%.o: %.c $(DEPS2)
	$(CC) -c -o $@ $< $(CFLAGS)

chatclient: $(OBJ2)
	$(CC) -o $@ $^ $(CFLAGS)
	rm chatclient.o

clean:
	rm chatclient
	rm chatserver