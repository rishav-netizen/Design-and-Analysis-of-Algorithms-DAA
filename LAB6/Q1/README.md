# Question 1: N-th Fibonacci Number using Dynamic Programming

## 📌 Problem Overview
Write a program to find the $n$-th Fibonacci number using **Dynamic Programming (Bottom-Up / Tabulation)**.

The Fibonacci sequence is a series of numbers where each number is the sum of the two preceding ones:
$$F(n) = \begin{cases} 0 & \text{if } n = 0 \\ 1 & \text{if } n = 1 \\ F(n-1) + F(n-2) & \text{if } n \ge 2 \end{cases}$$

---

## 💡 Why Dynamic Programming?

### ❌ Naive Recursive Approach
A standard recursive implementation evaluates subproblems repeatedly:
```
               F(5)
             /      \
          F(4)      F(3)
         /    \    /    \
      F(3)   F(2) F(2)  F(1)
```
- **Time Complexity:** $\mathcal{O}(2^n)$ (Exponential)
- **Space Complexity:** $\mathcal{O}(n)$ (Call stack depth)

### ✅ Dynamic Programming (Tabulation) Approach
By computing values bottom-up from base cases ($F(0)$ and $F(1)$) and storing them in an array `F`, every value from $0$ to $n$ is computed **exactly once**.

- **Time Complexity:** $\mathcal{O}(n)$ (Linear)
- **Space Complexity:** $\mathcal{O}(n)$ (Array storage)

---

## 🛠️ Implementation Details

The implementation in [`main.c`](file:///Users/rishav07/Documents/college/SEM3/DAA/LAB6/Q1/main.c) uses:
1. **Dynamic Memory Allocation:** Allocates an array `F` of size `n + 1` using `calloc()` (initialized to zero).
2. **64-bit Integers (`long long`):** Prevents early integer overflow for higher Fibonacci numbers.
3. **Tabulation Loop:** Iteratively calculates $F[i] = F[i-1] + F[i-2]$ from $i = 2$ up to $n$.
4. **Display Helper Function:** Prints the full DP table for verification.

---

## 🔍 Example Walkthrough

For **$n = 6$**:

1. **Initialization:**
   - `F[0] = 0`
   - `F[1] = 1`

2. **Tabulation Steps:**
   - $F[2] = F[1] + F[0] = 1 + 0 = 1$
   - $F[3] = F[2] + F[1] = 1 + 1 = 2$
   - $F[4] = F[3] + F[2] = 2 + 1 = 3$
   - $F[5] = F[4] + F[3] = 3 + 2 = 5$
   - $F[6] = F[5] + F[4] = 5 + 3 = 8$

3. **Output DP Array:**
   `{0, 1, 1, 2, 3, 5, 8}`

4. **Result:** $F(6) = 8$

---

## ⚙️ Compilation & Execution

To compile and run the program:

```bash
# Compile
gcc -o main main.c

# Run
./main
```

### 📥 Input
```
Enter which fibonacci number you wanna get: 6
```

### 📤 Sample Output
```text
F(6) = 8
{0, 1, 1, 2, 3, 5, 8}
```

---

## 📊 Complexity Summary

| Approach | Time Complexity | Space Complexity |
| :--- | :---: | :---: |
| Naive Recursion | $\mathcal{O}(2^n)$ | $\mathcal{O}(n)$ |
| **DP (Tabulation)** | **$\mathcal{O}(n)$** | **$\mathcal{O}(n)$** |
| DP (Space-Optimized) | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ |
