CC = gcc
CFLAGS = -O2 -std=c11 -Wall -Wextra -pthread
TARGET = compiled/solutions
BUILD_DIR = compiled
N ?= 5  # valeur par défaut de N

.PHONY: all sol clean test plot dirs

# Compiler et lancer avec N philosophes
sol: $(TARGET)
	$(TARGET) $(N)

# Compiler l’exécutable
$(TARGET): solutions.c
	$(CC) $(CFLAGS) -o $(TARGET) solutions.c -lm

# Lancer tous les tests → results.csv dans compiled/
test: $(TARGET)
	./tests.sh

# Générer graph.pdf dans compiled/
plot: test
	python plot.py compiled/results.csv compiled/graph.pdf

# Nettoyer folder compiled/
clean:
	rm -f compiled/*

# Tout en une commande
all: clean sol test plot
