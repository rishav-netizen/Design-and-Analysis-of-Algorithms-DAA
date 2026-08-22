# Q1 - Stable Color Sort (Application of Sorting I)

## 📌 Problem Statement
Given $n$ pairs of items as input, where each item consists of a **number** and a **color** ($\text{Red}$, $\text{Blue}$, or $\text{Yellow}$). The input pairs are initially sorted in non-decreasing order by number.

The objective is to sort the items by color such that:
1. All **Red** items appear before all **Blue** items, which appear before all **Yellow** items ($\text{Red} \to \text{Blue} \to \text{Yellow}$).
2. For items sharing the same color, their original sorted order by number is preserved (**Stability**).
3. The algorithm runs in **$O(n)$ time complexity**.

---

## 💡 Algorithm & Approach

Since the items are already sorted by number, achieving the target ordering requires a **stable partition / counting sort** based on the 3 discrete colors:

1. **Pass 1 (Count Frequency):**
   - Traverse the input array once to count the total occurrences of Red ($R$) and Blue ($B$).
   - Determine bucket starting indices:
     - `red_index` = $0$
     - `blue_index` = $R$
     - `yellow_index` = $R + B$

2. **Pass 2 (Stable Linear Placement):**
   - Allocate an auxiliary array of size $n$.
   - Iterate through the input array from left to right. Because the elements are visited in increasing order of their numbers, placing each color into its respective bucket index maintains stability.
   - Increment the respective bucket index after placing each item.

3. **Copy Back & Cleanup:**
   - Copy the elements from the auxiliary array back to the original array and free the allocated auxiliary memory.

> **Why not Dutch National Flag (DNF)?**  
> While Dijkstra's 3-way partitioning (Dutch National Flag) sorts in-place with $O(1)$ extra space, standard in-place swapping is **unstable** and disrupts the numerical order of identical colors. The linear auxiliary buffer approach ensures strict stability.

---

## ⏱️ Complexity Analysis

| Metric | Complexity | Description |
| :--- | :---: | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | Two linear passes over $n$ items: counting and placement. |
| **Space Complexity** | $\mathcal{O}(n)$ | Single auxiliary buffer of size $n$ to guarantee stability. |

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
How many pairs do you want in the array?: 6
Now enter the items, number followed by color's initial.
Item 1: 1 B
Item 2: 2 R
Item 3: 4 Y
Item 4: 5 R
Item 5: 7 B
Item 6: 9 Y
```

**Output:**
```text
Unsorted: {(1, B), (2, R), (4, Y), (5, R), (7, B), (9, Y)}
Sorted: {(2, R), (5, R), (1, B), (7, B), (4, Y), (9, Y)}
```
