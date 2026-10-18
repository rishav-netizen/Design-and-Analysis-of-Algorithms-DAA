# Lab 09 — Greedy Design Paradigm

<div align="center">

![C](https://img.shields.io/badge/Language-C11-00599C?style=for-the-badge&logo=c)
![Progress](https://img.shields.io/badge/Progress-10%20of%2010%20complete-059669?style=for-the-badge)
![Focus](https://img.shields.io/badge/Focus-Greedy%20Algorithms-F59E0B?style=for-the-badge)

**Lab 09 · Week 9 · Design and Analysis of Algorithms**  
*Instructor: Dr. Ajaya Kumar Dash*

</div>

> This lab explores advanced algorithmic problem-solving techniques using the **Greedy Design Paradigm** (Difficulty level: Medium and Hard). It covers classical resource scheduling with deterioration, canonical prefix-free Huffman coding, retroactive fuel optimization, binary merge structures, slope-based candy allocation, string reorganization with spacing barriers, deviation minimization with priority queues, interval scheduling and coloring, optimal alphabetic binary search trees (Hu-Tucker algorithm), and an exploration of the open Shortest Common Superstring problem and its recent September 2026 disproof. Every procedure is implemented in C with clean functional decomposition, memory safety, proper input representations, formal exchange-argument optimality proofs, and rigorous time/space complexity derivations.

[← Repository home](../README.md) · [Lab 09 Assignment Sheet (PDF)](2026_Week9_DAA_Lab_09.pdf) · [📄 Lab 09 Solutions Report (Rishav Kumar)](DAA_Lab_09_Report_Rishav_Kumar.pdf) · [📄 Lab 09 Solutions Report (Rishav Shaw)](DAA_Lab_09_Report_Rishav_Shaw.pdf)

```text
Lab 09  █████████████████████  100%  10 / 10 questions complete
```

---

## 📋 Question Directory & Key Results

| Question | Topic | Key Result | Files |
| :---: | :--- | :--- | :---: |
| [Q1](Q1/README.md) | **Fractional Knapsack with Deterioration** | Adjacent exchange proof shows faster-decaying items ($\lambda$) take strict precedence; integrates effective density over time in $\mathcal{O}(n \log n)$ time. | [C](Q1/main.c) · [README](Q1/README.md) |
| [Q2](Q2/README.md) | **Canonical Huffman Coding** | Min-heap Huffman tree synthesis + canonical bit assignment ordered monotonically by length in $\mathcal{O}(n \log n)$ time, comparing with Shannon entropy. | [C](Q2/main.c) · [README](Q2/README.md) |
| [Q3](Q3/README.md) | **Minimum Refueling Stops (Reverse Greedy)** | Retroactive max-heap greedy vehicle simulation minimizing total refueling stops to target $D$ in $\mathcal{O}(n \log n)$ time and $\mathcal{O}(n)$ space. | [C](Q3/main.c) · [README](Q3/README.md) |
| [Q4](Q4/README.md) | **Minimum Cost to Connect Sticks** | Binary merge tree synthesis equivalent to Huffman external path length minimization using min-heap in $\mathcal{O}(n \log n)$ time with 64-bit precision. | [C](Q4/main.c) · [README](Q4/README.md) |
| [Q5](Q5/README.md) | **Candy Distribution Problem** | Bi-directional two-pass slope greedy scan resolving left and right relative constraints in optimal $\Theta(n)$ linear time and $\Theta(n)$ space. | [C](Q5/main.c) · [README](Q5/README.md) |
| [Q6](Q6/README.md) | **Reorganise String with K-Distance Apart** | Max-heap highest-frequency priority queue coupled with circular FIFO cooldown queue enforcing separation barrier in $\mathcal{O}(N \log |\Sigma|)$ time. | [C](Q6/main.c) · [README](Q6/README.md) |
| [Q7](Q7/README.md) | **Minimise Deviation in Array** | Two-way greedy reduction to monotonic descent via upper-bound odd doubling and max-heap iterative halving in $\mathcal{O}(n \log(\max A) \log n)$ time. | [C](Q7/main.c) · [README](Q7/README.md) |
| [Q8](Q8/README.md) | **Minimum Number of Meeting Rooms** | Interval graph coloring / earliest-start-time scan with min-heap of room end times proving chromatic number $\chi(G) = \omega(G) = d$ in $\mathcal{O}(n \log n)$. | [C](Q8/main.c) · [README](Q8/README.md) |
| [Q9](Q9/README.md) | **Hu-Tucker Greedy Simulation** | 3-phase optimal alphabetic binary tree construction (compatible pair greedy combination, level extraction, in-order planar reconstruction) in $\mathcal{O}(n^2)$ time. | [C](Q9/main.c) · [README](Q9/README.md) |
| [Q10](Q10/README.md) | **Greedy Superstring Conjecture** | Exploration of NP-hard Shortest Common Superstring problem, greedy maximum-overlap reduction, exact permutation audit, and analysis of the September 2026 ArXiv disproof ($9/4 = 2.25$). | [C](Q10/main.c) · [README](Q10/README.md) |

---

## 🛠️ Compilation & Quick Run

Every program can be compiled using GCC/Clang with standard C11 flags:

```bash
# Example: Compile and run Question 1
cd Q1
gcc -Wall -Wextra -std=c11 -O2 main.c -o main
./main

# Example: Compile and run Question 2 (requires math library)
cd ../Q2
gcc -Wall -Wextra -std=c11 -O2 main.c -lm -o main
./main
```

Each program provides an interactive menu:
- **Option 0:** Accepts custom manual user inputs with full step-by-step telemetry.
- **Option 1:** Automated random data generator sampling uniform test distributions.
- **Option 2 (Q10):** Preloaded benchmark and 2026 counterexample analysis.

---

## 📁 Supporting Files

- [2026_Week9_DAA_Lab_09.pdf](2026_Week9_DAA_Lab_09.pdf): Official Lab 9 assignment sheet from the course instructor.
- [DAA_Lab_09_Report_Rishav_Kumar.pdf](DAA_Lab_09_Report_Rishav_Kumar.pdf): Formal compiled academic lab report for Rishav Kumar (Roll: B125099).
- [DAA_Lab_09_Report_Rishav_Shaw.pdf](DAA_Lab_09_Report_Rishav_Shaw.pdf): Formal compiled academic lab report for Rishav Shaw (Roll: B125100).
- [folders.py](folders.py): Automation script for scaffolding lab folders.

Each question directory contains an independent `main.c` and a dedicated `README.md` containing formal problem descriptions, exchange arguments, mathematical proofs, Mermaid flowcharts, and verification traces.
