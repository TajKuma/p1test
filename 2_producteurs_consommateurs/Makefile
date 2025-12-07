CC = gcc
CFLAGS = -O2 -std=c11 -Wall -Wextra -pthread
TARGET = compiled/solutions
BUILD_DIR = compiled
P ?= 2
C ?= 2

.PHONY: sol test plot all clean

sol: $(TARGET)
	$(TARGET) $(P) $(C)

$(TARGET): solutions.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) solutions.c -lm

test: $(TARGET)
	bash ./tests.sh

plot: test
	./plot.py

clean:
	rm -f compiled/*
	rm -rf compiled

all: clean plot