# Sorted Doubly Linked List Dictionary

[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Structure](https://img.shields.io/badge/Structure-Doubly%20Linked%20List-brightgreen.svg)](https://en.wikipedia.org/wiki/Doubly_linked_list)
[![Order](https://img.shields.io/badge/Order-Sorted-orange.svg)](https://en.wikipedia.org/wiki/Dictionary_(abstract_data_type))

`#C` `#DAA` `#DataStructures` `#Dictionary` `#DoublyLinkedList` `#SortedList` `#Pointer`

## Overview

This dictionary keeps unique integer keys in ascending order in a doubly linked list. It stores both `head` and `tail`, making the extreme keys and immediate neighbours directly available.

## Data Structure

```c
typedef struct Node {
    int key;
    struct Node *prev;
    struct Node *next;
} Node;
```

The `Dict` structure keeps `head`, `tail`, and `length`. Insertion traverses to the sorted position; all links are updated on insertion and deletion.

## Worst-Case Complexity

| Operation | Time | Reason |
|---|---:|---|
| Search | `O(n)` | Linked-list nodes have no random access. |
| Insert | `O(n)` | The correct sorted position may be at the tail. |
| Delete | `O(1)` | A provided target node is unlinked through `prev` and `next`. |
| Maximum | `O(1)` | `tail` holds the largest key. |
| Minimum | `O(1)` | `head` holds the smallest key. |
| Predecessor | `O(1)` | It is `target->prev`. |
| Successor | `O(1)` | It is `target->next`. |

## Build and Run

```bash
cc -std=c11 -Wall -Wextra -Werror main.c -o doubly_sorted
./doubly_sorted
```

## Notes

- Duplicate keys are rejected.
- Search is still linear even though the list is sorted; binary search needs indexed access.
- The constant-time delete, predecessor, and successor bounds assume the node pointer `x` is already provided, exactly as in the question.
