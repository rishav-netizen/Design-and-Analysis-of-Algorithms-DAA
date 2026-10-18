# Lab 04 - Applications of Sorting

<div align="center">

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Progress](https://img.shields.io/badge/Progress-6%20of%206%20complete-059669?style=for-the-badge)

**Lab 04 · Week 4 · Design and Analysis of Algorithms**

</div>

> This lab explores practical applications of sorting algorithms, including stable linear partitioning, multi-pointer searches, recursive combination searches with binary search, event-driven sweep-line algorithms, and interval merging.

[← Repository home](../README.md) · [Lab sheet (PDF)](2026_Week4_DAA_Lab_04.pdf)

```text
Lab 04  ████████████████████  100%  6 / 6 questions complete
```

| Question | Topic | Key result | Files |
| :---: | --- | --- | --- |
| [Q1](Q1/README.md) | Stable Color Sort (Application I) | Counting sort bucket placement preserves numerical stability in `O(n)` | [C](Q1/main.c) · [README](Q1/README.md) |
| [Q2](Q2/README.md) | Pair Sum from Two Sets (Application II) | Two-pointer scan on sorted sets finds pair `a + b = x` in `O(n log n)` | [C](Q2/main.c) · [README](Q2/README.md) |
| [Q3](Q3/README.md) | $k$-Sum Problem (Application III) | Recursive $(k-1)$ selection + binary search tests $k$-sum in `O(n^(k-1) log n)` | [C](Q3/main.c) · [README](Q3/README.md) |
| [Q4](Q4/README.md) | Simultaneous Party Guests (Application IV) | Event-driven sweep line finds peak simultaneous attendees in `O(n log n)` | [C](Q4/main.c) · [README](Q4/README.md) |
| [Q5](Q5/README.md) | Merge Overlapping Intervals (Application V) | Sort by start time and merge adjacent overlaps in `O(n log n)` | [C](Q5/main.c) · [README](Q5/README.md) |
| [Q6](Q6/README.md) | Point in Maximum Intervals (Application VI) | Event sweep line with inclusive endpoint tie-breaking in `O(n log n)` | [C](Q6/main.c) · [README](Q6/README.md) |

## Supporting file

- [folders.py](folders.py) creates the Q1-Q6 directory structure and starter templates for this lab.

Each question README includes the detailed problem statement, algorithmic approach, time/space complexity analysis, build commands, and sample execution traces. Start with the [Lab 04 assignment sheet](2026_Week4_DAA_Lab_04.pdf) for the original lab problems.
