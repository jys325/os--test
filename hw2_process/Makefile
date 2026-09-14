CC = gcc
CFLAGS = -O2 -Wall -Wextra
LDLIBS = -lrt

PROGRAMS = shared_memory_example message_passing_example ipc_benchmark

all: $(PROGRAMS)

$(PROGRAMS): %: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

clean:
	rm -f $(PROGRAMS)

.PHONY: all clean
