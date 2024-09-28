CCX := g++
CXXFLAGS = -std=c++20 -g -Wall -Wpedantic -O2
LDFLAGS :=


OBJECTS := measure.o

all: measure


measure: $(OBJECTS)
	$(CCX) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJECTS)

%.o: %.c
	$(CCX) $(CFLAGS) -c $^

clean:
	rm -f measure *.o a.out

.PHONY: clean
