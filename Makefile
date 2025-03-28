CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Iinclude -g  # Remove "-lm" from CFLAGS
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c,obj/%.o,$(SRCS))
EXEC = passgen

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

clean:
	rm -rf obj $(EXEC)

.PHONY: all clean
