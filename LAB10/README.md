# Lab 10 — Graphs & Disjoint Set Union (DSU)

<div align="center">

![C](https://img.shields.io/badge/Language-C11-00599C?style=for-the-badge&logo=c)
![Progress](https://img.shields.io/badge/Progress-5%20of%205%20complete-059669?style=for-the-badge)
![Focus](https://img.shields.io/badge/Focus-Graphs%20%26%20DSU-F59E0B?style=for-the-badge)

**Lab 10 · Week 10 · Design and Analysis of Algorithms**  
*Instructor: Dr. Ajaya Kumar Dash*

</div>

> This lab explores advanced graph algorithms and dynamic connectivity paradigms centered on the **Disjoint Set Union (DSU / Union-Find)** data structure, graph representations, and connected component maintenance (Difficulty level: Medium and Hard). It covers online graph-bipartiteness testing with parity potentials, dynamic 2D grid component tracking (Number of Islands II) via coordinate flattening, size-constrained maximum weight component optimization with lazy priority queues, reverse time-step offline graph component analysis under vertex deletions, and lexicographically smallest permutation synthesis through symmetric group transpositions on connected components. Every procedure is implemented in C11 with rigorous mathematical foundations, formal exchange and transitivity proofs, asymptotic complexity derivations, and interactive console verification.

[← Repository home](../README.md) · [Lab 10 Assignment Sheet (PDF)](2026_Week10_DAA_Lab_10.pdf)

```text
Lab 10  █████████████████████  100%  5 / 5 questions complete
```

---

## 📋 Question Directory & Key Results

| Question | Topic | Key Result | Files |
| :---: | :--- | :--- | :---: |
| [Q1](Q1/README.md) | **Online Graph-Bipartiteness Testing** | Maintains 2-coloring potentials in DSU forest; admits online edge arrivals, rejects odd cycles, and traces odd cycles via BFS in $\mathcal{O}(M \cdot \alpha(V))$ time. | [C](Q1/main.c) · [README](Q1/README.md) |
| [Q2](Q2/README.md) | **Dynamic Connected Components in a Grid** | Number of Islands II via canonical 2D $\to$ 1D coordinate flattening $\phi(r, c) = r \cdot C + c$ and 4-neighborhood DSU edge relaxation in $\mathcal{O}(R \cdot C + k \cdot \alpha(R \cdot C))$ time. | [C](Q2/main.c) · [README](Q2/README.md) |
| [Q3](Q3/README.md) | **Maximum Weight Component with Size Constraints** | Augmented DSU tracking sizes, weights, and version stamps coupled with a lazy max-heap to dynamically track max vertex weight among components with $|C| \le K$ in $\mathcal{O}(M \log(V + M))$ time. | [C](Q3/main.c) · [README](Q3/README.md) |
| [Q4](Q4/README.md) | **Reverse Time-Step DSU Application** | Offline time-reversal paradigm inverting destructive vertex deletions into incremental activations; maintains connected component sums in $\mathcal{O}((V + E) \cdot \alpha(V))$ optimal time. | [C](Q4/main.c) · [README](Q4/README.md) |
| [Q5](Q5/README.md) | **Lexicographically Smallest Permutation** | Generates full symmetric group $S_{|C|}$ via allowable swap transpositions on connected index components; sorts component values greedily in $\mathcal{O}(M \cdot \alpha(n) + n \log n)$ time. | [C](Q5/main.c) · [README](Q5/README.md) |

---

## 🛠️ Compilation & Quick Run

Every program can be compiled using GCC/Clang with standard C11 flags:

```bash
# Example: Compile and run Question 1
cd Q1
gcc -Wall -Wextra -std=c11 -O2 main.c -o main
./main

# Example: Compile and run Question 2
cd ../Q2
gcc -Wall -Wextra -std=c11 -O2 main.c -o main
./main
```

Each program provides an interactive menu:
- **Option 0:** Custom manual user input with step-by-step telemetry, ASCII grid visualizations, and cycle traces.
- **Option 1:** Automated random data generator sampling uniform test distributions.

---

## 📁 Supporting Files

- [2026_Week10_DAA_Lab_10.pdf](2026_Week10_DAA_Lab_10.pdf): Official Lab 10 assignment sheet from the course instructor.
- [folders.py](folders.py): Automation script for scaffolding lab folders.
- [report.typ](report.typ): Academic report source written in Typst.

Each question directory contains an independent `main.c` and a dedicated `README.md` containing formal problem descriptions, algebraic group and topological proofs, Mermaid diagrams, and verification traces.
