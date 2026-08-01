import pandas as pd
import matplotlib.pyplot as plt

# Read the generated CSV file
file = "q1_data.csv"
df = pd.read_csv(file)

plt.figure(figsize=(18, 10))

# Plot every function against n
for column in df.columns[1:]:
    plt.plot(df["n"], df[column], linewidth=2, label=column)

plt.title("Comparison of Function Growth Rates", fontsize=18, fontweight="bold")
plt.xlabel("n", fontsize=14)
plt.ylabel("Function Value", fontsize=14)

plt.yscale("log")  # Log scale so all curves are visible

plt.grid(True, which="both", linestyle="--", alpha=0.6)
plt.legend(loc="upper left", bbox_to_anchor=(1.02, 1), fontsize=9)

plt.tight_layout()
plt.savefig("growth_comparison.png", dpi=300, bbox_inches="tight")
plt.show()

