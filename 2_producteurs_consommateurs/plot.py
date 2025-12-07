#!/usr/bin/env python3
import os
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Récupération du csv
script_dir = os.path.dirname(os.path.abspath(__file__))
compiled_dir = os.path.join(script_dir, "compiled")
csv_path = os.path.join(compiled_dir, "results.csv")

df = pd.read_csv(csv_path)

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
graph_path = os.path.join(compiled_dir, "graph.pdf")
plt.savefig(graph_path)