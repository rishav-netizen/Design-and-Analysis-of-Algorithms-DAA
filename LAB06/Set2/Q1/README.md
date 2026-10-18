# Question 1: 1D Array Operations and Their Complexities

## 📌 Problem Overview
Given an array with $n$ unsorted integer elements, the objective is to write a C program to perform multiple statistical and structural operations and formally analyze their worst-case computational complexity in terms of $n$.

---

## 🛠️ Implementation Details
The codebase in [`main.c`](./main.c) provides a robust suite of functions:
1. **Interactive Menu Generation:** Offers manual array insertion vs random generation mapping back to earlier lab styles.
2. **Math Inclusion:** Requires the `<math.h>` standard library for accurate Standard Deviation derivations.
3. **Modular Construction:** All array operations are encapsulated in individual functions (`FindMax`, `FindMean`, etc.) adhering strictly to `PascalCase`.

---

## ⚙️ Compilation & Execution

Since `<math.h>` is used, the math library flag `-lm` is strictly required during compilation.

```bash
# Compile
gcc -o main main.c -lm

# Run
./main
```

---


### 📤 Sample Output
```text
Enter number of elements in array: 5
Choose input method:
1. Manual Input
2. Random Generation
Enter choice: 1
Enter 5 integers:
10 30 20 50 40

--- 1D Array Operations ---
1. Find Maximum
...
4. Find Median
...
Enter your choice: 4
Median: 30.00

--- 1D Array Operations ---
...
Enter your choice: 9
Pivot element 40 randomly chosen and placed at index 3
Array after partitioning: {10, 30, 20, 40, 50}

--- 1D Array Operations ---
...
Enter your choice: 0
Exiting...
```

---

## 📊 Complexity Summary & Analysis

| Operation | Worst-Case Time Complexity | Space Complexity | Description |
| :--- | :---: | :---: | :--- |
| **(i) Find Max Element** | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ | Single linear scan keeping track of the highest integer. |
| **(ii) 1st & 2nd Largest** | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ | Single linear scan keeping track of two separate max trackers. |
| **(iii) Find Mean** | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ | Summing all elements in a single pass, then dividing by $n$. |
| **(iv) Find Median** | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n)$ | Uses QuickSort to order a temporary array and extract the middle element. |
| **(v) Standard Deviation**| $\mathcal{O}(n)$ | $\mathcal{O}(1)$ | Two passes: One for mean, one for summation of variance differences. |
| **(vi) Find Mode** | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n)$ | Uses QuickSort to group elements, then scans linearly to find highest frequency. |
| **(vii) Remove Duplicates**| $\mathcal{O}(n^2)$ | $\mathcal{O}(1)$ | Iterating through elements and dynamically shifting elements left on collision. |
| **(viii) Reverse Array** | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ | Two-pointer approach swapping from edges to the center. |
| **(ix) Partition (Pivot)**| $\mathcal{O}(n)$ | $\mathcal{O}(1)$ | Hoare's or Lomuto's partition mechanism separating elements relative to a pivot. |
