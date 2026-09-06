# Question 4: Matrix Chain Multiplication (MCM)

## 📌 Problem Overview
Write a program to implement **Matrix Chain Multiplication** using Dynamic Programming. Given an array `arr[]` representing the dimensions of $N-1$ matrices, determine the minimum number of scalar multiplications required to multiply the complete matrix chain.

Multiplying an $A \times B$ matrix by a $B \times C$ matrix takes $A \times B \times C$ operations. Matrix multiplication is associative, so the order of grouping (parenthesizing) heavily impacts performance.

---

## 💡 Why Dynamic Programming?

### ❌ Naive Recursive Approach
Evaluating all possible parenthesization combinations is extremely slow, as the number of ways is related to the Catalan number.
- **Time Complexity:** $\mathcal{O}(2^n)$ (Exponential)
- **Space Complexity:** $\mathcal{O}(n)$

### ✅ Dynamic Programming (Tabulation) Approach
By calculating the optimal cost for smaller subchains first and using those to calculate larger chains, we can evaluate the optimal cost efficiently.
We use a table `m[i][j]` to store the minimum cost of multiplying matrices from $i$ to $j$.
$$m[i][j] = \min_{i \le k < j} \{ m[i][k] + m[k+1][j] + P_{i-1}P_kP_j \}$$

- **Time Complexity:** $\mathcal{O}(N^3)$
- **Space Complexity:** $\mathcal{O}(N^2)$

---

## 🛠️ Implementation Details

The implementation in [`main.c`](./main.c) uses:
1. **Dynamic Memory Allocation:** Properly handles variable chain lengths without overflowing the stack.
2. **Chain Length Iteration:** Calculates costs iteratively from chain length 2 up to $N$.
3. **Format & Clean IO:** Captures the dimensions cleanly and prints using a predefined `Display` formatter.

---

## 🔍 Example Walkthrough

**Input:**
- Dimension array size: `4`
- Array values: `{10, 30, 5, 60}`

This represents 3 matrices:
1. $10 \times 30$
2. $30 \times 5$
3. $5 \times 60$

**Tabulation Steps:**
The algorithm compares grouping $(A \times B) \times C$ vs $A \times (B \times C)$:
- $(A \times B) \times C = (10 \times 30 \times 5) + (10 \times 5 \times 60) = 1500 + 3000 = 4500$
- $A \times (B \times C) = (30 \times 5 \times 60) + (10 \times 30 \times 60) = 9000 + 18000 = 27000$

**Result:** Minimum multiplications = `4500`

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
Enter the number of elements in the dimensions array (minimum 2): 4
Enter the elements of the dimensions array:
Element 1: 10
Element 2: 30
Element 3: 5
Element 4: 60
Dimensions array: {10, 30, 5, 60}
Minimum number of scalar multiplications: 4500
```

---

## 📊 Complexity Summary

| Phase | Time Complexity | Space Complexity |
| :--- | :---: | :---: |
| **DP Matrix Fill** | **$\mathcal{O}(N^3)$** | **$\mathcal{O}(N^2)$** |
