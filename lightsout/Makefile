CC=gcc -std=c99 -pedantic
FAST_FLAGS=-Wall -Wextra -Werror -Wshadow -g -O3
SAFE_FLAGS=-Wall -Wextra -Werror -Wshadow -g -fsanitize=undefined -DDEBUG

LIB= lib/*.o lib/*.c
SAFE_LIB=$(LIB:%.o=%-safe.o)
FAST_LIB=$(LIB:%.o=%-fast.o)


.PHONY: lightsout lightsout-d bitvector-test board-ht-test clean


default: lightsout lightsout-d

lightsout: $(LIB) bitvector.c board-ht.c lightsout.c
	$(CC) $(FAST_FLAGS) $(FAST_LIB) bitvector.c board-ht.c lightsout.c \
	      -o lightsout

lightsout-d: $(LIB) bitvector.c board-ht.c lightsout.c
	$(CC) $(SAFE_FLAGS) $(SAFE_LIB) bitvector.c board-ht.c lightsout.c \
	      -o lightsout-d

large: $(LIB) bitvector-large.c board-ht.c lightsout.c
	$(CC) $(FAST_FLAGS) $(FAST_LIB) bitvector-large.c board-ht.c lightsout.c \
  -o lightsout-large

bitvector-test: $(LIB) bitvector.c bitvector-test.c
	$(CC) $(SAFE_FLAGS) $(SAFE_LIB) bitvector.c bitvector-test.c \
	      -o bitvector-test

board-ht-test: $(LIB) bitvector.c board-ht.c board-ht-test.c
	$(CC) $(SAFE_FLAGS) $(SAFE_LIB) bitvector.c board-ht.c board-ht-test.c \
	      -o board-ht-test

clean:
	rm -Rf lightsout lightsout-d lightsout-large bitvector-test board-ht-test *.dSYM
