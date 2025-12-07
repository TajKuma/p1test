#!/bin/bash
set -euo pipefail

BINARY="./compiled/solutions"    
OUTPUT="./compiled/results.csv"

# En-tête CSV
echo "N,Temps(s)" > "$OUTPUT"

# Configurations testées
TOTAL_THREADS_LIST="2 4 8 16 32"
N_MEASURES=5

for N in $TOTAL_THREADS_LIST; do
    for i in $(seq 1 $N_MEASURES); do
        echo "Running N=$N mesure $i..."

        # Mesure du temps réel en secondes avec précision maximale POSIX
        /usr/bin/time -f "%e" -o tmp.time "$BINARY" "$N" >/dev/null

        TIME=$(cat tmp.time)

        # Ajout au CSV
        echo "$N,$TIME" >> "$OUTPUT"
    done
done

rm -f tmp.time

echo "Mesures terminées. Résultats dans $OUTPUT"