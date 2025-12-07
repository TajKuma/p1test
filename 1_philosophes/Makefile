CC = gcc
CFLAGS = -O2 -std=c11 -Wall -Wextra -pthread
TARGET = compiled/solutions
BUILD_DIR = compiled
N ?= 5

.PHONY: sol test plot all clean

sol: $(TARGET)
	$(TARGET) $(N)

$(TARGET): solutions.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) solutions.c -lm

test: $(TARGET)
	bash ./tests.sh

plot: test
	./plot.py

clean:
	rm -f compiled/*

all: clean plot
