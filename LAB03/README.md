# Lab 03 - Divide and Conquer

<div align="center">

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Progress](https://img.shields.io/badge/Progress-6%20of%206%20complete-059669?style=for-the-badge)

**Lab 03 · Week 3 · Design and Analysis of Algorithms**

</div>

> This lab applies divide-and-conquer techniques to searching, selection, and matrix multiplication, then concludes with a selection-sort correctness analysis.

[← Repository home](../README.md) · [Lab sheet (PDF)](2026_Week3_DAA_Lab_03.pdf)

```text
Lab 03  ████████████████████  100%  6 / 6 questions complete
```

| Question | Topic | Key result | Files |
| --- | --- | --- | --- |
| [Q1](Q1/README.md) | Binary vs. ternary search | Both are `O(log n)`; binary search uses fewer comparisons on average | [benchmark C](Q1/fun.c) · [interactive C](Q1/main.c) · [README](Q1/README.md) |
| [Q2](Q2/README.md) | Defective coin search | Halving the candidates takes `O(log n)` balance operations | [C](Q2/main.c) · [README](Q2/README.md) |
| [Q3](Q3/README.md) | Minimum and maximum | Divide and conquer uses about `3n/2` comparisons | [C](Q3/main.c) · [README](Q3/README.md) |
| [Q4](Q4/README.md) | Strassen matrix multiplication | `O(n^log2(7))`, approximately `O(n^2.81)` | [C](Q4/main.c) · [README](Q4/README.md) |
| [Q5](Q5/README.md) | Special-pattern matrix multiplication | Exploits recursive block symmetry in `O(n^2)` | [C](Q5/main.c) · [README](Q5/README.md) |
| [Q6](Q6/README.md) | Selection sort and loop invariant | Always makes `n(n - 1) / 2` comparisons | [C](Q6/main.c) · [README](Q6/README.md) |

## Supporting file

- [folders.py](folders.py) creates the Q1-Q6 folder and starter-file layout used for this lab.

Each question README includes the question summary, build command, and complexity discussion. Start with the [Lab 03 assignment sheet](2026_Week3_DAA_Lab_03.pdf) for the original questions.
