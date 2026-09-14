CC = gcc
CFLAGS = -Wall -Wextra -g -pthread

all: race_condition

race_condition: race_condition.c
	$(CC) $(CFLAGS) -o race_condition race_condition.c

clean:
	rm -f race_condition

.PHONY: all clean