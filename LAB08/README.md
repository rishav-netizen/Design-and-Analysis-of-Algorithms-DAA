# Lab 08 — Dynamic Programming Design Paradigm

<div align="center">

![C](https://img.shields.io/badge/Language-C11-00599C?style=for-the-badge&logo=c)
![Progress](https://img.shields.io/badge/Progress-9%20of%209%20complete-059669?style=for-the-badge)
![Focus](https://img.shields.io/badge/Focus-Dynamic%20Programming-7C3AED?style=for-the-badge)

**Lab 08 · Week 8 · Design and Analysis of Algorithms**  
*Instructor: Dr. Ajaya Kumar Dash*

</div>

> This lab explores advanced algorithmic problem-solving techniques using the **Dynamic Programming** design paradigm (Difficulty level: Medium and Hard). It covers classical optimization problems, combinatorial counts, sequence alignment, subsequence extraction, binary search tree optimization, and trajectory analysis of an open mathematical problem. Every procedure is implemented in C with clean functional decomposition, memory safety, proper input representations, optimal substructure analyses, and rigorous time/space complexity proofs.

[← Repository home](../README.md) · [Lab 08 Assignment Sheet (PDF)](2026_Week8_DAA_Lab_08.pdf) · [📄 Lab 08 Solutions Report (Rishav Kumar)](DAA_Lab_08_Report_Rishav_Kumar.pdf)

```text
Lab 08  █████████████████████  100%  9 / 9 questions complete
```

---

## 📋 Question Directory & Key Results

| Question | Topic | Key Result | Files |
| :---: | :--- | :--- | :---: |
| [Q1](Q1/README.md) | **Minimum Coin Change** | Bottom-up DP finding minimum coins in $\mathcal{O}(n \cdot V)$ time and $\mathcal{O}(V)$ space with exact coin set reconstruction. | [C](Q1/main.c) · [README](Q1/README.md) |
| [Q2](Q2/README.md) | **Coin Change: Total Number of Ways** | Unbounded combination DP counting total distinct non-ordered combinations in $\mathcal{O}(n \cdot V)$ time and $\mathcal{O}(V)$ space. | [C](Q2/main.c) · [README](Q2/README.md) |
| [Q3](Q3/README.md) | **Longest Common Subsequence (LCS)** | 2D tabulation DP with directional traceback matrix in $\mathcal{O}(m \cdot n)$ reconstructing the actual string. | [C](Q3/main.c) · [README](Q3/README.md) |
| [Q4](Q4/README.md) | **Longest Increasing Subsequence (LIS)** | Dual implementation: $\mathcal{O}(n^2)$ tabulation DP + $\mathcal{O}(n \log n)$ patience sorting with predecessor reconstruction. | [C](Q4/main.c) · [README](Q4/README.md) |
| [Q5](Q5/README.md) | **Maximum Sum Increasing Subsequence (MSIS)** | Dynamic programming maximizing subsequence sum in $\mathcal{O}(n^2)$ time with element chain reconstruction. | [C](Q5/main.c) · [README](Q5/README.md) |
| [Q6](Q6/README.md) | **Edit Distance with Traceback Information** | Levenshtein distance DP in $\mathcal{O}(m \cdot n)$ generating full step-by-step transformation alignment (Insert, Delete, Replace, Match). | [C](Q6/main.c) · [README](Q6/README.md) |
| [Q7](Q7/README.md) | **Rod Cutting with Reconstruction** | Revenue maximization in $\mathcal{O}(n^2)$ time, outputting complete piece decomposition breakdown and revenue tables. | [C](Q7/main.c) · [README](Q7/README.md) |
| [Q8](Q8/README.md) | **Optimal Binary Search Trees (OBST)** | CLRS Section 15.5 dynamic programming computing expected cost $e$, weight $w$, root tables, and tree hierarchy in $\mathcal{O}(n^3)$. | [C](Q8/main.c) · [README](Q8/README.md) |
| [Q9](Q9/README.md) | **Collatz Conjecture ($3n+1$ Problem)** | Modular dynamical orbit simulator with 64-bit overflow prevention, dynamic trajectory arrays, and interval $[a, b]$ statistics. | [C](Q9/main.c) · [README](Q9/README.md) |

---

## 🛠️ Compilation & Quick Run

Every program can be compiled using GCC/Clang with standard C11 flags:

```bash
# Example: Compile and run Question 1
cd Q1
gcc -Wall -Wextra -std=c11 -O2 main.c -o main
./main

# Each program provides an interactive menu:
# Option 1: Runs automated validation and demonstration test suites
# Option 2: Accepts custom user inputs
```

For Question 9 (Collatz Conjecture), direct command-line arguments are also supported:
```bash
cd Q9
gcc -Wall -Wextra -std=c11 -O2 main.c -o main
./main 27         # Trajectory for n = 27
./main 1 100      # Interval analysis for [1, 100]
```

---

## 📁 Supporting Files

- [2026_Week8_DAA_Lab_08.pdf](2026_Week8_DAA_Lab_08.pdf): Official Lab 8 assignment sheet from the course instructor.
- [DAA_Lab_08_Report_Rishav_Kumar.pdf](DAA_Lab_08_Report_Rishav_Kumar.pdf): Formal compiled academic lab report for Rishav Kumar (Roll: B125099).
- [folders.py](folders.py): Automation script for workspace folder scaffolding.

Each question directory contains an independent `main.c` and a dedicated `README.md` containing formal problem descriptions, recurrence derivations, ASCII tables, Mermaid flowcharts, and verification traces.
