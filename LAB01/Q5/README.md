

# 🚀 DAA Lab 1 - Question 5

<div align="center">

# 🔍 Find the Partition Point

**Design and Analysis of Algorithms - Lab 1**

<img src="https://img.shields.io/badge/Language-C-blue.svg"/>
<img src="https://img.shields.io/badge/Algorithm-Binary_Search-success"/>
<img src="https://img.shields.io/badge/Time_Complexity-O(log_n)-orange"/>
<img src="https://img.shields.io/badge/Space_Complexity-O(1)-brightgreen"/>
<img src="https://img.shields.io/badge/Status-Completed-success"/>

</div>

---

## 📖 Problem Statement

> Consider an array **A** with **n** elements containing a run of **0's** followed by a run of **1's**. Implement a method to find the **exact partition (transition) point** between them.

### Example

```text
Input Array:
{0, 0, 0, 0, 1, 1, 1, 1}

Partition Point Index = 4
```

---

## 💡 Approach

Since the array is **sorted** (all `0`s followed by all `1`s), a **Binary Search** is used instead of scanning the array linearly.

The algorithm repeatedly:

- Computes the middle element.
- Checks whether the middle value is `1`.
- Narrows the search space accordingly.
- Returns the index where the transition begins.

This reduces the search time from **O(n)** to **O(log n)**.

---

## ⚙️ Algorithm

1. Read the size of the array.
2. Read the number of `1`s.
3. Construct a binary array containing `0`s followed by `1`s.
4. Apply Binary Search to locate the first occurrence of `1`.
5. Print the partition index.

---

## 📂 Project Structure

```text
Q5/
├── README.md
└── main.c
```

---

## 📄 Source Files

| File | Description |
|------|-------------|
| 📄 [main.c](./main.c) | C implementation using Binary Search to locate the partition point. |
| 📘 [README.md](./README.md) | Documentation for Question 5. |

---

## ▶️ Compilation

```bash
gcc main.c -o q5
./q5
```

---

## 🖥️ Sample Run

```text
Enter the size of array: 10
Enter the number of ones: 4

{0, 0, 0, 0, 0, 0, 1, 1, 1, 1}

Index of partition is: 6
```

---

## ⏱️ Complexity Analysis

| Operation | Complexity |
|-----------|------------|
| Time | **O(log n)** |
| Space | **O(1)** |

---

## 📚 Concepts Used

- Binary Search
- Divide and Conquer
- Arrays
- Dynamic Memory Allocation (`malloc`)
- Time Complexity Analysis

---

## 🛠️ Technologies

- C
- GCC Compiler
- Standard C Library (`stdio.h`, `stdlib.h`)

---

## 🏷️ Tags

`C` `Binary Search` `DAA` `Algorithms` `Arrays` `Divide and Conquer` `Lab 1` `Problem Solving` `Time Complexity`

---

<div align="center">

### ⭐ If you found this repository helpful, consider giving it a star!

Made with ❤️ for **Design and Analysis of Algorithms Lab**

</div>