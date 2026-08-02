import pandas as pd
import matplotlib.pyplot as plt

# Read the generated CSV file
file = "steps_count.csv"
df = pd.read_csv(file)

plt.figure(figsize=(18, 10))

# Plot every function against n
for column in df.columns[1:]:
    plt.plot(df["n"], df[column], linewidth=2, label=column)

plt.title("Steps taken to move n disks", fontsize=18, fontweight="bold")
plt.xlabel("Number of Disks", fontsize=14)
plt.ylabel("Steps", fontsize=14)


plt.grid(True, which="both", linestyle="--", alpha=0.6)
plt.legend(loc="upper left", bbox_to_anchor=(1.02, 1), fontsize=9)

plt.tight_layout()
plt.savefig("steps_graph.png", dpi=300, bbox_inches="tight")
plt.show()

