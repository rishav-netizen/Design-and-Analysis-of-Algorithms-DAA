# Q6 — The Best Time to be Alive

## 📌 Problem Statement

> **[The best time to be alive]**  
> An editor of *The History of the World Science* wants to find out the time when the largest number of prominent scientists were alive. The prominent scientists are, by definition, the people mentioned in the book with the dates of their birth and death. (No living scientists are included in the book.)
> 
> Devise an algorithm for this task if it has the book’s index as its input. The entries in the index are sorted alphabetically and give the persons’ birth and death years. If a person A died the same year person B was born, assume that the former event happened before the latter one.
>
> By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## 💡 Algorithmic Approach: Sweep-Line Event Processing

### 1. Modeling as Interval Overlap
Each prominent scientist $i$ lived over the interval $[\text{birth}_i, \text{death}_i]$.  
We want to find the year $Y$ that is covered by the maximum number of intervals.

### 2. Handling the Boundary Condition
The problem explicitly specifies:
> *"If a person A died the same year person B was born, assume that the former event happened before the latter one."*

This means:
- If person A dies in year $Y$ and person B is born in year $Y$, person A's departure is recorded **before** person B's arrival.
- Consequently, they are **not** considered concurrently alive in year $Y$.

### 3. Event Transformation & Sorting
We decompose each scientist's lifespan into two discrete events:
1. **Birth event:** $(\text{year} = \text{birth}_i, \text{type} = +1)$
2. **Death event:** $(\text{year} = \text{death}_i, \text{type} = -1)$

#### Sorting Rules:
1. Primary criterion: Sort by `year` ascending.
2. Tie-breaking criterion: If two events share the same `year`, place the **death event** (`-1`) before the **birth event** (`+1`).

### 4. Linear Sweep
We iterate through the sorted event list:
- Maintain a running counter `curr_alive += event.type`.
- If `curr_alive > max_alive`, update `max_alive` and record `best_year = event.year`.

---

## 🛠️ Input Representation

In [`main.c`](file:///Users/rishav07/Documents/college/SEM3/DAA/LAB7/Q6/main.c):
- `Scientist` struct: Holds `name`, `birth`, and `death` year.
- `Event` struct: Holds `year`, `type` (`+1` for birth, `-1` for death), and reference `id`.
- Uses `qsort()` with a custom comparator ensuring proper tie-breaking.

---

## ⏱️ Complexity Analysis

| Step | Operation | Time Complexity | Space Complexity |
| :--- | :--- | :---: | :---: |
| 1 | Create $2N$ events from $N$ scientists | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ |
| 2 | Sort $2N$ events using `qsort` | $\mathcal{O}(N \log N)$ | $\mathcal{O}(\log N)$ |
| 3 | Sweep through events to find maximum | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ |
| **Total** | **End-to-End Algorithm** | $\mathbf{\mathcal{O}(N \log N)}$ | $\mathbf{\mathcal{O}(N)}$ |

---

## ⚙️ Compilation & Execution

```bash
# Compile
gcc -Wall -Wextra -O2 main.c -o main

# Run
./main
```

---

## 🧪 Sample Output

```text
Index of prominent scientists in database:
 1. Galileo Galilei        [1564 - 1642]
 2. Isaac Newton           [1643 - 1727]
 3. Johannes Kepler        [1571 - 1630]
 4. Rene Descartes         [1596 - 1650]
 5. Blaise Pascal          [1623 - 1662]
 6. Robert Boyle           [1627 - 1691]
 7. Robert Hooke           [1635 - 1703]
 8. Gottfried Leibniz      [1646 - 1716]
 9. Leonhard Euler         [1707 - 1783]
10. Carl Friedrich Gauss   [1777 - 1855]
11. James Clerk Maxwell    [1831 - 1879]
12. Charles Darwin         [1809 - 1882]
13. Albert Einstein        [1879 - 1955]
14. Niels Bohr             [1885 - 1962]
15. Max Planck             [1858 - 1947]

--- Results ---
Peak year: 1646
Maximum prominent scientists alive simultaneously: 6
Scientists alive in 1646:
  - Isaac Newton (1643 - 1727)
  - Rene Descartes (1596 - 1650)
  - Blaise Pascal (1623 - 1662)
  - Robert Boyle (1627 - 1691)
  - Robert Hooke (1635 - 1703)
  - Gottfried Leibniz (1646 - 1716)
```
