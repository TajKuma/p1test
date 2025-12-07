#!/bin/bash
set -euo pipefail

BINARY="./compiled/solutions"
OUTPUT="./compiled/results.csv"

# En-tête CSV adapté aux lecteurs/écrivains
echo "Lecteurs,Ecrivains,Temps(s)" > $OUTPUT

# Nombres totaux de threads à tester
TOTAL_THREADS_LIST="2 4 8 16 32"
N_MEASURES=5

for TOTAL in $TOTAL_THREADS_LIST; do
    # Répartir en lecteurs et écrivains
    L=$((TOTAL / 2))
    E=$((TOTAL / 2))

    for i in $(seq 1 $N_MEASURES); do
        echo "Running TOTAL=$TOTAL (L=$L E=$E) mesure $i..."

        # Mesure du temps réel
        /usr/bin/time -f "%e" -o tmp.time "$BINARY" "$L" "$E" >/dev/null

        TIME=$(cat tmp.time)

        # Ajout des données
        echo "$L,$E,$TIME" >> $OUTPUT
    done
done

rm -f tmp.time

echo "Mesures terminées. Résultats dans $OUTPUT"
