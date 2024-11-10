CC = gcc
CFLAGS = -o

all: send tcp

send: send.c
	$(CC) send.c $(CFLAGS) send

tcp: tcp.c
	$(CC) tcp.c $(CFLAGS) tcp

clean:
	rm -f send tcp

