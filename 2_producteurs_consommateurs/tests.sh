#!/bin/bash
set -euo pipefail

BINARY="./compiled/solutions" 
OUTPUT="./compiled/results.csv"

# En-tête CSV
echo "P,C,TOTAL_ITEMS,Temps(s)" > $OUTPUT

# Nombres totaux de threads à tester
TOTAL_THREADS_LIST="2 4 8 16 32"
N_MEASURES=5

# Nombre d'éléments produit/consommé
TOTAL_ITEMS=131072

for TOTAL in $TOTAL_THREADS_LIST; do
    # Répartir les threads en P et C égaux
    P=$((TOTAL / 2))
    C=$((TOTAL / 2))

    for i in $(seq 1 $N_MEASURES); do
        echo "Running TOTAL=$TOTAL (P=$P C=$C) mesure $i..."
        
        # /usr/bin/time écrit le temps réel dans tmp.time
        # STDOUT du programme vers /dev/null
        /usr/bin/time -f "%e" -o tmp.time "$BINARY" "$P" "$C" >/dev/null
        
        # Lire le temps réel
        TIME=$(cat tmp.time)
        
        # Ajouter la mesure au CSV
        echo "$P,$C,$TOTAL_ITEMS,$TIME" >> $OUTPUT
    done
done

rm -f tmp.time

echo "Mesures terminées. Résultats dans $OUTPUT"