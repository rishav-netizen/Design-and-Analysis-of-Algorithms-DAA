#!/usr/bin/env python3
"""Plot timing data produced by the Question 2 merge-sort benchmark."""

from __future__ import annotations

import argparse
import csv
import math
from pathlib import Path

import matplotlib

# The script only writes a PNG, so a non-interactive backend works everywhere.
matplotlib.use("Agg")

import matplotlib.pyplot as plt


def read_results(csv_path: Path) -> tuple[list[int], list[float], list[float]]:
    """Load and validate the benchmark CSV file."""
    sizes: list[int] = []
    two_way: list[float] = []
    three_way: list[float] = []

    with csv_path.open(newline="", encoding="utf-8") as results_file:
        reader = csv.DictReader(results_file)
        required_columns = {"n", "two_way_seconds", "three_way_seconds"}

        if reader.fieldnames is None or not required_columns.issubset(reader.fieldnames):
            raise ValueError(
                "CSV must contain n, two_way_seconds, and three_way_seconds columns."
            )

        for row in reader:
            size = int(row["n"])
            classic_time = float(row["two_way_seconds"])
            modified_time = float(row["three_way_seconds"])

            if size < 2 or classic_time < 0.0 or modified_time < 0.0:
                raise ValueError("CSV contains an invalid benchmark value.")

            sizes.append(size)
            two_way.append(classic_time)
            three_way.append(modified_time)

    if not sizes:
        raise ValueError("CSV does not contain any benchmark rows.")

    return sizes, two_way, three_way


def scaled_n_log_n(sizes: list[int], measurements: list[float]) -> list[float]:
    """Scale n log n so its first value matches a measured curve."""
    growth = [size * math.log2(size) for size in sizes]
    scale = measurements[0] / growth[0] if growth[0] else 0.0
    return [scale * value for value in growth]


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Plot two-way and three-way merge-sort benchmark results."
    )
    parser.add_argument(
        "--input",
        type=Path,
        default=Path("data/benchmark_results.csv"),
        help="CSV produced by main.c (default: data/benchmark_results.csv)",
    )
    parser.add_argument(
        "--output",
        type=Path,
        default=Path("plots/merge_sort_complexity.png"),
        help="PNG destination (default: plots/merge_sort_complexity.png)",
    )
    arguments = parser.parse_args()

    sizes, two_way, three_way = read_results(arguments.input)
    n_log_n = [size * math.log2(size) for size in sizes]
    two_way_normalized = [time / growth for time, growth in zip(two_way, n_log_n)]
    three_way_normalized = [
        time / growth for time, growth in zip(three_way, n_log_n)
    ]

    figure, (timing_axis, normalized_axis) = plt.subplots(1, 2, figsize=(13, 5.5))
    figure.suptitle("Classic vs. Modified Three-Way Merge Sort", fontsize=15, fontweight="bold")

    timing_axis.plot(sizes, two_way, "o-", linewidth=2, label="Two-way merge sort")
    timing_axis.plot(
        sizes, three_way, "s-", linewidth=2, label="Three-way merge sort"
    )
    timing_axis.plot(
        sizes,
        scaled_n_log_n(sizes, two_way),
        "--",
        color="dimgray",
        linewidth=1.8,
        label="Scaled n log₂ n reference",
    )
    timing_axis.set_xscale("log", base=2)
    timing_axis.set_xlabel("Input size n")
    timing_axis.set_ylabel("Average CPU time (seconds)")
    timing_axis.set_title("Measured running time")
    timing_axis.grid(True, alpha=0.3)
    timing_axis.legend()

    normalized_axis.plot(
        sizes, two_way_normalized, "o-", linewidth=2, label="Two-way / (n log₂ n)"
    )
    normalized_axis.plot(
        sizes,
        three_way_normalized,
        "s-",
        linewidth=2,
        label="Three-way / (n log₂ n)",
    )
    normalized_axis.set_xscale("log", base=2)
    normalized_axis.set_xlabel("Input size n")
    normalized_axis.set_ylabel("Time / (n log₂ n)")
    normalized_axis.set_title("Normalized growth (roughly flat for Θ(n log n))")
    normalized_axis.grid(True, alpha=0.3)
    normalized_axis.legend()

    figure.text(
        0.5,
        0.01,
        "Each point is an average over repeated, identical-input trials."
        "  Timing is machine dependent.",
        ha="center",
        fontsize=9,
    )
    figure.tight_layout(rect=(0, 0.05, 1, 0.92))

    arguments.output.parent.mkdir(parents=True, exist_ok=True)
    figure.savefig(arguments.output, dpi=180, bbox_inches="tight")
    print(f"Saved plot to {arguments.output}")


if __name__ == "__main__":
    main()
