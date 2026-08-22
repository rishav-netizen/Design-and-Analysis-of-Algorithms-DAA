# Q4 - Maximum Simultaneous Party Guests (Application of Sorting IV)

## 📌 Problem Statement
A camera at the door of a party tracks the entry time $a_i$ and exit time $b_i$ (where $b_i > a_i$) for each of $n$ attendees $p_i$. All entry and exit times across all attendees are distinct (no ties).

The objective is to design an algorithm running in **$\mathcal{O}(n \log n)$ time complexity** to determine the exact time when the maximum number of people were simultaneously present at the party, and implement it in C.

---

## 💡 Algorithm & Approach

A naive approach of checking every timestamp or testing interval overlaps pairwise would take $\mathcal{O}(n^2)$ time. Instead, we use an **Event-Driven Sweep-Line Algorithm**:

1. **Event Representation:**
   - Decompose each person's attendance interval $[a_i, b_i]$ into two discrete chronological events:
     - **Entry Event:** $(\text{time} = a_i, \text{type} = +1)$ — a person arrives.
     - **Exit Event:** $(\text{time} = b_i, \text{type} = -1)$ — a person leaves.
   - For $n$ persons, create an array of $2n$ events.

2. **Sorting Events:**
   - Sort all $2n$ events in ascending order of their `time` using `qsort` ($\mathcal{O}(2n \log(2n)) = \mathcal{O}(n \log n)$).
   - Because all timestamps are strictly distinct, there are no simultaneous entry/exit conflicts to resolve.

3. **Sweep-Line Linear Scan:**
   - Initialize `count = 0`, `maxCount = 0`, and `maxTime = 0`.
   - Sweep through the sorted events from left to right:
     - Update running attendance: `count += events[i].type`.
     - If `count > maxCount`:
       - `maxCount = count`
       - `maxTime = events[i].time`

$$\text{Total Time Complexity} = \underbrace{\mathcal{O}(n)}_{\text{Input / Event Creation}} + \underbrace{\mathcal{O}(n \log n)}_{\text{Sorting } 2n \text{ Events}} + \underbrace{\mathcal{O}(n)}_{\text{Linear Sweep}} = \mathbf{\mathcal{O}(n \log n)}$$

---

## ⏱️ Complexity Analysis

| Metric | Complexity | Description |
| :--- | :---: | :--- |
| **Event Creation** | $\mathcal{O}(n)$ | Converting $n$ person intervals into $2n$ discrete events. |
| **Sorting** | $\mathcal{O}(n \log n)$ | Sorting $2n$ events chronologically using `qsort`. |
| **Linear Sweep** | $\mathcal{O}(n)$ | Single pass over $2n$ events to compute prefix sums. |
| **Total Time Complexity** | $\mathcal{O}(n \log n)$ | Dominated by the sorting phase. |
| **Space Complexity** | $\mathcal{O}(n)$ | Dynamically allocated array of size $2n$ for the events. |

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
Enter the number of persons attending the party (n): 4

Enter entry and exit times for each person (ai bi):
Person 1: 1 5
Person 2: 2 6
Person 3: 4 8
Person 4: 7 10
```

**Output:**
```text
Recorded 8 events:
{(1, Entry), (5, Exit), (2, Entry), (6, Exit), (4, Entry), (8, Exit), (7, Entry), (10, Exit)}

Max people 3 at time: 4
```

### Trace Walkthrough

| Time | Event Type | Delta | Running Count (`count`) | Peak (`maxCount`, `maxTime`) |
| :---: | :---: | :---: | :---: | :---: |
| **1** | Entry | $+1$ | $1$ | $(1, 1)$ |
| **2** | Entry | $+1$ | $2$ | $(2, 2)$ |
| **4** | Entry | $+1$ | **3** | **$(3, 4)$ (Max)** |
| **5** | Exit | $-1$ | $2$ | $(3, 4)$ |
| **6** | Exit | $-1$ | $1$ | $(3, 4)$ |
| **7** | Entry | $+1$ | $2$ | $(3, 4)$ |
| **8** | Exit | $-1$ | $1$ | $(3, 4)$ |
| **10** | Exit | $-1$ | $0$ | $(3, 4)$ |
