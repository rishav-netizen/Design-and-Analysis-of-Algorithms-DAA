import pandas as pd
import matplotlib.pyplot as plt

file = "randoms_count.csv"
df = pd.read_csv(file)

plt.figure(figsize=(14, 6))
plt.plot(
    df["Numbers"],
    df["Frequency"],
    marker="o",
    markersize=4,
    linewidth=1.5,
    label="Frequency"
)

plt.title("Frequency Distribution of Generated Random Numbers", fontsize=16)
plt.xlabel("Random Number", fontsize=12)
plt.ylabel("Frequency", fontsize=12)
plt.xticks(range(df["Numbers"].min(), df["Numbers"].max() + 1, 10), rotation=45)
plt.grid(True, linestyle="--", alpha=0.6)
plt.legend()
plt.tight_layout()

plt.savefig("frequency_distribution.png", dpi=300)
plt.show()