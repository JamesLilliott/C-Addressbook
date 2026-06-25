CC = gcc
CFLAGS = -Wall -Wextra -g

addressbook: main.c contact.c contact.h
	$(CC) $(CFLAGS) main.c contact.c -o addressbook

clean:
	rm -f addressbook