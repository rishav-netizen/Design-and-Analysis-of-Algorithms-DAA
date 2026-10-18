# Set 1: Dynamic Programming

This directory contains solutions for the dynamic programming problems provided in the image assignment.

📄 **View the question set here:** [`questions.png`](../questions.png)

## Questions Overview

### [Q1: Fibonacci Number](./Q1/main.c)
Finds the $n$-th Fibonacci number using Dynamic Programming (Bottom-Up / Tabulation). This avoids the exponential time complexity of the naive recursive approach by storing previously computed values.
- **Time Complexity:** $O(n)$
- **Space Complexity:** $O(n)$

### [Q2: 0/1 Knapsack Problem](./Q2/main.c)
Given $n$ items with their weights and profits, and a knapsack of capacity $W$, this program determines the maximum profit that can be obtained.
- **Time Complexity:** $O(n \times W)$
- **Space Complexity:** $O(n \times W)$

### [Q3: Longest Common Subsequence (LCS)](./Q3/main.c)
Given two strings, this program finds the length of their longest common subsequence and displays the subsequence itself using a backtracking path on the DP table.
- **Time Complexity:** $O(m \times n)$
- **Space Complexity:** $O(m \times n)$

### [Q4: Matrix Chain Multiplication (MCM)](./Q4/main.c)
Given the dimensions of $N-1$ matrices in an array, this program determines the minimum number of scalar multiplications required to multiply the complete matrix chain optimally.
- **Time Complexity:** $O(N^3)$
- **Space Complexity:** $O(N^2)$
