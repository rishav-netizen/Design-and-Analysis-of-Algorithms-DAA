# Q3 — Reve’s Puzzle (4-Peg Tower of Hanoi)

## 📌 Problem Statement

> **[Reve’s Puzzle]**  
> There are eight disks of different sizes and four pegs. Initially, all the disks are on the first peg in order of size, the largest on the bottom and the smallest on the top. The objective is to transfer all the disks to another peg by a sequence of moves.
> 
> Only one disk can be moved at a time, and it is forbidden to place a larger disk on top of a smaller one.
> 
> Devise an algorithm that solves the puzzle in **33 moves**. Generalize your algorithm for an $n$-disk problem.
>
> By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

```text
Peg A (Source)         Peg B (Aux 1)       Peg C (Aux 2)       Peg D (Target)
     |                      |                   |                   |
    (1)                     |                   |                   |
   ( 2 )                    |                   |                   |
  (  3  )                   |                   |                   |
 (   4   )                  |                   |                   |
(    5    )                 |                   |                   |
(    6    )                 |                   |                   |
(    7    )                 |                   |                   |
(    8    )                 |                   |                   |
=============          =============       =============       =============
```

---

## 💡 Mathematical Analysis & Algorithmic Derivation

### 1. Classical 3-Peg Hanoi vs. 4-Peg Reve's Puzzle

In the classical Tower of Hanoi with $3$ pegs, moving $n$ disks requires exactly:
$$H_3(n) = 2^n - 1 \text{ moves}$$
For $n = 8$ disks on 3 pegs: $H_3(8) = 2^8 - 1 = 255\text{ moves}$.

With a 4th auxiliary peg available (Reve's Puzzle), the number of required moves drops dramatically from $255$ down to **$33$ moves** using the **Frame-Stewart Algorithm** (proposed independently by J. S. Frame and B. M. Stewart in 1941, proven optimal for 4 pegs by Bousch in 2014).

---

### 2. The Frame-Stewart Algorithmic Strategy

To transfer $n$ disks from source Peg $A$ to target Peg $D$ using two auxiliary pegs $B$ and $C$:

1. **Partition:** Choose an optimal integer $k$ ($1 \le k < n$).
2. **Subproblem 1 (4 pegs):** Recursively transfer the top $k$ smallest disks from Peg $A$ to auxiliary Peg $B$ using all 4 pegs ($A, B, C, D$).  
   *Cost:* $R(k)$ moves.
3. **Subproblem 2 (3 pegs):** Transfer the remaining $n - k$ largest disks from Peg $A$ to destination Peg $D$ using only 3 pegs ($A, C, D$), never touching Peg $B$ (since Peg $B$ contains smaller disks).  
   *Cost:* $H_3(n - k) = 2^{n - k} - 1$ moves.
4. **Subproblem 3 (4 pegs):** Recursively transfer the $k$ disks from Peg $B$ to destination Peg $D$ using all 4 pegs ($A, B, C, D$).  
   *Cost:* $R(k)$ moves.

#### Recurrence Relation
$$\boxed{R(n) = \min_{1 \le k < n} \left( 2 \cdot R(k) + 2^{n - k} - 1 \right)}$$

with base cases:
$$R(0) = 0, \quad R(1) = 1$$

---

### 3. Deriving the 33-Move Solution for $n = 8$

Computing values bottom-up using the recurrence:

| $n$ | Optimal $k$ | Decomposition: $2 R(k) + 2^{n-k} - 1$ | $R(n)$ (4 Pegs) | $H_3(n)$ (3 Pegs) |
| :---: | :---: | :--- | :---: | :---: |
| 1 | 0 | Base case | **1** | 1 |
| 2 | 1 | $2(1) + (2^1 - 1) = 2 + 1$ | **3** | 3 |
| 3 | 1 | $2(1) + (2^2 - 1) = 2 + 3$ | **5** | 7 |
| 4 | 2 | $2(3) + (2^2 - 1) = 6 + 3$ | **9** | 15 |
| 5 | 3 | $2(5) + (2^2 - 1) = 10 + 3$ | **13** | 31 |
| 6 | 3 | $2(5) + (2^3 - 1) = 10 + 7$ | **17** | 63 |
| 7 | 3 | $2(5) + (2^4 - 1) = 10 + 15$ | **25** | 127 |
| **8** | **4** | **$2 R(4) + (2^{8-4} - 1) = 2(9) + (16 - 1) = 18 + 15$** | **33** | **255** |

For $n = 8$, the optimal partition is $k = 4$:
- Move top 4 disks to Peg $B$: **9 moves**
- Move remaining 4 disks to Peg $D$ (3-peg Hanoi): $2^4 - 1 =$ **15 moves**
- Move 4 disks from Peg $B$ to Peg $D$: **9 moves**
- **Total moves:** $9 + 15 + 9 = \mathbf{33\text{ moves}}$ (Exact match!).

---

### 4. Generalization for Arbitrary $n$

The sequence of increments $R(n) - R(n-1)$ equals $2^{m-1}$ repeated $m$ times, corresponding to the $m$-th triangular number $T_m = \frac{m(m+1)}{2}$.  
The optimal partition $k^*(n)$ is given analytically by:
$$k^*(n) = n - \left\lfloor \sqrt{2n + 1} + 0.5 \right\rfloor + 1$$

---

## 🛠️ Input Representation & Data Structures

In [`main.c`](file:///Users/rishav07/Documents/college/SEM3/DAA/LAB7/Q3/main.c):
1. **Peg Representation:**
   `int pegs[4][MAX_DISKS]` tracks disk stacks, with `top[4]` holding stack pointers.
2. **Move Invariant Checker:**
   `moveDisk(from, to)` verifies that every move is legal:
   - Source peg is not empty.
   - Target peg top disk is strictly larger than the incoming disk ($pegs[to][top] > disk$).
3. **Algorithms Implemented:**
   - `reve(n, from, to, aux1, aux2)`: 4-peg Frame-Stewart recursive solver.
   - `hanoi3(m, from, to, aux)`: Standard 3-peg Hanoi recursive solver.

---

## ⏱️ Complexity Analysis

| Metric | Complexity | Explanation |
| :--- | :---: | :--- |
| **Move Count $R(n)$** | $\mathcal{O}(2^{\sqrt{2n}})$ | Sub-exponential growth, significantly smaller than $\mathcal{O}(2^n)$. |
| **Time Complexity** | $\mathcal{O}(R(n))$ | Directly proportional to generating each disk transfer. |
| **DP Precomputation** | $\mathcal{O}(n^2)$ | Precomputing optimal partition $k$ up to $n$. |
| **Space Complexity** | $\mathcal{O}(n)$ | Stack memory for recursion depth and peg disk arrays. |

---

## ⚙️ Compilation & Execution

```bash
# Compile
gcc -Wall -Wextra -O2 main.c -o main

# Run
./main
```

---

## 🧪 Sample Output & Execution Trace ($n = 8$, 33 Moves)

```text
====================================================
        Reve's Puzzle (4-Peg Tower of Hanoi)        
                  DAA Lab 07, Q3                    
====================================================

[Initial State: 8 Disks on Peg A]
Current Peg Status:
  Peg A: [ 8 7 6 5 4 3 2 1 ]
  Peg B: [ ]
  Peg C: [ ]
  Peg D: [ ]

[Frame-Stewart Algorithmic Decomposition for n = 8]
  Optimal partition k: 4
  Formula: R(8) = 2 * R(4) + (2^4 - 1) = 2 * 9 + 15 = 33 moves

[Move Sequence Execution]
  Move  1: Move Disk 1 from Peg A -> Peg D
  Move  2: Move Disk 2 from Peg A -> Peg B
  Move  3: Move Disk 3 from Peg A -> Peg C
  Move  4: Move Disk 2 from Peg B -> Peg C
  Move  5: Move Disk 4 from Peg A -> Peg B
  Move  6: Move Disk 2 from Peg C -> Peg A
  Move  7: Move Disk 3 from Peg C -> Peg B
  Move  8: Move Disk 2 from Peg A -> Peg B
  Move  9: Move Disk 1 from Peg D -> Peg B
  Move 10: Move Disk 5 from Peg A -> Peg C
  Move 11: Move Disk 6 from Peg A -> Peg D
  Move 12: Move Disk 5 from Peg C -> Peg D
  Move 13: Move Disk 7 from Peg A -> Peg C
  Move 14: Move Disk 5 from Peg D -> Peg A
  Move 15: Move Disk 6 from Peg D -> Peg C
  Move 16: Move Disk 5 from Peg A -> Peg C
  Move 17: Move Disk 8 from Peg A -> Peg D
  Move 18: Move Disk 5 from Peg C -> Peg D
  Move 19: Move Disk 6 from Peg C -> Peg A
  Move 20: Move Disk 5 from Peg D -> Peg A
  Move 21: Move Disk 7 from Peg C -> Peg D
  Move 22: Move Disk 5 from Peg A -> Peg C
  Move 23: Move Disk 6 from Peg A -> Peg D
  Move 24: Move Disk 5 from Peg C -> Peg D
  Move 25: Move Disk 1 from Peg B -> Peg A
  Move 26: Move Disk 2 from Peg B -> Peg D
  Move 27: Move Disk 3 from Peg B -> Peg C
  Move 28: Move Disk 2 from Peg D -> Peg C
  Move 29: Move Disk 4 from Peg B -> Peg D
  Move 30: Move Disk 2 from Peg C -> Peg B
  Move 31: Move Disk 3 from Peg C -> Peg D
  Move 32: Move Disk 2 from Peg B -> Peg D
  Move 33: Move Disk 1 from Peg A -> Peg D

[Final State after Execution]
Current Peg Status:
  Peg A: [ ]
  Peg B: [ ]
  Peg C: [ ]
  Peg D: [ 8 7 6 5 4 3 2 1 ]

[Verification]
  Actual moves taken:   33
  Theoretical minimum:  33
  Result: SUCCESS! Solved exactly in 33 legal moves.
```
