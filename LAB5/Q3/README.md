# Q3 - Quick Sort of $N$ Random Elements Stored in a File

## 📌 Problem Statement

Implement **Quick Sort** to sort $N$ randomly generated numbers stored in an external file. The application must:
1. Generate $N$ random integers and store them into a file (`unsorted.txt`).
2. Read the numbers from the file into memory.
3. Sort the array using the **Quick Sort** algorithm while recording key operational metrics (time taken, comparisons, swaps).
4. Store the resulting sorted numbers into an output file (`sorted.txt`).

---

## 💡 Algorithmic Approach

### Workflow Pipeline

```
[ Random Generator ]
        │
        ▼ writes N random integers
  ( unsorted.txt )
        │
        ▼ reads into memory
   [ Memory Array ]
        │
        ▼ Quick Sort (Divide & Conquer)
  [ Sorted Memory Array ]
        │
        ▼ writes sorted data
   ( sorted.txt )
```

### Quick Sort Algorithm
Quick Sort is a classic **Divide and Conquer** algorithm:
1. **Choose a Pivot:** Pick an element from the subarray to act as the pivot (e.g. median / middle element to prevent worst-case performance on already sorted runs).
2. **Partition:** Rearrange the array such that:
   - All elements less than or equal to the pivot move to the left of the pivot.
   - All elements greater than the pivot move to the right.
   - The pivot lands at its final sorted index `pivot_idx`.
3. **Recurse:** Recursively apply Quick Sort to the left subarray $[low, \text{pivot\_idx} - 1]$ and right subarray $[\text{pivot\_idx} + 1, high]$.

---

## ⏱️ Complexity Analysis

### Time Complexity

| Case | Recurrence Relation | Complexity | Condition |
| :--- | :--- | :---: | :--- |
| **Best Case** | $T(N) = 2T(N/2) + \Theta(N)$ | $\mathcal{O}(N \log N)$ | Pivot splits the array into two equal halves at every recursive step. |
| **Average Case** | $T(N) = 2T(N/2) + \Theta(N)$ | $\mathcal{O}(N \log N)$ | Balanced partitioning across random input distributions. |
| **Worst Case** | $T(N) = T(N-1) + \Theta(N)$ | $\mathcal{O}(N^2)$ | Pivot is consistently the smallest or largest element (e.g. already sorted array with fixed endpoint pivot). |

#### Mathematical Proof for Best / Average Case:
Applying Case 2 of the **Master Theorem** ($a = 2, b = 2, f(N) = \Theta(N)$):
$$\log_b a = \log_2 2 = 1 \implies f(N) = \Theta(N^1) \implies T(N) = \Theta(N \log N)$$

### Space Complexity

| Space Component | Complexity | Description |
| :--- | :---: | :--- |
| **Auxiliary Memory** | $\mathcal{O}(1)$ | In-place partitioning requires no extra data array buffers. |
| **Call Stack (Best/Avg)**| $\mathcal{O}(\log N)$ | Recursive call tree depth with balanced pivots. |
| **Call Stack (Worst)** | $\mathcal{O}(N)$ | Call stack depth if completely unbalanced partitions occur. |

---

## 🛠️ Compilation & Execution

```bash
# Compile using GCC / Clang
gcc -Wall -Wextra -std=c11 main.c -o main

# Run the executable
./main
```

---

## 💻 Sample Execution

**Terminal Interaction:**
```text
Enter number of random elements (N): -5
Invalid input! Try again: 6
Enter limits between which random numbers should be: 100 20
Invalid Input! Try again.
Enter limits between which random numbers should be: 20 100

Unsorted preview: {54, 100, 76, 71, 53, 20}
Sorted preview: {20, 53, 54, 71, 76, 100}

Execution Time: 0.0050 ms
Total Comparisons: 8
Total Swaps: 5
```

### Generated File Format

**`unsorted.txt`:**
```text
6
54 100 76 71 53 20 
```

**`sorted.txt`:**
```text
6
20 53 54 71 76 100 
```
