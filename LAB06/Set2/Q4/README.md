# Question 4: Sorting via Reversal Procedure

## 📌 Problem Overview
Given a permutation $p$ of the integers $1$ to $n$, the goal is to sort the array into increasing order.
**Constraint:** The *only* operation at your disposal is `reverse(p, i, j)`, which inverses the subsequence from index $i$ to index $j$.
**Cost:** The cost of one execution of `reverse(p, i, j)` is defined as its length: $|j - i| + 1$.

Design an algorithm that achieves the sort in a total accumulated cost bounded by $\mathcal{O}(n \log^2 n)$.

---

## 💡 The $\mathcal{O}(n \log^2 n)$ Strategy

A standard selection sort using reversals (often known as basic Pancake Sorting) requires $\mathcal{O}(n^2)$ total cost.
To achieve $\mathcal{O}(n \log^2 n)$, we apply a **Divide and Conquer** Merge Sort hybrid using rotational blocks:

1. **Split Phase:** Recursively divide the array into halves until the size is $1$.
2. **Merge Phase:**
   Instead of using an auxiliary array (which violates the reversal restriction), we utilize **Block Rotations**.
   To merge two adjacent sorted sub-arrays, we binary search the optimal insertion point, and swap the sub-arrays in place using precisely **three reversals** (e.g., $A^R$, $B^R$, $(A^RB^R)^R$).
3. Because we merge using binary search ($\mathcal{O}(\log n)$ depth) inside a recursion tree of depth $\mathcal{O}(\log n)$, the total length/cost cascades perfectly into $\mathcal{O}(n \log^2 n)$.

---

## 🛠️ Implementation Details
The algorithm in [`main.c`](./main.c) breaks this down via:
1. **`Reverse()`:** Safely swaps mirrored positions in place.
2. **`Rotate()`:** Wraps the classic three-step reversal sequence.
3. **`MergeSortReversals()`:** Coordinates the recursive layout and tracks the integer cost.

---

## ⚙️ Compilation & Execution

```bash
# Compile
gcc -o main main.c

# Run
./main
```

---


### 📤 Sample Output
```text
Enter the size of the permutation: 5
Enter the elements of the permutation (1 to 5):
1 4 3 2 5
Original Array: {1, 4, 3, 2, 5}
Sorted Array: {1, 2, 3, 4, 5}
Total Reversal Cost: 7
```

---

## 📊 Complexity Summary

| Component | Cost per Step | Depth / Recurrence | Total Accumulated Cost |
| :--- | :---: | :---: | :---: |
| **Binary Search (Insertion)** | $\mathcal{O}(\log n)$ | $\mathcal{O}(\log n)$ | - |
| **Block Rotations (Reversals)** | $\mathcal{O}(n)$ | $\mathcal{O}(\log n)$ tree layers | **$\mathcal{O}(n \log^2 n)$** |
