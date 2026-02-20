SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c, obj/%.o, $(SRCS))

all: $(OBJS)

obj/%.o: src/%.c
	@mkdir -p obj
	gcc -c $< -o $@
