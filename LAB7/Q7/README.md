# Q7 — Matrix Chain Multiplication (MCM)

## 📌 Problem Statement

> **[Matrix Chain Multiplication (MCM) problem]**  
> Consider the matrix chain multiplication problem. Write a program in C to implement the dynamic programming solution of the MCM problem in order to find the minimum number of scalar multiplications involved and the corresponding ordering to obtain the final result.

```text
Matrices: A1, A2, ..., An
Dimensions: A_i has dimension p_{i-1} x p_i

Goal: Parenthesize the product A1 x A2 x ... x An
to minimize total scalar multiplications.
```

---

## 💡 Dynamic Programming Formulation

### 1. Optimal Substructure
Let $A_{i..j} = A_i \times A_{i+1} \times \dots \times A_j$.  
Any parenthesization must split the product at some position $k$ ($i \le k < j$):
$$A_{i..j} = (A_{i..k}) \times (A_{k+1..j})$$

The cost of computing $A_{i..j}$ consists of:
1. Cost of multiplying subchain $A_{i..k}$
2. Cost of multiplying subchain $A_{k+1..j}$
3. Cost of multiplying the two resulting matrices: $p_{i-1} \cdot p_k \cdot p_j$ scalar multiplications.

### 2. Recurrence Relation
Let $m[i][j]$ be the minimum number of scalar multiplications needed to compute $A_{i..j}$.

$$\boxed{m[i][j] = \begin{cases} 0 & \text{if } i = j \\ \min\limits_{i \le k < j} \Big( m[i][k] + m[k+1][j] + p_{i-1} \cdot p_k \cdot p_j \Big) & \text{if } i < j \end{cases}}$$

We also record the optimal split index $k$ in table $s[i][j]$:
$$s[i][j] = \arg\min_{i \le k < j} \Big( m[i][k] + m[k+1][j] + p_{i-1} \cdot p_k \cdot p_j \Big)$$

---

## 🛠️ Implementation Details

In [`main.c`](file:///Users/rishav07/Documents/college/SEM3/DAA/LAB7/Q7/main.c):
1. **Bottom-Up Tabulation:**
   Fills table $m$ in order of increasing chain length $L = 2, 3, \dots, n$.
2. **Optimal Parenthesization Reconstruction:**
   `PrintOptimalParens(i, j)` recursively traverses table $s$ to display the parenthesized expression:
   - If $i == j$: prints $A_i$.
   - Else: prints `(` + `PrintOptimalParens(i, s[i][j])` + ` x ` + `PrintOptimalParens(s[i][j] + 1, j)` + `)`.

---

## ⏱️ Complexity Analysis

| Metric | Complexity | Explanation |
| :--- | :---: | :--- |
| **Time Complexity** | $\mathcal{O}(n^3)$ | Three nested loops: chain length $L$, starting index $i$, and split index $k$. |
| **Space Complexity** | $\mathcal{O}(n^2)$ | Tables $m[n][n]$ and $s[n][n]$. |

---

## ⚙️ Compilation & Execution

```bash
# Compile
gcc -Wall -Wextra -O2 main.c -o main

# Run
./main
```

---

## 🧪 Sample Output (Benchmark Chain $p = [30, 35, 15, 5, 10, 20, 25]$)

```text
--- Matrix Chain Multiplication (MCM) ---
Using standard matrix dimensions: 30 35 15 5 10 20 25 
(Total matrices: 6)

--- M Table (Cost) ---
      0   15750    7875    9375   11875   15125 
      -       0    2625    4375    7125   10500 
      -       -       0     750    2500    5375 
      -       -       -       0    1000    3500 
      -       -       -       -       0    5000 
      -       -       -       -       -       0 

--- S Table (Split Points) ---
  -   1   1   3   3   3 
  -   -   2   3   3   3 
  -   -   -   3   3   3 
  -   -   -   -   4   5 
  -   -   -   -   -   5 
  -   -   -   -   -   - 

Minimum scalar multiplications: 15125
Optimal parenthesization: ((A1 x (A2 x A3)) x ((A4 x A5) x A6))
```
