# Question 2: 0/1 Knapsack Problem using Dynamic Programming

## 📌 Problem Overview
Given $n$ items, each with a specific weight and a profit, and a knapsack of maximum capacity $W$, determine the maximum profit that can be obtained by selecting a subset of the items such that their total weight does not exceed $W$.

In the **0/1 Knapsack problem**, items cannot be broken down; you must either include the entire item (1) or exclude it (0).

---

## 💡 Why Dynamic Programming?

### ❌ Naive Recursive Approach
The naive approach generates all subsets (or combinations) of items and calculates the total weight and profit for each. 
- **Time Complexity:** $\mathcal{O}(2^n)$ (Exponential)
- **Space Complexity:** $\mathcal{O}(n)$ (Call stack depth)

### ✅ Dynamic Programming (Tabulation) Approach
By using a 2D array (table) `dp[i][w]`, we can store the maximum profit that can be achieved using the first $i$ items and a maximum weight limit of $w$.
The state transition is:
$$dp[i][w] = \max(dp[i-1][w], \text{profit}[i-1] + dp[i-1][w-\text{weight}[i-1]])$$

- **Time Complexity:** $\mathcal{O}(n \times W)$ (Pseudo-polynomial)
- **Space Complexity:** $\mathcal{O}(n \times W)$

---

## 🛠️ Implementation Details

The implementation in [`main.c`](./main.c) includes:
1. **Dynamic Memory Allocation:** Allocates `weights` and `profits` arrays, as well as the 2D DP table, using `malloc()`.
2. **Interactive Input Handling:** Uses strict input validation loops to clear the buffer and ensure only positive integers are accepted for item counts and capacities.
3. **Tabulation Loop:** Iteratively computes the optimal profit values for **all** capacities up to $W$.
4. **Display Helper:** Custom formatting to print the item arrays cleanly.

---

## 🔍 Example Walkthrough

**Input:**
- Number of items: `3`
- Weights: `{10, 20, 30}`
- Profits: `{60, 100, 120}`
- Knapsack Capacity: `50`

**Tabulation:**
The algorithm builds the DP table and evaluates whether including the current item yields a higher profit than excluding it. For capacity `50`, the optimal choice is to pick item 2 (weight 20) and item 3 (weight 30).

**Result:** Maximum Profit = `220`

---

## ⚙️ Compilation & Execution

To compile and run the program:

```bash
# Compile
gcc -o main main.c

# Run
./main
```

---


### 📤 Sample Output
```text
Enter the number of items (> 0): 3
Enter weight and profit for item 1 (space separated): 10 60
Enter weight and profit for item 2 (space separated): 20 100
Enter weight and profit for item 3 (space separated): 30 120
Enter the knapsack capacity (> 0): 50
Weights: {10, 20, 30}
Profits: {60, 100, 120}
Maximum profit is: 220
```

---

## 📊 Complexity Summary

| Approach | Time Complexity | Space Complexity |
| :--- | :---: | :---: |
| Naive Recursion | $\mathcal{O}(2^n)$ | $\mathcal{O}(n)$ |
| **DP (Tabulation)** | **$\mathcal{O}(n \times W)$** | **$\mathcal{O}(n \times W)$** |
