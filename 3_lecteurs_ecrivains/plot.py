#!/usr/bin/env python3
import pandas as pd
import matplotlib.pyplot as plt

CSV_FILE = "./compiled/results.csv"

# Lire le CSV
df = pd.read_csv(CSV_FILE)

# Nombre total de threads (lecteurs + écrivains)
df["TOTAL_THREADS"] = df["Lecteurs"] + df["Ecrivains"]

# Calcul statistiques
stats = df.groupby("TOTAL_THREADS")["Temps(s)"].agg(["mean", "std"]).reset_index()

#graphique
plt.figure(figsize=(8, 6))
plt.errorbar(
    stats["TOTAL_THREADS"],
    stats["mean"],
    yerr=stats["std"],
    fmt='o-',
    ecolor='red',
    capsize=5,
    label="Temps moyen ± écart type"
)

plt.title("Performance Lecteurs/Écrivains")
plt.xlabel("Nombre total de threads")
plt.ylabel("Temps d'exécution (s)")
plt.grid(True)
plt.xticks(stats["TOTAL_THREADS"])
plt.legend()

plt.savefig("compiled/graph.pdf")
