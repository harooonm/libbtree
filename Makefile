help:
	@echo "targets debug release"

clean:
	rm -f btree.o
	rm -f libbtree.so

INCDIR=include/
SRCDIR=src/
SRCS=$(wildcard $(SRCDIR)*.c)
CC=gcc
CFLAGS=-Wall -Wextra -Wfatal-errors -D_POSIX_C_SOURCE=200809L\
	-std=c11

IFLAGS=-I$(INCDIR)

debug:	CFLAGS += -g -Og
release:	CFLAGS += -flto -Os -s

debug:	objs
release:	objs


objs:
	$(CC) -c -fPIC $(CFLAGS) $(IFLAGS) $(SRCS)
	$(CC) $(CFLAGS) -shared -o libbtree.so btree.o
