import pandas as pd
import matplotlib.pyplot as plt

# Read CSV
df = pd.read_csv("q2_data.csv")

plt.figure(figsize=(12, 7))

# Experimental probabilities
plt.plot(
    df["Trials"],
    df["FairProbability"],
    marker="o",
    linewidth=2.5,
    markersize=8,
    label="Fair Coin (Experimental)"
)

plt.plot(
    df["Trials"],
    df["BiasedProbability"],
    marker="s",
    linewidth=2.5,
    markersize=8,
    label="Biased Coin (Experimental)"
)

# Theoretical probabilities
plt.axhline(
    y=0.5,
    color="green",
    linestyle="--",
    linewidth=2,
    label="Fair Coin (Theoretical = 0.5)"
)

plt.axhline(
    y=0.7,
    color="red",
    linestyle="--",
    linewidth=2,
    label="Biased Coin (Theoretical = 0.7)"
)

# Use log scale because trials increase by powers of 10
plt.xscale("log")

plt.title(
    "Fair vs Biased Coin Toss Simulation",
    fontsize=18,
    fontweight="bold"
)

plt.xlabel("Number of Tosses (log scale)", fontsize=13)
plt.ylabel("Probability of Heads", fontsize=13)

plt.ylim(0.45, 0.75)

plt.grid(True, which="both", linestyle="--", alpha=0.6)

plt.legend(fontsize=11)

plt.tight_layout()

plt.savefig("coin_toss_comparison.png", dpi=300)

plt.show()