# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic
AR = ar
ARFLAGS = rcs

LIB = libtcp.a
OBJ = tcp.o

all: $(LIB)

$(LIB): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c tcp.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(LIB)
