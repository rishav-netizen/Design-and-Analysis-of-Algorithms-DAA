#!/usr/bin/env python3
"""Benchmark and plot the two solutions for Question 3.

The script compiles the two C programs in a temporary directory, collects CSV
timings from their --benchmark modes, verifies every reported output is sorted,
and saves both a CSV data file and a PNG figure beside this script by default.
"""

from __future__ import annotations

import argparse
import csv
import math
import os
import subprocess
import sys
import tempfile
from pathlib import Path


ROOT = Path(__file__).resolve().parent
# Keep Matplotlib's font/config cache in a writable temporary location. This
# avoids a noisy warning on systems where the home-directory cache is locked.
os.environ.setdefault("MPLCONFIGDIR", str(Path(tempfile.gettempdir()) / "q3_matplotlib"))
PROGRAMS = {
    "Sequential merge": ROOT / "01_sequentialMerge" / "main.c",
    "Balanced pairwise merge": ROOT / "02_balancedPairwiseMerge" / "main.c",
}


def positive_integer(value: str) -> int:
    """Parse a command-line value that must be a positive integer."""
    try:
        number = int(value)
    except ValueError as error:
        raise argparse.ArgumentTypeError("must be an integer") from error
    if number <= 0:
        raise argparse.ArgumentTypeError("must be positive")
    return number


def compile_program(compiler: str, source: Path, executable: Path) -> None:
    """Compile one benchmark executable with strict C11 warnings enabled."""
    command = [
        compiler,
        "-std=c11",
        "-O2",
        "-Wall",
        "-Wextra",
        "-Werror",
        str(source),
        "-o",
        str(executable),
    ]
    subprocess.run(command, check=True)


def read_benchmark(executable: Path, k: int, n: int, trials: int) -> dict[str, object]:
    """Run a C program once and return its single CSV record."""
    completed = subprocess.run(
        [str(executable), "--benchmark", str(k), str(n), str(trials)],
        check=True,
        text=True,
        capture_output=True,
    )
    rows = list(csv.DictReader(completed.stdout.splitlines()))
    if len(rows) != 1:
        raise RuntimeError(f"Expected one CSV timing row from {executable}, got {len(rows)}.")

    row = rows[0]
    if row.get("sorted") != "true":
        raise RuntimeError(f"{executable.name} produced an unsorted result.")

    return {
        "k": int(row["k"]),
        "n": int(row["n"]),
        "total_elements": int(row["total_elements"]),
        "average_seconds": float(row["average_seconds"]),
        "sorted": row["sorted"],
    }


def write_csv(rows: list[dict[str, object]], destination: Path) -> None:
    """Save the measurements in a spreadsheet-friendly format."""
    with destination.open("w", newline="", encoding="utf-8") as file:
        writer = csv.DictWriter(
            file,
            fieldnames=["method", "k", "n", "total_elements", "average_seconds", "sorted"],
        )
        writer.writeheader()
        writer.writerows(rows)


def create_plot(rows: list[dict[str, object]], destination: Path) -> None:
    """Create raw-runtime and normalized-growth plots without requiring NumPy."""
    try:
        import matplotlib

        matplotlib.use("Agg")
        import matplotlib.pyplot as plt
    except ModuleNotFoundError as error:
        raise RuntimeError(
            "Plotting requires matplotlib. Install it with: python3 -m pip install matplotlib"
        ) from error

    methods = sorted({str(row["method"]) for row in rows})
    grouped = {method: sorted((row for row in rows if row["method"] == method),
                              key=lambda row: int(row["k"])) for method in methods}

    figure, (runtime_axis, normalized_axis) = plt.subplots(1, 2, figsize=(13, 5.4))
    colors = {"Sequential merge": "#d97706", "Balanced pairwise merge": "#2563eb"}
    normalizers = {
        "Sequential merge": lambda row: int(row["n"]) * int(row["k"]) ** 2,
        "Balanced pairwise merge": lambda row: int(row["n"]) * int(row["k"]) * math.log2(int(row["k"])),
    }
    labels = {
        "Sequential merge": r"sequential: $\Theta(nk^2)$",
        "Balanced pairwise merge": r"balanced: $\Theta(nk\log_2 k)$",
    }

    for method, measurements in grouped.items():
        k_values = [int(row["k"]) for row in measurements]
        seconds = [float(row["average_seconds"]) for row in measurements]
        if any(value <= 0 for value in seconds):
            raise RuntimeError(
                "A timing was zero. Increase --elements-per-array or --trials before plotting."
            )

        runtime_axis.plot(
            k_values,
            seconds,
            marker="o",
            linewidth=2.2,
            color=colors.get(method),
            label=labels.get(method, method),
        )
        normalized_axis.plot(
            k_values,
            [time / normalizers[method](row) for time, row in zip(seconds, measurements)],
            marker="o",
            linewidth=2.2,
            color=colors.get(method),
            label=labels.get(method, method),
        )

    runtime_axis.set_title("Measured running time")
    runtime_axis.set_xlabel("Number of sorted arrays, k")
    runtime_axis.set_ylabel("Average CPU time (seconds)")
    runtime_axis.set_xscale("log", base=2)
    runtime_axis.set_yscale("log")
    runtime_axis.grid(True, which="both", alpha=0.25)
    runtime_axis.legend()

    normalized_axis.set_title("Runtime normalized by predicted growth")
    normalized_axis.set_xlabel("Number of sorted arrays, k")
    normalized_axis.set_ylabel("seconds / growth term")
    normalized_axis.set_xscale("log", base=2)
    normalized_axis.grid(True, which="both", alpha=0.25)
    normalized_axis.legend()

    figure.suptitle("Question 3 — Merging k Sorted Arrays", fontsize=15, fontweight="bold")
    figure.text(
        0.5,
        0.01,
        "Each input array contains the same n elements; every output was verified sorted.",
        ha="center",
        color="#475569",
    )
    figure.tight_layout(rect=(0, 0.04, 1, 0.94))
    figure.savefig(destination, dpi=180, bbox_inches="tight")
    plt.close(figure)


def parse_arguments() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Compile, benchmark, and plot both Question 3 merge strategies."
    )
    parser.add_argument(
        "--elements-per-array",
        type=positive_integer,
        default=8000,
        help="n: elements in every input array (default: 8000)",
    )
    parser.add_argument(
        "--trials",
        type=positive_integer,
        default=5,
        help="timing repetitions per point (default: 5)",
    )
    parser.add_argument(
        "--k-values",
        nargs="+",
        type=positive_integer,
        default=[2, 4, 8, 16, 32, 64],
        help="positive k values to benchmark (default: 2 4 8 16 32 64)",
    )
    parser.add_argument(
        "--compiler",
        default="cc",
        help="C compiler command (default: cc)",
    )
    parser.add_argument(
        "--csv-output",
        type=Path,
        default=ROOT / "benchmark_results.csv",
        help="where to save raw timing data",
    )
    parser.add_argument(
        "--plot-output",
        type=Path,
        default=ROOT / "merge_k_arrays_complexity.png",
        help="where to save the PNG chart",
    )
    return parser.parse_args()


def main() -> int:
    arguments = parse_arguments()
    if any(k < 2 for k in arguments.k_values):
        print("Every k value must be at least 2 for the log(k) comparison.", file=sys.stderr)
        return 2

    arguments.csv_output.parent.mkdir(parents=True, exist_ok=True)
    arguments.plot_output.parent.mkdir(parents=True, exist_ok=True)
    measurements: list[dict[str, object]] = []

    try:
        with tempfile.TemporaryDirectory(prefix="q3_merge_benchmark_") as directory:
            build_directory = Path(directory)
            executables: dict[str, Path] = {}
            for method, source in PROGRAMS.items():
                executable = build_directory / source.parent.name
                compile_program(arguments.compiler, source, executable)
                executables[method] = executable

            for method, executable in executables.items():
                for k in arguments.k_values:
                    row = read_benchmark(
                        executable, k, arguments.elements_per_array, arguments.trials
                    )
                    row["method"] = method
                    measurements.append(row)
                    print(
                        f"{method:24} k={k:>3}, n={arguments.elements_per_array:>6}: "
                        f"{float(row['average_seconds']):.6f} s"
                    )

        write_csv(measurements, arguments.csv_output)
        create_plot(measurements, arguments.plot_output)
    except (OSError, RuntimeError, subprocess.CalledProcessError, ValueError) as error:
        print(f"Benchmark failed: {error}", file=sys.stderr)
        return 1

    print(f"\nSaved raw data: {arguments.csv_output}")
    print(f"Saved plot:     {arguments.plot_output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
