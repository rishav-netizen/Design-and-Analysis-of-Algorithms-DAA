# 🔗 Q1.4 — Sorted Singly Linked List Dictionary

<div align="center">

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Git](https://img.shields.io/badge/Git-F05032?style=for-the-badge&logo=git&logoColor=white)
![GitHub](https://img.shields.io/badge/GitHub-181717?style=for-the-badge&logo=github&logoColor=white)
![Structure](https://img.shields.io/badge/Structure-Sorted%20Singly%20Linked%20List-2563EB?style=for-the-badge)

</div>

[← Previous](../03_singlyLinkedUnsortedList/README.md) · [Q1 overview](../README.md) · [Source code](main.c) · [Next →](../05_doublyLinkedUnsortedList/README.md)

**Tags:** `#C` `#Git` `#GitHub` `#DAA` `#DataStructures` `#Dictionary` `#SinglyLinkedList` `#SortedList` `#Pointer`

## Overview

This dictionary stores unique integer keys in ascending order in a singly linked list. It cannot use binary search because linked-list nodes do not support random access, but sorted order makes `Min` and `Successor` fast.

## Data Structure

```c
typedef struct Node {
    int key;
    struct Node *next;
} Node;
```

The dictionary owns a `head` pointer and a node count. `Insert` finds the correct link and preserves ascending order.

## Worst-Case Complexity

| Operation | Time | Reason |
|---|---:|---|
| Search | `O(n)` | Nodes are traversed sequentially. |
| Insert | `O(n)` | The sorted insertion point may be at the end. |
| Delete | `O(n)` | The previous node is needed to unlink the target. |
| Maximum | `O(n)` | The last node must be reached from the head. |
| Minimum | `O(1)` | The head holds the smallest key. |
| Predecessor | `O(n)` | A singly linked list has no backward link. |
| Successor | `O(1)` | It is `target->next`. |

## Build and Run

```bash
cc -std=c11 -Wall -Wextra -Werror main.c -o singly_sorted
./singly_sorted
```

## Notes

- Duplicate keys are rejected.
- `Search` exits early when it passes the requested key.
- Predecessor and successor receive the node pointer described in the assignment; the interactive driver first finds it from the entered key.
