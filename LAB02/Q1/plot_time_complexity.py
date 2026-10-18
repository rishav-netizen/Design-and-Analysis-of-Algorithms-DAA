#!/usr/bin/env python3
"""Create the theoretical worst-case growth chart for Question 1.

The six dictionary implementations have only three distinct worst-case growth
classes: O(1), O(log n), and O(n).  Implementations with the same bound are
grouped on a single line in each operation panel so that overlapping curves do
not hide one another.

Run from this directory:
    python3 plot_time_complexity.py

The default output is dictionary_time_complexity.png beside this file.  Use
--output to write the figure elsewhere.
"""

from __future__ import annotations

import argparse
import math
import sys
from pathlib import Path
from typing import Callable

try:
    import matplotlib

    # A non-interactive backend makes the script work in terminals and CI.
    matplotlib.use("Agg")
    import matplotlib.pyplot as plt
except ImportError as error:
    raise SystemExit(
        "Matplotlib is required to create the chart. Install it with:\n"
        "  python3 -m pip install matplotlib"
    ) from error


OUTPUT_FILE = Path(__file__).with_name("dictionary_time_complexity.png")

# Short labels keep legends readable; their full forms appear in the figure.
IMPLEMENTATIONS = {
    "UA": "Unsorted array",
    "SA": "Sorted array",
    "SUL": "Unsorted singly linked list",
    "SSL": "Sorted singly linked list",
    "DUL": "Unsorted doubly linked list",
    "DSL": "Sorted doubly linked list",
}

# These bounds follow the pointer/reference convention stated in README.md for
# Delete, Predecessor, and Successor.
OPERATION_COMPLEXITIES = {
    "Search": {
        "UA": "O(n)", "SA": "O(log n)", "SUL": "O(n)",
        "SSL": "O(n)", "DUL": "O(n)", "DSL": "O(n)",
    },
    "Insert": {
        "UA": "O(1)", "SA": "O(n)", "SUL": "O(1)",
        "SSL": "O(n)", "DUL": "O(1)", "DSL": "O(n)",
    },
    "Delete*": {
        "UA": "O(n)", "SA": "O(n)", "SUL": "O(n)",
        "SSL": "O(n)", "DUL": "O(1)", "DSL": "O(1)",
    },
    "Maximum": {
        "UA": "O(n)", "SA": "O(1)", "SUL": "O(n)",
        "SSL": "O(n)", "DUL": "O(n)", "DSL": "O(1)",
    },
    "Minimum": {
        "UA": "O(n)", "SA": "O(1)", "SUL": "O(n)",
        "SSL": "O(1)", "DUL": "O(n)", "DSL": "O(1)",
    },
    "Predecessor*": {
        "UA": "O(n)", "SA": "O(1)", "SUL": "O(n)",
        "SSL": "O(n)", "DUL": "O(n)", "DSL": "O(1)",
    },
    "Successor*": {
        "UA": "O(n)", "SA": "O(1)", "SUL": "O(n)",
        "SSL": "O(1)", "DUL": "O(n)", "DSL": "O(1)",
    },
}

CURVE_ORDER = ("O(1)", "O(log n)", "O(n)")
CURVE_STYLES = {
    "O(1)": {"color": "#0072B2", "linestyle": "-", "marker": "o"},
    "O(log n)": {"color": "#009E73", "linestyle": "--", "marker": "s"},
    "O(n)": {"color": "#D55E00", "linestyle": "-.", "marker": "^"},
}


def constant_growth(values: list[int]) -> list[float]:
    """Return a flat relative-work curve for O(1)."""
    return [1.0 for _ in values]


def logarithmic_growth(values: list[int]) -> list[float]:
    """Return a base-two logarithmic relative-work curve for O(log n)."""
    return [math.log2(value) for value in values]


def linear_growth(values: list[int]) -> list[float]:
    """Return a linear relative-work curve for O(n)."""
    return [float(value) for value in values]


GROWTH_FUNCTIONS: dict[str, Callable[[list[int]], list[float]]] = {
    "O(1)": constant_growth,
    "O(log n)": logarithmic_growth,
    "O(n)": linear_growth,
}


def grouped_implementations(bounds: dict[str, str]) -> dict[str, list[str]]:
    """Group implementation abbreviations by their shared complexity class."""
    groups = {curve: [] for curve in CURVE_ORDER}
    for abbreviation in IMPLEMENTATIONS:
        groups[bounds[abbreviation]].append(abbreviation)
    return groups


def create_chart(output_path: Path) -> None:
    """Render all seven operations into one readable, self-contained figure."""
    n_values = list(range(2, 257))
    figure, axes = plt.subplots(4, 2, figsize=(16, 16), sharex=True, sharey=True)
    plot_axes = axes.flat

    for operation, bounds in OPERATION_COMPLEXITIES.items():
        axis = next(plot_axes)
        groups = grouped_implementations(bounds)

        for curve in CURVE_ORDER:
            abbreviations = groups[curve]
            if not abbreviations:
                continue

            curve_values = GROWTH_FUNCTIONS[curve](n_values)
            style = CURVE_STYLES[curve]
            axis.plot(
                n_values,
                curve_values,
                label=f"{curve}: {', '.join(abbreviations)}",
                linewidth=2.2,
                markevery=32,
                markersize=4.5,
                **style,
            )

        axis.set_title(operation, fontweight="bold", pad=9)
        axis.set_xlim(2, 256)
        axis.set_ylim(0.85, 300)
        axis.set_yscale("log", base=2)
        axis.set_xticks((2, 32, 64, 128, 192, 256))
        axis.set_yticks((1, 2, 4, 8, 16, 32, 64, 128, 256))
        axis.grid(True, which="both", alpha=0.25, linewidth=0.7)
        axis.legend(loc="upper left", frameon=True, fontsize=8)

    # The unused eighth panel documents abbreviations and keeps the chart
    # self-explanatory when it is viewed independently from the README.
    information_axis = next(plot_axes)
    information_axis.axis("off")
    information_axis.text(
        0.03,
        0.96,
        "How to read this chart",
        transform=information_axis.transAxes,
        va="top",
        fontsize=13,
        fontweight="bold",
    )
    information_axis.text(
        0.03,
        0.82,
        (
            "Each panel groups implementations that have the same "
            "worst-case growth curve. A logarithmic y-axis keeps O(1), "
            "O(log n), and O(n) visible together.\n\n"
            "Abbreviations\n"
            "UA  Unsorted array\n"
            "SA  Sorted array\n"
            "SUL  Unsorted singly linked list\n"
            "SSL  Sorted singly linked list\n"
            "DUL  Unsorted doubly linked list\n"
            "DSL  Sorted doubly linked list\n\n"
            "* Delete, predecessor, and successor assume a pointer or "
            "reference to the target item is already available. If a key "
            "must first be found, add the cost of Search."
        ),
        transform=information_axis.transAxes,
        va="top",
        fontsize=10.5,
        linespacing=1.45,
        wrap=True,
    )

    figure.suptitle(
        "Dictionary ADT: Theoretical Worst-Case Growth by Representation",
        fontsize=18,
        fontweight="bold",
        y=0.985,
    )
    figure.supxlabel("Number of dictionary items, n", y=0.035, fontsize=12)
    figure.supylabel("Relative theoretical work (logarithmic scale)", x=0.02, fontsize=12)
    figure.tight_layout(rect=(0.035, 0.055, 1, 0.955))

    output_path.parent.mkdir(parents=True, exist_ok=True)
    figure.savefig(output_path, dpi=200, bbox_inches="tight", facecolor="white")
    plt.close(figure)


def parse_arguments() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Plot theoretical worst-case dictionary-operation growth."
    )
    parser.add_argument(
        "--output",
        type=Path,
        default=OUTPUT_FILE,
        help=f"PNG file to create (default: {OUTPUT_FILE.name})",
    )
    return parser.parse_args()


def main() -> int:
    arguments = parse_arguments()
    create_chart(arguments.output.resolve())
    print(f"Created {arguments.output.resolve()}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
