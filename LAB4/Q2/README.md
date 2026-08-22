# Q2 - Pair Sum from Two Sets (Application of Sorting II)

## 📌 Problem Statement
Given two sets $S_1$ and $S_2$, each containing $n$ elements, and a target value $x$, determine whether there exists a pair of elements $(a, b)$ such that $a \in S_1$, $b \in S_2$, and $a + b = x$.

The objective is to design an algorithm that runs in **$\mathcal{O}(n \log n)$ time complexity** and implement it in C.

---

## 💡 Algorithm & Approach

A brute-force search checking all pairs $(a, b) \in S_1 \times S_2$ would take $\mathcal{O}(n^2)$ time. To achieve $\mathcal{O}(n \log n)$ time complexity, we sort both sets and employ the **two-pointer technique**:

1. **Sorting:**
   - Sort set $S_1$ in ascending order using `qsort` ($\mathcal{O}(n \log n)$).
   - Sort set $S_2$ in ascending order using `qsort` ($\mathcal{O}(n \log n)$).

2. **Two-Pointer Search:**
   - Initialize pointer `i = 0` at the beginning of $S_1$ (smallest element of $S_1$).
   - Initialize pointer `j = n - 1` at the end of $S_2$ (largest element of $S_2$).
   - While `i < n` and `j >= 0`:
     - Compute $\text{currentSum} = S_1[i] + S_2[j]$.
     - If $\text{currentSum} == x$: A valid pair $(S_1[i], S_2[j])$ is found; return `true`.
     - If $\text{currentSum} < x$: The sum is too small; increment `i` (`i++`) to consider a larger element from $S_1$.
     - If $\text{currentSum} > x$: The sum is too large; decrement `j` (`j--`) to consider a smaller element from $S_2$.

3. **Termination:**
   - If the pointers cross without finding any pair that sums to $x$, return `false`.

> **Alternative Approach (Binary Search):**  
> Alternatively, one could sort only $S_2$ ($\mathcal{O}(n \log n)$) and perform a binary search for $(x - a)$ in $S_2$ for each $a \in S_1$ ($n \times \mathcal{O}(\log n) = \mathcal{O}(n \log n)$). The two-pointer approach avoids repeated binary searches and achieves a linear $\mathcal{O}(n)$ search phase after sorting.

---

## ⏱️ Complexity Analysis

| Metric | Complexity | Description |
| :--- | :---: | :--- |
| **Sorting Complexity** | $\mathcal{O}(n \log n)$ | Sorting two arrays of size $n$ using `qsort`. |
| **Search Complexity** | $\mathcal{O}(n)$ | Two pointers traverse $S_1$ and $S_2$ at most $2n$ steps in total. |
| **Total Time Complexity** | $\mathcal{O}(n \log n)$ | Dominated by the initial sorting phase. |
| **Space Complexity** | $\mathcal{O}(n)$ | Dynamic allocation for sets $S_1$ and $S_2$ of size $n$. |

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
Enter the number of elements for the sets(n): 4

Enter elements for set S1:
5 1 9 3

Enter elements for set S2:
8 2 4 10

Entered sets are: 
S1: {5, 1, 9, 3}
S2: {8, 2, 4, 10}
Enter sum to find(x): 13
```

**Output:**
```text
Found pair: 3 + 10 = 13
```
