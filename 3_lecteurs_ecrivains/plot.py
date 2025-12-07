#!/usr/bin/env python3
import os
import pandas as pd
import matplotlib.pyplot as plt

script_dir = os.path.dirname(os.path.abspath(__file__))
compiled_dir = os.path.join(script_dir, "compiled")
csv_path = os.path.join(compiled_dir, "results.csv")

df = pd.read_csv(csv_path)

#nbr threads (lecteurs + écrivains)
df["TOTAL_THREADS"] = df["Lecteurs"] + df["Ecrivains"]

#calculs statistiques
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

graph_path = os.path.join(compiled_dir, "graph.pdf")
plt.savefig(graph_path)
