# Q2 - Find the $K$'th Smallest Element Without Sorting

## 📌 Problem Statement

Given a list of $N$ numbers and an integer $K$ ($1 \le K \le N$), find the **$K$-th smallest element** in the list **without sorting** the entire list. Perform a detailed **complexity analysis** of the algorithm.

---

## 💡 Algorithmic Approach

The problem of finding the $K$-th smallest element in an unsorted list is formally known as finding the **$K$-th order statistic**.

### Selection Algorithms Comparison

| Approach | Time Complexity | Space Complexity | In-place? | Description |
| :--- | :---: | :---: | :---: | :--- |
| **Full Sorting** | $\mathcal{O}(N \log N)$ | $\mathcal{O}(1)$ or $\mathcal{O}(N)$ | Yes/No | Sort entire array, then access index $K-1$. Overkill when we only need 1 element. |
| **Max-Heap of Size $K$** | $\mathcal{O}(N \log K)$ | $\mathcal{O}(K)$ | No | Maintain a heap of the $K$ smallest elements seen so far. |
| **Quickselect (Hoare's Selection)** | $\mathcal{O}(N)$ expected | $\mathcal{O}(1)$ | **Yes** | **Optimal approach.** Partitions array and prunes search space in half each step. |
| **Median-of-Medians** | $\mathcal{O}(N)$ worst-case | $\mathcal{O}(\log N)$ | No | Deterministic linear selection with higher constant factor. |

### Quickselect Algorithm (Hoare's Selection)
Quickselect is a divide-and-conquer (prune-and-search) algorithm related to Quicksort:
1. **Target Index:** The $K$-th smallest element corresponds to the 0-based target index $\text{target\_idx} = K - 1$.
2. **Randomized Pivot Selection:** Choose a random pivot between $low$ and $high$ and swap it with $\text{arr}[high]$ to avoid adversarial $\mathcal{O}(N^2)$ degradation.
3. **Partition:** Run Lomuto partitioning to place the pivot at its final sorted position `pivot_idx`.
4. **Decide Branch:**
   - If $\text{pivot\_idx} == \text{target\_idx}$: The pivot is the exact $K$-th smallest element! Return $\text{arr}[\text{pivot\_idx}]$.
   - If $\text{pivot\_idx} > \text{target\_idx}$: The element must be in the left partition $[low, \text{pivot\_idx} - 1]$.
   - If $\text{pivot\_idx} < \text{target\_idx}$: The element must be in the right partition $[\text{pivot\_idx} + 1, high]$.

Because Quickselect discards the irrelevant subarray at each partition, it operates strictly in **linear average time $\mathcal{O}(N)$**.

---

## ⏱️ Complexity Analysis

### Time Complexity

| Case | Recurrence Relation | Complexity | Condition |
| :--- | :--- | :---: | :--- |
| **Best Case** | $T(N) = \mathcal{O}(N)$ | $\mathcal{O}(N)$ | Pivot chosen on the first iteration lands exactly at index $K - 1$. |
| **Average Case** | $T(N) = T(N/2) + \Theta(N)$ | $\mathcal{O}(N)$ | Random pivot splits the array roughly evenly on average. |
| **Worst Case** | $T(N) = T(N-1) + \Theta(N)$ | $\mathcal{O}(N^2)$ | Pathological pivots selected every step (extreme min/max repeatedly). |

#### Mathematical Derivation of Expected $\mathcal{O}(N)$
On average, a randomized pivot splits the array such that the subproblem size shrinks geometrically by a factor of at least $\frac{3}{4}$:
$$T(N) \le T(3N/4) + cN$$
Expanding the recurrence:
$$T(N) \le cN \sum_{i=0}^{\infty} \left(\frac{3}{4}\right)^i = cN \cdot \frac{1}{1 - 3/4} = 4cN = \mathcal{O}(N)$$

By the **Master Theorem** ($T(N) = a T(N/b) + f(N)$ with $a = 1, b = 2, f(N) = \Theta(N)$):
$$\log_2(1) = 0 \implies f(N) = \Omega(N^{0 + \epsilon}) \implies T(N) = \Theta(N)$$

### Space Complexity

| Metric | Complexity | Explanation |
| :--- | :---: | :--- |
| **Auxiliary Space** | $\mathcal{O}(1)$ | Implemented iteratively with simple loop pointers; no recursive stack overhead. |
| **Input Space** | $\mathcal{O}(N)$ | Operates directly on the input array in-place. |

---

## 🛠️ Compilation & Execution

```bash
# Compile with GCC / Clang
gcc -Wall -Wextra -std=c11 main.c -o main

# Run the executable
./main
```

---

## 💻 Sample Traces

### Example 1: Custom Array
**Input:**
```text
Enter number of elements: 8
Choose input method (1 for manual, 2 for random): 1
Element 1: 34
Element 2: 7
Element 3: 23
Element 4: 32
Element 5: 5
Element 6: 62
Element 7: 19
Element 8: 12
Enter K (1 <= K <= 8): 4
```

**Output:**
```text
Original Unsorted Array: {34, 7, 23, 32, 5, 62, 19, 12}
Array After Quickselect: {5, 7, 12, 19, 23, 62, 32, 34}
Result: 4th smallest element is 19
```

*(Notice that while the 4th smallest element 19 is placed correctly and all elements $\le 19$ are to the left and $\ge 19$ to the right, the subarrays themselves are not fully sorted!)*

### Example 2: Random Array Input & Error Handling Showcase
**Input:**
```text
Enter number of elements: -3
Invalid input! Try again: 5
Choose input method (1 for manual, 2 for random): 4
Invalid input!
Try again: 2
Enter limits between which random numbers should be: 50 10
Invalid Input! Try again.
Enter limits between which random numbers should be: 1 100
Enter K (1 <= K <= 5): 7
	Invalid input, try again!
Enter K: 3
```

**Output:**
```text
Original Unsorted Array: {45, 12, 89, 33, 67}
Array After Quickselect: {12, 33, 45, 89, 67}
Result: 3th smallest element is 45
```
