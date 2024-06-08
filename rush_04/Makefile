
CFLAGS=-Wall -Wextra -g -fsanitize=address
CPPFLAGS=-MMD -Iinclude
LDFLAGS=
LDLIBS=-lm -lSDL2 -lSDL2_image

SRCS=$(wildcard src/*.c)
FILES=$(subst src/,,$(SRCS))
OBJS=$(addprefix obj/,$(FILES:.c=.o))

DEPS=$(OBJS:.o=.d)

.PHONY: all clean

all: bin/snake

-include $(DEPS)

obj/%.o: src/%.c
	gcc -c $(CFLAGS) $(CPPFLAGS) $< -o $@

bin/snake: $(OBJS)
	gcc $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -f $(OBJS) $(DEPS) bin/snake

