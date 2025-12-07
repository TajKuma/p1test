#!/usr/bin/env python3
import pandas as pd
import matplotlib.pyplot as plt

# Récupération du csv
df = pd.read_csv("./compiled/results.csv")

# moyenne et l'écart-type
stats = df.groupby("N")["Temps(s)"].agg(["mean", "std"]).reset_index()

# plot
plt.figure(figsize=(8,5))
plt.errorbar(
    stats["N"],        # X = nombre de threads
    stats["mean"],     # Y = temps moyen
    yerr=stats["std"], # barres d'erreur = écart-type
    fmt='o-',          # points reliés par une ligne
    capsize=5,         # petites barres aux extrémités
    color='blue',
    label="Temps moyen ± écart-type"
)

plt.xlabel("Nombre de threads")
plt.ylabel("Temps d'exécution (s)")
plt.title("Temps d'exécution en fonction du nombre de threads")
plt.xticks(stats["N"])
plt.ylim(bottom=0)
plt.grid(True, linestyle='--', alpha=0.5)
plt.legend()
plt.tight_layout()
plt.savefig("compiled/graph.pdf")