CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Iinclude -g -lm
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c,obj/%.o,$(SRCS))
EXEC = passgen

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -lm $^ -o $@

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

clean:
	rm -rf build obj $(EXEC)

.PHONY: all clean
