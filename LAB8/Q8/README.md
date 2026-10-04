# Question 8: Optimal Binary Search Trees (OBST)

<div align="center">

![C](https://img.shields.io/badge/Language-C11-00599C?style=for-the-badge&logo=c)
![Paradigm](https://img.shields.io/badge/Paradigm-Dynamic%20Programming-7C3AED?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Complete-059669?style=for-the-badge)

</div>

---

## 📌 Problem Statement

> Given a set of $n$ distinct sorted keys $K = \langle k_1, k_2, \dots, k_n \rangle$ with search probabilities $p_1, p_2, \dots, p_n$, and $n+1$ dummy keys $d_0, d_1, \dots, d_n$ representing searches not in $K$ with probabilities $q_0, q_1, \dots, q_n$, find the minimum expected search cost of a binary search tree.
>
> By choosing the proper input representation, write a program in C to validate your procedures and derive the complexity analysis of your algorithm.

---

## 🧠 Theoretical Formulation

### 1. Expected Search Cost
Let $T$ be a binary search tree storing keys $K$ and leaves representing dummy keys $d_0, \dots, d_n$.
The expected cost of a single search in $T$ is:
$$\mathbb{E}[\text{Cost}(T)] = \sum_{i=1}^n (\text{depth}_T(k_i) + 1) \cdot p_i + \sum_{i=0}^n (\text{depth}_T(d_i) + 1) \cdot q_i$$
where $\text{depth}_T(u)$ is the number of edges from the root to node $u$ (root has depth $0$).

### 2. Optimal Substructure (CLRS Section 15.5)
Consider any optimal subtree containing keys $k_i, \dots, k_j$ and dummy keys $d_{i-1}, \dots, d_j$.
If key $k_r$ ($i \le r \le j$) is chosen as the subtree's root:
- The left subtree contains keys $k_i, \dots, k_{r-1}$ and dummy keys $d_{i-1}, \dots, d_{r-1}$.
- The right subtree contains keys $k_{r+1}, \dots, k_j$ and dummy keys $d_r, \dots, d_j$.
- Placing $k_r$ at the root increases the depth of every node in both subtrees by $1$.

### 3. Probability Weight Sum
The cumulative probability weight of subtree $(i, j)$ is:
$$w[i, j] = \sum_{l=i}^j p_l + \sum_{l=i-1}^j q_l$$
with the recurrence:
$$w[i, i-1] = q_{i-1}$$
$$w[i, j] = w[i, j-1] + p_j + q_j \quad (j \ge i)$$

### 4. Recurrence Relation
Let $e[i, j]$ denote the expected search cost of an optimal binary search tree containing keys $k_i \dots k_j$:

$$e[i, j] = \begin{cases}
q_{i-1} & \text{if } j = i - 1 \text{ (empty subtree, only dummy key } d_{i-1} \text{)} \\
\min_{i \le r \le j} \left\{ e[i, r-1] + e[r+1, j] \right\} + w[i, j] & \text{if } i \le j
\end{cases}$$

The optimal root index is recorded in:
$$root[i, j] = \arg\min_{i \le r \le j} \left\{ e[i, r-1] + e[r+1, j] \right\}$$

---

## 📊 Data Structures & Input Representation

- **Probability Arrays:** `double p[n+1]` ($1$-indexed) and `double q[n+1]` ($0$-indexed).
- **Cost DP Matrix:** `double **e` — $(n+2) \times (n+1)$ matrix storing expected search costs.
- **Weight Matrix:** `double **w` — $(n+2) \times (n+1)$ matrix storing cumulative probability sums.
- **Root Choice Matrix:** `int **root` — $(n+2) \times (n+1)$ matrix storing the optimal root index for each subproblem.

```c
void optimalBST(int n, const double p[], const double q[], double **e, double **w, int **root);
void printTreeStructure(int i, int j, int **root, int parent, int is_left);
void printAsciiTree(int i, int j, int **root, int depth, const char *prefix);
void printOBSTTables(int n, double **e, double **w, int **root);
```

---

## 🔄 Algorithmic Procedure

```mermaid
flowchart TD
    A([Start: Input n, p[1..n], q[0..n]]) --> B["Allocate (n+2) x (n+1) matrices: e, w, root"]
    B --> C["Base Cases: e[i, i-1] = q[i-1], w[i, i-1] = q[i-1] for i in 1..n+1"]
    C --> D["Outer Loop: Subtree chain length l from 1 to n"]
    D --> E["Middle Loop: Subtree start index i from 1 to n - l + 1"]
    E --> F["Set j = i + l - 1<br>Compute w[i, j] = w[i, j-1] + p[j] + q[j]<br>Initialize e[i, j] = INF"]
    F --> G["Inner Loop: Try every candidate root r from i to j"]
    G --> H["Compute candidate cost: t = e[i, r-1] + e[r+1, j] + w[i, j]"]
    H --> I{"t < e[i, j]?"}
    I -- Yes --> J["e[i, j] = t<br>root[i, j] = r"]
    I -- No --> K["Continue to next r"]
    J --> K
    K --> L{"r reaches j?"}
    L -- No --> G
    L -- Yes --> M{"i reaches end of row?"}
    M -- No --> E
    M -- Yes --> N{"l reaches n?"}
    N -- No --> D
    N -- Yes --> O["Global Optimal Cost = e[1, n]"]
    O --> P["Recursively display parent-child tree hierarchy from root[1, n]"]
    P --> Q([End: Display Tables and Tree Structure])
```

---

## ⏱️ Complexity Analysis

| Component | Time Complexity | Space Complexity | Description |
| :--- | :---: | :---: | :--- |
| **Base Case Fill** | $\Theta(n)$ | $\Theta(n^2)$ | Initializes $n+1$ boundary conditions for dummy keys. |
| **Weight Matrix Fill** | $\Theta(n^2)$ | $\Theta(n^2)$ | Accumulates subarray probabilities incrementally. |
| **Cost Matrix Fill** | $\sum_{l=1}^n (n - l + 1) l = \Theta(n^3)$ | $\Theta(n^2)$ | Three nested loops over length $l$, start $i$, and root $r$. |
| **Knuth's Optimization (Note)** | Can be reduced to $\mathcal{O}(n^2)$ | $\Theta(n^2)$ | Restricting $r$ to $root[i, j-1] \le r \le root[i+1, j]$. |
| **Tree Reconstruction** | $\Theta(n)$ | $\mathcal{O}(n)$ stack | Recursive traversal visiting each node and leaf once. |
| **Total Program** | $\mathbf{\Theta(n^3)}$ | $\mathbf{\Theta(n^2)}$ | Standard CLRS dynamic programming formulation. |

---

## 🛠️ Compilation & Execution

```bash
# Navigate to question directory
cd /Users/rishav07/Documents/college/SEM3/DAA/LAB8/Q8

# Compile with GCC
gcc -Wall -Wextra -std=c11 -O2 main.c -o main

# Run interactive binary
./main
```

---

## 💻 Sample Traces

### Trace 1: Canonical CLRS Section 15.5 Benchmark ($n = 5$)

```text
========================================================================
 Demo 1: Canonical CLRS 15.5 Benchmark (n = 5)
========================================================================
  Number of Keys (n): 5
  Key Probabilities p[1..5]: { 0.15, 0.10, 0.05, 0.10, 0.20 }
  Dummy Probabilities q[0..5]: { 0.05, 0.10, 0.05, 0.05, 0.05, 0.10 }

  Table e[i, j] (Expected Search Cost):
     i \ j |       0       1       2       3       4       5 
  ---------+------------------------------------------------
      1    |  0.0500  0.4500  0.9000  1.2500  1.7500  2.7500 
      2    |       -  0.1000  0.4000  0.7000  1.2000  2.0000 
      3    |       -       -  0.0500  0.2500  0.6000  1.3000 
      4    |       -       -       -  0.0500  0.3000  0.9000 
      5    |       -       -       -       -  0.0500  0.5000 
      6    |       -       -       -       -       -  0.1000 

  Table w[i, j] (Cumulative Probability Weight):
     i \ j |       0       1       2       3       4       5 
  ---------+------------------------------------------------
      1    |  0.0500  0.3000  0.4500  0.5500  0.7000  1.0000 
      2    |       -  0.1000  0.2500  0.3500  0.5000  0.8000 
      3    |       -       -  0.0500  0.1500  0.3000  0.6000 
      4    |       -       -       -  0.0500  0.2000  0.5000 
      5    |       -       -       -       -  0.0500  0.3500 
      6    |       -       -       -       -       -  0.1000 

  Table root[i, j] (Optimal Root Indices):
     i \ j |     1     2     3     4     5 
  ---------+------------------------------
      1    |     1     1     2     2     2 
      2    |     -     2     2     2     4 
      3    |     -     -     3     4     5 
      4    |     -     -     -     4     5 
      5    |     -     -     -     -     5 

  ----------------- OPTIMAL BST STRUCTURE -----------------
  Minimum Expected Search Cost e[1, 5] = 2.7500

  Subtree Relationships:
  Key k2 is the root of the tree
  Key k1 is the left child of key k2
  Dummy key d0 is the left child of key k1
  Dummy key d1 is the right child of key k1
  Key k5 is the right child of key k2
  Key k4 is the left child of key k5
  Key k3 is the left child of key k4
  Dummy key d2 is the left child of key k3
  Dummy key d3 is the right child of key k3
  Dummy key d4 is the right child of key k4
  Dummy key d5 is the right child of key k5

  Hierarchical Visual Tree Layout:
  |-- (k2)
  |   |-- (k1)
  |   |   |-- [d0]
  |   |   |-- [d1]
  |   |-- (k5)
  |   |   |-- (k4)
  |   |   |   |-- (k3)
  |   |   |   |   |-- [d2]
  |   |   |   |   |-- [d3]
  |   |   |   |-- [d4]
  |   |   |-- [d5]
========================================================================
```
