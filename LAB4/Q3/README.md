# Q3 - $k$-Sum Problem (Application of Sorting III)

## 📌 Problem Statement
Given a set $S$ of $n$ integers, a target integer $T$, and an integer $k$ ($1 \le k \le n$), determine whether there exists a subset of $k$ distinct integers in $S$ that add up to $T$. If such elements exist, identify and print them.

The objective is to design an algorithm running in **$\mathcal{O}(n^{k-1} \log n)$ time complexity** and implement it in C.

---

## 💡 Algorithm & Approach

A brute-force search trying all $\binom{n}{k}$ subsets takes $\mathcal{O}(n^k)$ time. By pre-sorting the set and combining recursive combination enumeration with binary search, we achieve the optimal $\mathcal{O}(n^{k-1} \log n)$ bound:

1. **Initial Sorting:**
   - Sort the array $S$ in ascending order using `qsort` ($\mathcal{O}(n \log n)$).

2. **Recursive Combination Enumeration (`kElementsExist`):**
   - Use recursion to select $(k - 1)$ elements sequentially.
   - At each recursive level, iterate from index $l$ up to $n - k$ (ensuring at least $k - 1$ elements remain ahead in the array to avoid out-of-bounds selection).
   - Recurse with:
     - Next starting index: $l = i + 1$ (prevents reusing previously selected elements, ensuring distinctness)
     - Remaining target: $T' = T - S[i]$
     - Remaining count: $k' = k - 1$

3. **Base Case & Binary Search:**
   - When $k == 1$, exactly one element is needed to complete the target sum.
   - Perform a **Binary Search** via `binarySearch` in the remaining sorted range $[l, n - 1]$ for the exact required value $T$.
   - Binary search takes $\mathcal{O}(\log n)$ time.

4. **Output Reconstruction on Call-Stack Unwind:**
   - When a valid combination is found, the base case prints the $k$-th element ($S[\text{index}]$).
   - As the recursive call stack unwinds, each parent level prints its chosen element ($S[i]$), successfully outputting the exact numbers that sum to $T$.

$$\text{Total Operations} = \underbrace{\mathcal{O}(n \log n)}_{\text{Sorting}} + \underbrace{\binom{n}{k-1}}_{\mathcal{O}(n^{k-1}) \text{ combinations}} \times \underbrace{\mathcal{O}(\log n)}_{\text{Binary Search}} = \mathbf{\mathcal{O}(n^{k-1} \log n)}$$

---

## ⏱️ Complexity Analysis

| Metric | Complexity | Description |
| :--- | :---: | :--- |
| **Initial Sorting** | $\mathcal{O}(n \log n)$ | Sorting array $S$ of size $n$ using `qsort`. |
| **Search Traversal** | $\mathcal{O}(n^{k-1} \log n)$ | $\mathcal{O}(n^{k-1})$ recursive paths with an $\mathcal{O}(\log n)$ binary search at depth $k = 1$. |
| **Total Time Complexity** | $\mathcal{O}(n^{k-1} \log n)$ | Strictly conforms to the requested asymptotic upper bound. |
| **Space Complexity** | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ for dynamically allocated array $S$, plus $\mathcal{O}(k)$ recursion call-stack depth. |

---

## 🛠️ Compilation & Execution

```bash
# Compile the C program
gcc -Wall -Wextra main.c -o main

# Run the executable
./main
```

### Example

**Input:**
```text
Enter the number of elements for the set(n): 5

Enter elements for set S:
10 2 3 7 5

Entered set is: 
S: {10, 2, 3, 7, 5}
Enter sum to find(T): 14
Enter number of integers(k) to add up to sum: 3
```

**Output:**
```text
Result:   7
 	+ 5
 	+ 2
 	= 14 
Found!
```
