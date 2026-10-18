# Question 3: Longest Common Subsequence (LCS)

## 📌 Problem Overview
Write a program to implement the **Longest Common Subsequence (LCS)** algorithm using Dynamic Programming. Given two strings, find the length of their longest common subsequence and display the actual subsequence.

A **subsequence** is a sequence that appears in the same relative order, but not necessarily contiguous. For example, "abc" is a subsequence of "ahbgdc".

---

## 💡 Why Dynamic Programming?

### ❌ Naive Recursive Approach
Comparing every possible subsequence of both strings leads to enormous repeated work.
- **Time Complexity:** $\mathcal{O}(2^m \times 2^n)$ (Exponential)
- **Space Complexity:** $\mathcal{O}(m+n)$ (Call stack)

### ✅ Dynamic Programming (Tabulation) Approach
We can define a 2D table `dp[i][j]` that represents the length of the LCS of the prefixes of length $i$ and $j$ from the two strings.
- If characters match: `dp[i][j] = 1 + dp[i-1][j-1]`
- If characters differ: `dp[i][j] = max(dp[i-1][j], dp[i][j-1])`

- **Time Complexity:** $\mathcal{O}(m \times n)$
- **Space Complexity:** $\mathcal{O}(m \times n)$

---

## 🛠️ Implementation Details

The implementation in [`main.c`](./main.c) uses:
1. **Dynamic 2D DP Table:** Allocated securely using `malloc()`.
2. **Backtracking the Table:** Once the DP table is filled, the code traces back from `dp[m][n]` to `dp[0][0]` to construct the string of the Longest Common Subsequence.
3. **Interactive String Input:** Uses standard I/O buffer flushing to accept multi-character alphanumeric sequences reliably.

---

## 🔍 Example Walkthrough

**Input:**
- String 1: `ABCBDAB`
- String 2: `BDCABA`

**Tabulation Steps:**
The table calculates the local maximum common string length. Upon hitting `dp[7][6] = 4`, the algorithm performs a reverse trace. It looks for diagonal jumps (which represent a matched character).

**Result:**
- LCS Length: `4`
- Subsequence: `BCBA` (or `BDAB` depending on tie-breakers)

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
Enter the first string (max 999 characters): ABCBDAB
Enter the second string (max 999 characters): BDCABA
Length of Longest Common Subsequence: 4
Longest Common Subsequence: BCBA
```

---

## 📊 Complexity Summary

| Phase | Time Complexity | Space Complexity |
| :--- | :---: | :---: |
| **DP Table Construction** | **$\mathcal{O}(m \times n)$** | **$\mathcal{O}(m \times n)$** |
| **Backtracking (String Creation)** | **$\mathcal{O}(m + n)$** | **$\mathcal{O}(\max(m, n))$** |
