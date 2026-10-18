# Q5 - Merge Overlapping Intervals (Application of Sorting V)

## 📌 Problem Statement
Given a list $I$ of $n$ intervals specified as $(x_i, y_i)$ pairs where $x_i < y_i$, merge all overlapping intervals and return a consolidated list of non-overlapping intervals.

The algorithm must run in worst-case **$\mathcal{O}(n \log n)$ time complexity** and be implemented in C with suitable input/output representations.

---

## 💡 Algorithm & Approach

A naive pairwise comparison would require $\mathcal{O}(n^2)$ time. By sorting intervals beforehand, all potentially overlapping intervals become adjacent, allowing a single linear pass:

1. **Interval Representation:**
   - Define a `struct Interval` containing `start` ($x_i$) and `end` ($y_i$).

2. **Sorting by Start Time ($\mathcal{O}(n \log n)$):**
   - Sort the array of intervals in non-decreasing order of their `start` values using `qsort`.
   - Sorting guarantees that for any two intervals $I_a$ and $I_b$ with $a < b$, $I_a.\text{start} \le I_b.\text{start}$.

3. **Linear Merge Sweep ($\mathcal{O}(n)$):**
   - Initialize an active interval `current = I[0]`.
   - Iterate through the remaining intervals from $i = 1$ to $n - 1$:
     - **Overlap Case (`I[i].start <= current.end`):**  
       The next interval overlaps with or connects to `current`. Expand `current.end` to $\max(\text{current.end}, I[i].\text{end})$.
     - **Disjoint Case (`I[i].start > current.end`):**  
       There is a gap between `current` and $I[i]$. Since all subsequent intervals start even later, `current` is finalized. Append `current` to `result` and set `current = I[i]`.
   - After the loop finishes, append the last remaining `current` to `result`.

$$\text{Total Time Complexity} = \underbrace{\mathcal{O}(n \log n)}_{\text{Sorting by Start Time}} + \underbrace{\mathcal{O}(n)}_{\text{Linear Merge Sweep}} = \mathbf{\mathcal{O}(n \log n)}$$

---

## ⏱️ Complexity Analysis

| Metric | Complexity | Description |
| :--- | :---: | :--- |
| **Sorting** | $\mathcal{O}(n \log n)$ | Sorting $n$ intervals based on starting endpoint via `qsort`. |
| **Merging Pass** | $\mathcal{O}(n)$ | Single forward scan comparing adjacent interval boundaries. |
| **Total Time Complexity** | $\mathcal{O}(n \log n)$ | Dominated by the initial sorting stage. |
| **Space Complexity** | $\mathcal{O}(n)$ | Dynamically allocated memory for input array `I` and `result` array. |

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
Enter number of intervals: 4
Enter interval 1 start and end time: 1 3
Enter interval 2 start and end time: 2 6
Enter interval 3 start and end time: 8 10
Enter interval 4 start and end time: 7 18
```

**Output:**
```text
{(1, 3), (2, 6), (8, 10), (7, 18)}
{(1, 6), (7, 18)}
```

### Step-by-Step Trace

| Step | Next Interval $I[i]$ | Condition | Action | Active `current` | `result` List |
| :---: | :---: | :---: | :---: | :---: | :---: |
| **Init** | $(1, 3)$ | — | Initial candidate | $(1, 3)$ | `[]` |
| **$i=1$** | $(2, 6)$ | $2 \le 3$ (Overlap) | $\text{end} = \max(3, 6) = 6$ | $(1, 6)$ | `[]` |
| **$i=2$** | $(7, 18)$ | $7 > 6$ (Disjoint) | Save $(1, 6)$; new candidate | $(7, 18)$ | `[(1, 6)]` |
| **$i=3$** | $(8, 10)$ | $8 \le 18$ (Overlap) | $\text{end} = \max(18, 10) = 18$ | $(7, 18)$ | `[(1, 6)]` |
| **End** | — | End of array | Flush last candidate $(7, 18)$ | — | **`[(1, 6), (7, 18)]`** |
