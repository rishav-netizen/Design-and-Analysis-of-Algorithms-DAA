# 🔗 Q1.3 — Unsorted Singly Linked List Dictionary

<div align="center">

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Git](https://img.shields.io/badge/Git-F05032?style=for-the-badge&logo=git&logoColor=white)
![GitHub](https://img.shields.io/badge/GitHub-181717?style=for-the-badge&logo=github&logoColor=white)
![Structure](https://img.shields.io/badge/Structure-Unsorted%20Singly%20Linked%20List-D97706?style=for-the-badge)

</div>

[← Previous](../02_sortedList/README.md) · [Q1 overview](../README.md) · [Source code](main.c) · [Next →](../04_singlyLinkedSortedList/README.md)

**Tags:** `#C` `#Git` `#GitHub` `#DAA` `#DataStructures` `#Dictionary` `#SinglyLinkedList` `#UnsortedList` `#Pointer`

## Overview

This program implements a dictionary with an unsorted singly linked list. Each node stores one integer key and a link to the next node. New elements are added at the head, so insertion itself is constant time.

The program uses `Node *` as the result of `Search`, matching the question's requirement that operations such as `Delete(D, x)` receive a pointer to an item.

## Data Structure

```c
typedef struct Node {
    int key;
    struct Node *next;
} Node;
```

`Dict` stores the first node (`head`) and the current number of nodes (`length`). Enter distinct keys to preserve dictionary semantics.

## Worst-Case Complexity

| Operation | Time | Reason |
|---|---:|---|
| Search | `O(n)` | Nodes must be examined one by one. |
| Insert | `O(1)` | A new node is linked at the head. |
| Delete | `O(n)` | Even with a target pointer, its previous node must be found. |
| Maximum | `O(n)` | All keys must be inspected. |
| Minimum | `O(n)` | All keys must be inspected. |
| Predecessor | `O(n)` | The largest smaller key is found by scanning. |
| Successor | `O(n)` | The smallest larger key is found by scanning. |

## Build and Run

```bash
cc -std=c11 -Wall -Wextra -Werror main.c -o singly_unsorted
./singly_unsorted
```

## Notes

- List order is insertion order, not key order.
- `Destroy` releases every allocated node before the program exits.
- Predecessor and successor mean the adjacent keys in **sorted key order**, not adjacent nodes in the unsorted list.
