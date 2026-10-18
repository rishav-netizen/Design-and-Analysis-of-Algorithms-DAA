# Set 2: Algorithm Analysis and Complexities

This directory contains solutions for the computational complexity problems provided in the PDF assignment.

📄 **View the question set here:** [`2026_Week6_DAA_Lab_06.pdf`](../2026_Week6_DAA_Lab_06.pdf)

## Questions Overview

### [Q1: 1D Array Operations](./Q1/main.c)
Validates various 1D array operations on unsorted data and derives their worst-case complexities:
- **Maximum element**
- **First and second largest elements**
- **Mean, Median, Mode**
- **Standard Deviation**
- **Removing duplicates**
- **Reversing elements**
- **Partitioning around a random pivot**

### [Q2: 2D Square Matrix Operations](./Q2/main.c)
Validates operations on $n \times n$ square matrices and derives their worst-case computational complexities:
- **Matrix Addition & Multiplication**
- **Zero & Symmetric matrix checks**
- **Determinant computation** (using Gaussian Elimination)
- **In situ (in-place) Transpose**
- **Eigenvalue and Eigenvector estimation** (using the Power Method)

### [Q3: Convolution Operation](./Q3/main.c)
Implements the convolution of two vectors $A$ and $B$ (of sizes $m$ and $n$) using an efficient $O(n \log n)$ Divide and Conquer algorithm (utilizing the Fast Fourier Transform).

### [Q4: Sorting via Reversal Procedure](./Q4/main.c)
Solves the pancake sorting variation where the only operation allowed is `reverse(p, i, j)` with cost equal to the length $|j - i| + 1$. Achieves sorting in $O(n \log^2 n)$ total cost using a clever variation of Merge Sort relying heavily on block reversals.
