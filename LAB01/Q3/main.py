import pandas as pd
import matplotlib.pyplot as plt

# Load CSV file
df = pd.read_csv("q3_data.csv")

# Create figure
plt.figure(figsize=(10, 6))

# Plot both Bubble Sort variants
plt.plot(
    df["ArraySize"],
    df["OptimizedComparisons"],
    marker="o",
    linewidth=2,
    label="Optimized Bubble Sort"
)

plt.plot(
    df["ArraySize"],
    df["NormalComparisons"],
    marker="s",
    linewidth=2,
    label="Normal Bubble Sort"
)

# Graph formatting
plt.title("Bubble Sort Comparison", fontsize=16, fontweight="bold")
plt.xlabel("Array Size (n)", fontsize=12)
plt.ylabel("Number of Comparisons", fontsize=12)

plt.xticks(df["ArraySize"])
plt.grid(True, linestyle="--", alpha=0.7)
plt.legend()
plt.tight_layout()

# Save graph
plt.savefig("q3_graph.png", dpi=300)

# Display graph
plt.show()