# Q6 - Point in Maximum Intervals (Application of Sorting VI)

## 📌 Problem Statement
Given a set $S$ of $n$ intervals on a 1D line, where each interval is described by its left and right endpoints $[l_i, r_i]$ with $l_i \le r_i$, find a point $p$ on the line that belongs to the maximum number of intervals. Endpoints are inclusive (i.e., an endpoint counts as being inside its interval).

The algorithm must run in worst-case **$\mathcal{O}(n \log n)$ time complexity** and be implemented in C.

---

## 💡 Algorithm & Approach

Instead of testing continuous points across the line, the number of overlapping intervals only changes at interval endpoints. We utilize an **Event-Driven Sweep-Line Algorithm**:

1. **Event Decomposition:**
   - Convert each interval $[l_i, r_i]$ into two discrete events:
     - **Start Event:** $(\text{point} = l_i, \text{type} = +1)$
     - **End Event:** $(\text{point} = r_i, \text{type} = -1)$
   - Allocate an array of $2n$ events.

2. **Sorting Events with Inclusive Endpoint Handling ($\mathcal{O}(n \log n)$):**
   - Sort the $2n$ events in ascending order of coordinate `point`.
   - **Critical Tie-Breaker:** When two events share the same coordinate (e.g., one interval ends at $x$ and another starts at $x$), the **Start event (`+1`) must precede the End event (`-1`)** because closed intervals include their endpoints.

3. **Sweep-Line Linear Scan ($\mathcal{O}(n)$):**
   - Initialize `count = 0`, `maxCount = 0`, and `p = 0`.
   - Iterate through the sorted events:
     - Update active interval count: `count += events[i].type`.
     - Whenever `count > maxCount`:
       - `maxCount = count`
       - `p = events[i].point`

$$\text{Total Time Complexity} = \underbrace{\mathcal{O}(n \log n)}_{\text{Sorting } 2n \text{ Events}} + \underbrace{\mathcal{O}(n)}_{\text{Linear Sweep Scan}} = \mathbf{\mathcal{O}(n \log n)}$$

---

## ⏱️ Complexity Analysis

| Metric | Complexity | Description |
| :--- | :---: | :--- |
| **Event Creation** | $\mathcal{O}(n)$ | Generating $2n$ start and end events from $n$ intervals. |
| **Sorting** | $\mathcal{O}(n \log n)$ | Sorting $2n$ events using `qsort` with tie-breaking. |
| **Linear Sweep** | $\mathcal{O}(n)$ | Single pass over $2n$ events accumulating prefix sums. |
| **Total Time Complexity** | $\mathcal{O}(n \log n)$ | Strictly bounded by $\mathcal{O}(n \log n)$. |
| **Space Complexity** | $\mathcal{O}(n)$ | Dynamically allocated memory for $2n$ `Event` structs. |

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
Enter number of intervals (n): 4

Enter left and right endpoints for each interval (li ri):
Interval 1: 1 4
Interval 2: 2 5
Interval 3: 3 6
Interval 4: 5 9
```

**Output:**
```text
Recorded 8 events:
{(1, Start), (4, End), (2, Start), (5, End), (3, Start), (6, End), (5, Start), (9, End)}

Sorted events:
{(1, Start), (2, Start), (3, Start), (4, End), (5, Start), (5, End), (6, End), (9, End)}

Point in maximum intervals: p = 3 (overlaps with 3 intervals)
```

### Step-by-Step Trace Walkthrough

| Point | Event Type | Delta | Running Overlap (`count`) | Peak (`maxCount`, `p`) | Active Intervals at Point |
| :---: | :---: | :---: | :---: | :---: | :---: |
| **1** | Start | $+1$ | $1$ | $(1, 1)$ | $\{[1, 4]\}$ |
| **2** | Start | $+1$ | $2$ | $(2, 2)$ | $\{[1, 4], [2, 5]\}$ |
| **3** | Start | $+1$ | **3** | **$(3, 3)$ (Max)** | $\{[1, 4], [2, 5], [3, 6]\}$ |
| **4** | End | $-1$ | $2$ | $(3, 3)$ | $\{[2, 5], [3, 6]\}$ |
| **5** | Start | $+1$ | **3** | $(3, 3)$ | $\{[2, 5], [3, 6], [5, 9]\}$ *(Tie processed first)* |
| **5** | End | $-1$ | $2$ | $(3, 3)$ | $\{[3, 6], [5, 9]\}$ |
| **6** | End | $-1$ | $1$ | $(3, 3)$ | $\{[5, 9]\}$ |
| **9** | End | $-1$ | $0$ | $(3, 3)$ | $\emptyset$ |
