# Q4 - Heap Sort of $N$ Random Elements Stored in a File

## 📌 Problem Statement

Implement **Heap Sort** to sort $N$ randomly generated numbers stored in an external file, and perform a complete **complexity analysis** of the algorithm.

The program must:
1. Generate $N$ random integers and store them into a file (`unsorted.txt`).
2. Read the elements from the file into memory.
3. Sort the array using **Heap Sort** (Max-Heap construction and successive extractions).
4. Store the sorted array into an output file (`sorted.txt`).

---

## 💡 Algorithmic Approach

A **Heap** is a complete binary tree that satisfies the **Heap Property**. In a **Max-Heap**, for every node $i$ other than the root:
$$\text{Array}[\text{Parent}(i)] \ge \text{Array}[i]$$

### Array Representation of Binary Heap (0-indexed)
For any node at index $i$:
- **Parent:** $\lfloor (i - 1) / 2 \rfloor$
- **Left Child:** $2i + 1$
- **Right Child:** $2i + 2$
- **Last Non-Leaf Node:** $\lfloor N / 2 \rfloor - 1$

---

### Algorithm Phases

```
1. Build Max-Heap Phase:
   [ Unsorted Array ] ──( bottom-up max_heapify from N/2 - 1 down to 0 )──> [ Max-Heap ]

2. Sorting / Extraction Phase:
   For i = N - 1 down to 1:
     a. Swap root (Array[0] = maximum) with Array[i]
     b. Reduce effective heap size to i
     c. max_heapify(Array, size = i, root = 0)
```

---

## ⏱️ Detailed Complexity Analysis

### 1. Complexity of `max_heapify`
At each level of the tree, `max_heapify` performs $\mathcal{O}(1)$ comparisons and moves down at most one level.
For a tree of height $h$:
$$\text{Time}(\text{max\_heapify}) = \mathcal{O}(h) = \mathcal{O}(\log N)$$

---

### 2. Complexity of `build_max_heap` ($\mathcal{O}(N)$ Proof)
A naive bound suggests $N/2$ calls to `max_heapify`, each taking $\mathcal{O}(\log N)$, yielding $\mathcal{O}(N \log N)$. However, this bound is not tight.

- Most nodes reside near the bottom of the tree where their height $h$ is small.
- An $N$-element complete binary tree has at most $\left\lceil \frac{N}{2^{h+1}} \right\rceil$ nodes at height $h$.
- The total cost to build the heap is:
  $$T(\text{build\_heap}) = \sum_{h=0}^{\lfloor\log_2 N\rfloor} \left\lceil \frac{N}{2^{h+1}} \right\rceil \mathcal{O}(h) = \mathcal{O}\left( N \sum_{h=0}^{\infty} \frac{h}{2^h} \right)$$

Using the known mathematical summation for the arithmetic-geometric series:
$$\sum_{h=0}^{\infty} \frac{h}{2^h} = \frac{1/2}{(1 - 1/2)^2} = 2$$

Therefore:
$$T(\text{build\_heap}) = \mathcal{O}(N \cdot 2) = \mathcal{O}(N)$$

---

### 3. Complexity of Sorting Phase
The loop runs $N - 1$ times. In each iteration:
- 1 swap operation: $\mathcal{O}(1)$
- 1 `max_heapify` on root of heap size $k$ ($k$ decreasing from $N-1$ down to 1): $\mathcal{O}(\log k)$

$$\sum_{k=1}^{N-1} \mathcal{O}(\log k) = \mathcal{O}(\log(N!)) = \mathcal{O}(N \log N)$$

---

### 4. Overall Time Complexity Summary

| Case | Build Heap | Extraction Phase | Overall Time Complexity |
| :--- | :---: | :---: | :---: |
| **Best Case** | $\mathcal{O}(N)$ | $\mathcal{O}(N \log N)$ | $\mathcal{O}(N \log N)$ |
| **Average Case** | $\mathcal{O}(N)$ | $\mathcal{O}(N \log N)$ | $\mathcal{O}(N \log N)$ |
| **Worst Case** | $\mathcal{O}(N)$ | $\mathcal{O}(N \log N)$ | $\mathcal{O}(N \log N)$ |

> **Key Strength:** Unlike Quick Sort (which degrades to $\mathcal{O}(N^2)$ in the worst case), Heap Sort **guarantees $\mathcal{O}(N \log N)$ time in all scenarios** while sorting in-place.

---

### 5. Space Complexity

| Space Component | Complexity | Description |
| :--- | :---: | :--- |
| **Auxiliary Memory** | $\mathcal{O}(1)$ | Sorts completely in-place without auxiliary arrays. |
| **Recursion Stack** | $\mathcal{O}(\log N)$ | Tail-recursive call depth of `max_heapify` (or $\mathcal{O}(1)$ if iterative). |

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
Enter number of random elements (N): 0
Invalid input! Try again: -2
Invalid input! Try again: 15
Enter limits between which random numbers should be: 5000 1000
Invalid Input! Try again.
Enter limits between which random numbers should be: 300 600

Unsorted preview: {509, 423, 533, 465, 399, 323, 540, 600, 460, 541, 484, 315, 310, 537, 325}
Sorted preview: {310, 315, 323, 325, 399, 423, 460, 465, 484, 509, 533, 537, 540, 541, 600}

Execution Time: 0.0060 ms
Total Comparisons: 54
Total Swaps: 22
```

### Generated Files

**`unsorted.txt`:**
```text
15
509 423 533 465 399 323 540 600 460 541 484 315 310 537 325 
```

**`sorted.txt`:**
```text
15
310 315 323 325 399 423 460 465 484 509 533 537 540 541 600 
```
