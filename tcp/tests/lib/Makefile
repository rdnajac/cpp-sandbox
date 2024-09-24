# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic
LDFLAGS = -L../../lib -ltcp

# Source files and target executables
SRCS = test_addr_info.c test_socket.c
TARGETS = $(SRCS:.c=)

# Phony targets
.PHONY: all clean

# Default target
all: $(TARGETS)

# Build each target
%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# Clean up
clean:
	rm -f $(TARGETS)

