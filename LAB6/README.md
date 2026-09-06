# Lab 06 - Dynamic Programming & Algorithm Analysis

<div align="center">

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Progress](https://img.shields.io/badge/Progress-8%20of%208%20complete-059669?style=for-the-badge)

**Lab 06 · Week 6 · Design and Analysis of Algorithms**

</div>

> This lab explores Dynamic Programming algorithms (Fibonacci, 0/1 Knapsack, Longest Common Subsequence, and Matrix Chain Multiplication) alongside rigorous asymptotic complexity analysis for 1D arrays, 2D matrices, Fast Fourier Transform (FFT) convolutions, and block reversal sorting.

[← Repository home](../README.md) · [Questions sheet (Image)](questions.png) · [Questions sheet (PDF)](2026_Week6_DAA_Lab_06.pdf)

```text
Lab 06  ████████████████████  100%  8 / 8 questions complete
```

### Set 1: Dynamic Programming (Image)
| Question | Topic | Key Result | Files |
| :---: | --- | --- | --- |
| [Q1](Set1/Q1/README.md) | N-th Fibonacci Number | Dynamic Programming (Tabulation) computes $F(n)$ efficiently in $\mathcal{O}(n)$ time | [C](Set1/Q1/main.c) · [README](Set1/Q1/README.md) |
| [Q2](Set1/Q2/README.md) | 0/1 Knapsack Problem | Tabulation DP finds optimal items subset in $\mathcal{O}(n \times W)$ time | [C](Set1/Q2/main.c) · [README](Set1/Q2/README.md) |
| [Q3](Set1/Q3/README.md) | Longest Common Subsequence | 2D DP grid determines LCS string length & sequence in $\mathcal{O}(m \times n)$ | [C](Set1/Q3/main.c) · [README](Set1/Q3/README.md) |
| [Q4](Set1/Q4/README.md) | Matrix Chain Multiplication | DP optimization dictates best parenthesization grouping in $\mathcal{O}(N^3)$ | [C](Set1/Q4/main.c) · [README](Set1/Q4/README.md) |

### Set 2: Algorithm Analysis & Complexities (PDF)
| Question | Topic | Key Result | Files |
| :---: | --- | --- | --- |
| [Q1](Set2/Q1/README.md) | 1D Array Operations | Implements statistics functions and partitions deriving worst-case $\mathcal{O}(n)$ to $\mathcal{O}(n^2)$ | [C](Set2/Q1/main.c) · [README](Set2/Q1/README.md) |
| [Q2](Set2/Q2/README.md) | 2D Square Matrix Operations | Validates complex matrix algorithms including Gaussian Determinant in $\mathcal{O}(n^3)$ | [C](Set2/Q2/main.c) · [README](Set2/Q2/README.md) |
| [Q3](Set2/Q3/README.md) | FFT Vector Convolution | Divide & Conquer Fast Fourier Transform achieves convolution in $\mathcal{O}(n \log n)$ | [C](Set2/Q3/main.c) · [README](Set2/Q3/README.md) |
| [Q4](Set2/Q4/README.md) | Block Reversal Merge Sort | Hybrid Merge Sort sorts arrays solely via sequence flips in $\mathcal{O}(n \log^2 n)$ | [C](Set2/Q4/main.c) · [README](Set2/Q4/README.md) |

## 📂 Directory Structure

```text
LAB6/
├── 2026_Week6_DAA_Lab_06.pdf
├── questions.png
├── folders.py
├── README.md
├── Set1/
│   ├── README.md
│   ├── Q1/
│   │   ├── README.md
│   │   └── main.c
│   ├── Q2/
│   │   ├── README.md
│   │   └── main.c
│   ├── Q3/
│   │   ├── README.md
│   │   └── main.c
│   └── Q4/
│       ├── README.md
│       └── main.c
└── Set2/
    ├── README.md
    ├── Q1/
    │   ├── README.md
    │   └── main.c
    ├── Q2/
    │   ├── README.md
    │   └── main.c
    ├── Q3/
    │   ├── README.md
    │   └── main.c
    └── Q4/
        ├── README.md
        └── main.c
```

## Supporting file

- [folders.py](folders.py): Directory setup and scaffolding script for Lab 6.

Each question's README includes the detailed problem statement, algorithmic approach, time/space complexity analysis, build commands, and sample execution traces. Refer to [questions.png](questions.png) and [2026_Week6_DAA_Lab_06.pdf](2026_Week6_DAA_Lab_06.pdf) for the original lab assignment prompts.
