CC = gcc

CFLAGS = -Wall -Wextra -g -pthread

all: race_condition deadlock

race_condition: race_condition.c

	$(CC) $(CFLAGS) -o race_condition race_condition.c

deadlock: deadlock.c

	$(CC) $(CFLAGS) -o deadlock deadlock.c

clean:

	rm -f race_condition deadlock

.PHONY: all clean