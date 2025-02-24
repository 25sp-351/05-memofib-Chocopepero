# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g -I./munit -g3 -O0

# Target executable
EXEC = memofib

# Source files
SRCS = main.c fib.c memo.c ./tiny-bignum-c/bn.c bignum-helper.c
OBJS = $(SRCS:.c=.o)

# MUnit Test Files
TEST_SRCS = test_fib.c fib.c memo.c ./tiny-bignum-c/bn.c bignum-helper.c munit/munit.c
TEST_OBJS = $(TEST_SRCS:.c=.o)
TEST_EXEC = test_fib

# Default Target: Compile Program
all: $(EXEC)

# Compile Executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) -lm

# Compile Object Files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile Test Executable
$(TEST_EXEC): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_EXEC) $(TEST_OBJS) -lm

# Run MUnit Tests
test: $(TEST_EXEC)
	@echo "Running MUnit Tests..."
	./$(TEST_EXEC)

# Clean Build Files
clean:
	rm -f $(OBJS) $(EXEC) $(TEST_OBJS) $(TEST_EXEC)

# Phony Targets
.PHONY: all test clean