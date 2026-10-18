# Question 2: 2D Square Matrix Operations and Complexities

## 📌 Problem Overview
Given a square matrix with $n$ rows and $n$ columns, write a C program to validate multiple linear algebra algorithms and derive their worst-case computational complexity.

---

## 🛠️ Implementation Details
The source code in [`main.c`](./main.c) encompasses matrix logic:
1. **Dynamic Matrix Allocation:** Using double pointers to allocate row/col blocks safely.
2. **Advanced Math Procedures:** 
   - **Gaussian Elimination** is deployed to transform the matrix to an upper triangle for $\mathcal{O}(n^3)$ determinant extraction.
   - **The Power Method** is used to iteratively converge upon the dominant Eigenvalue and Eigenvector.
3. **In-place transpositions:** Directly swaps mirroring elements against the diagonal.

---

## ⚙️ Compilation & Execution

Math libraries are leveraged for the vector normalization in the Power Method.

```bash
# Compile
gcc -o main main.c -lm

# Run
./main
```

---


### 📤 Sample Output
```text
Enter dimension n for n x n matrices: 2

Matrix A:
Enter elements for Matrix A (2x2):
A[0][0]: 1
A[0][1]: 2
A[1][0]: 3
A[1][1]: 4

Matrix B:
Enter elements for Matrix B (2x2):
B[0][0]: 5
B[0][1]: 6
B[1][0]: 7
B[1][1]: 8

--- 2D Square Matrix Operations ---
...
Enter your choice: 1
Result of A + B:
{6.00, 8.00}
{10.00, 12.00}

--- 2D Square Matrix Operations ---
...
Enter your choice: 5
Determinant of A: -2.0000
Determinant of B: -2.0000
...
```

---

## 📊 Complexity Summary & Analysis

| Operation | Worst-Case Time Complexity | Space Complexity | Description |
| :--- | :---: | :---: | :--- |
| **(i) Matrix Addition** | $\mathcal{O}(n^2)$ | $\mathcal{O}(n^2)$ | Direct cell-by-cell addition iterating through both dimensions. |
| **(ii) Matrix Multiplication**| $\mathcal{O}(n^3)$ | $\mathcal{O}(n^2)$ | Standard dot-product of rows and columns (triple nested loop). |
| **(iii) Zero Matrix Check** | $\mathcal{O}(n^2)$ | $\mathcal{O}(1)$ | Linear pass returning early if any non-zero element is found. |
| **(iv) Symmetric Check** | $\mathcal{O}(n^2)$ | $\mathcal{O}(1)$ | Checking if $M[i][j] == M[j][i]$ for all elements. |
| **(v) Determinant** | $\mathcal{O}(n^3)$ | $\mathcal{O}(n^2)$ | Modifying the matrix via Gaussian Elimination to fetch the diagonal product. |
| **(vi) Transpose (In situ)** | $\mathcal{O}(n^2)$ | $\mathcal{O}(1)$ | Swapping $M[i][j]$ with $M[j][i]$ in place, avoiding extraneous allocations. |
| **(vii) Eigenvalue/Vector** | $\mathcal{O}(k \cdot n^2)$ | $\mathcal{O}(n)$ | Power Iteration method converging over $k$ iterations doing matrix-vector multiplications. |
