#!/usr/bin/env python3
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Fichier CSV généré par le script bash
CSV_FILE = "./compiled/results.csv"

# Lire le CSV
df = pd.read_csv(CSV_FILE)

# Calculer le nombre total de threads
df["TOTAL_THREADS"] = df["P"] + df["C"]

# Calculer moyenne et écart type pour chaque configuration
stats = df.groupby("TOTAL_THREADS")["Temps(s)"].agg(['mean', 'std']).reset_index()

# Tracer
plt.figure(figsize=(8,6))
plt.errorbar(
    stats["TOTAL_THREADS"],
    stats["mean"],
    yerr=stats["std"],
    fmt='o-',
    ecolor='red',
    capsize=5,
    label="Temps moyen ± écart type"
)

plt.title("Performance du programme Producteurs/Consommateurs")
plt.xlabel("Nombre total de threads (P+C)")
plt.ylabel("Temps d'exécution (s)")
plt.ylim(bottom=0)  # axe y commence à 0
plt.xticks(stats["TOTAL_THREADS"])
plt.grid(True)
plt.legend()

# Sauvegarder
plt.savefig("compiled/graph.pdf")