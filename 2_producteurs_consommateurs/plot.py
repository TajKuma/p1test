#!/usr/bin/env python3
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Récupération du csv
df = pd.read_csv("./compiled/results.csv")

# nbr de threads
df["TOTAL_THREADS"] = df["P"] + df["C"]

# moyenne et l'écart type
stats = df.groupby("TOTAL_THREADS")["Temps(s)"].agg(['mean', 'std']).reset_index()

# plot
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
plt.ylim(bottom=0)
plt.xticks(stats["TOTAL_THREADS"])
plt.grid(True)
plt.legend()
plt.savefig("compiled/graph.pdf")