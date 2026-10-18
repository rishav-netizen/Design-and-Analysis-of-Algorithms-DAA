# Q1 - Find the Median Without Sorting

## 📌 Problem Statement

Given a list of $N$ numbers, find the **median** of the list **without sorting** the entire list. Perform a detailed **complexity analysis** of the algorithm.

---

## 💡 Algorithmic Approach

Sorting an array of size $N$ requires $\mathcal{O}(N \log N)$ time. However, to find the median, we only need the middle element(s), not a fully sorted array.

We use **Hoare's Selection Algorithm (Quickselect)** with **randomized partitioning**:

### 1. Median Definition
- **Odd $N$ ($N = 2m + 1$):**  
  The median is the unique middle element at 0-based rank $k = \lfloor N / 2 \rfloor$ (1-based rank $(N+1)/2$).
- **Even $N$ ($N = 2m$):**  
  The median is typically defined as the arithmetic mean of the two middle elements at 0-based ranks $k_1 = (N/2) - 1$ and $k_2 = N/2$:
  $$\text{Median} = \frac{\text{element}(N/2 - 1) + \text{element}(N/2)}{2}$$

### 2. Quickselect Mechanism
Quickselect works similarly to Quicksort, but instead of recurring into both left and right subarrays, it recurs into **only one subarray** that contains the desired $k$-th target index:
1. **Choose a Pivot:** Pick a random pivot to avoid worst-case degeneracies on sorted/structured inputs.
2. **Partition:** Partition the subarray $[low, high]$ around the pivot such that:
   - All elements to the left of `pivot_index` are $\le \text{pivot}$.
   - All elements to the right of `pivot_index` are $\ge \text{pivot}$.
3. **Compare & Narrow Down:**
   - If $\text{pivot\_index} == k$: The pivot is exactly the element at rank $k$. Return it!
   - If $\text{pivot\_index} > k$: The $k$-th element lies in the left subarray $[low, \text{pivot\_index} - 1]$.
   - If $\text{pivot\_index} < k$: The $k$-th element lies in the right subarray $[\text{pivot\_index} + 1, high]$.

### 3. Handling Even $N$ in Linear Time
For even $N$:
1. Quickselect the element at index $N/2$. This places $\text{arr}[N/2]$ at its exact position and partitions the array into elements $\le \text{arr}[N/2]$ on the left and $\ge \text{arr}[N/2]$ on the right.
2. Find the element at index $(N/2 - 1)$ within the left partition $[0 \dots N/2 - 1]$.
3. Compute the average of both elements. Total work remains strictly $\mathcal{O}(N)$.

---

## ⏱️ Complexity Analysis

### Time Complexity

| Case | Recurrence Relation | Complexity | Description |
| :--- | :--- | :---: | :--- |
| **Best Case** | $T(N) = \mathcal{O}(N)$ | $\mathcal{O}(N)$ | Pivot chosen on the first partition lands directly on the target index $k$. |
| **Average Case** | $T(N) = T(N/2) + \Theta(N)$ | $\mathcal{O}(N)$ | A balanced partition discards approximately half the elements at each step. |
| **Worst Case** | $T(N) = T(N-1) + \Theta(N)$ | $\mathcal{O}(N^2)$ | Occurs if unbalanced pivots are chosen repeatedly (mitigated by randomized pivot selection to expected $\mathcal{O}(N)$). |

#### Mathematical Proof for Average Case $\mathcal{O}(N)$:
At each step, partitioning takes linear time proportional to the current subarray size:
$$T(N) = N + \frac{N}{2} + \frac{N}{4} + \frac{N}{8} + \dots + 1 = N \sum_{i=0}^{\log_2 N} \left(\frac{1}{2}\right)^i \le N \cdot \frac{1}{1 - 1/2} = 2N = \mathcal{O}(N)$$

By the **Master Theorem** ($T(N) = T(N/2) + \Theta(N)$ with $a = 1, b = 2, f(N) = \Theta(N)$):
$$\log_b a = \log_2 1 = 0 \implies f(N) = \Omega(N^{0 + \epsilon}) \implies T(N) = \Theta(N)$$

### Space Complexity

| Space Component | Complexity | Description |
| :--- | :---: | :--- |
| **Auxiliary Space** | $\mathcal{O}(1)$ | Iterative implementation uses constant extra variables (in-place). |
| **Input Array** | $\mathcal{O}(N)$ | Modifies array in-place via partitioning without creating full auxiliary copies. |

---

## 🛠️ Compilation & Execution

```bash
# Compile using GCC / Clang
gcc -Wall -Wextra -std=c11 main.c -o main

# Run the program
./main
```

---

## 💻 Sample Traces

### Example 1: Odd $N$ ($N = 7$)
**Input:**
```text
Enter number of elements: 7
Choose input method (1 for manual, 2 for random): 1
Element 1: 12
Element 2: 3
Element 3: 5
Element 4: 7
Element 5: 4
Element 6: 19
Element 7: 26
```

**Output:**
```text
Original Unsorted Array: {12, 3, 5, 7, 4, 19, 26}
Array After Quickselect: {4, 3, 5, 7, 12, 19, 26}
Median: 7.00 (Value = 7)
```

### Example 2: Even $N$ ($N = 6$)
**Input:**
```text
Enter number of elements: 6
Choose input method (1 for manual, 2 for random): 1
Element 1: 20
Element 2: 10
Element 3: 50
Element 4: 30
Element 5: 40
Element 6: 60
```

**Output:**
```text
Original Unsorted Array: {20, 10, 50, 30, 40, 60}
Array After Quickselect: {20, 10, 30, 40, 50, 60}
Middle elements: 30 and 40
Median (Average): 35.00
```

### Example 3: Random Array Input & Error Handling Showcase
**Input:**
```text
Enter number of elements: -5
Invalid input! Try again: 0
Invalid input! Try again: 5
Choose input method (1 for manual, 2 for random): 3
Invalid input!
Try again: 2
Enter limits between which random numbers should be: 100 10
Invalid Input! Try again.
Enter limits between which random numbers should be: 10 100
```

**Output:**
```text
Original Unsorted Array: {42, 17, 89, 56, 12}
Array After Quickselect: {12, 17, 42, 89, 56}
Median: 42.00 (Value = 42)
```
