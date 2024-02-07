CC = clang++
CFLAGS = -Wall -Wextra -std=c++11

SRCS = expressions.cpp lexer.cpp
OBJS = $(patsubst %.cpp,bin/%.o,$(SRCS))
EXEC = bin/expressions

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

bin/%.o: %.cpp lexer.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
