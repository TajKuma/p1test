#!/bin/bash

# Ce script mesure les performances du programme lecteurs/écrivains
# en variant le nombre TOTAL de threads : 2, 4, 8, 16, 32
# Les threads lecteurs et écrivains sont répartis équitablement.

PROGRAMME="./lecteurs_ecrivains"   # Nom de l'exécutable à tester
CSV="resultats_perf.csv"            # Fichier CSV de sortie

# En-tête du CSV
echo "threads_total,lecteurs,ecrivains,essai,temps_sec" > "$CSV"

# Liste des valeurs du nombre total de threads
THREADS_LIST="2 4 8 16 32"

for total in $THREADS_LIST; do

    # Répartition équitable
    lecteurs=$((total / 2))
    ecrivains=$((total / 2))

    for essai in $(seq 1 5); do

        tmpfile=$(mktemp)

        # Exécution silencieuse avec mesure du temps réel
        /usr/bin/time -f "%e" -o "$tmpfile" $PROGRAMME $lecteurs $ecrivains > /dev/null 2>&1

        temps=$(cat "$tmpfile")

        if [[ -z "$temps" ]]; then
            temps="NaN"
        fi

        echo "$total,$lecteurs,$ecrivains,$essai,$temps" >> "$CSV"

        rm -f "$tmpfile"

    done

done

echo "Mesures terminées. Résultats dans $CSV"