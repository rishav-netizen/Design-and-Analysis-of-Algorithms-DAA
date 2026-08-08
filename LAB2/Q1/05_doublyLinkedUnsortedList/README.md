# Unsorted Doubly Linked List Dictionary

[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Structure](https://img.shields.io/badge/Structure-Doubly%20Linked%20List-brightgreen.svg)](https://en.wikipedia.org/wiki/Doubly_linked_list)
[![Order](https://img.shields.io/badge/Order-Unsorted-orange.svg)](https://en.wikipedia.org/wiki/Dictionary_(abstract_data_type))

`#C` `#DAA` `#DataStructures` `#Dictionary` `#DoublyLinkedList` `#UnsortedList` `#Pointer`

## Overview

This implementation stores integer keys in an unsorted doubly linked list. Every node has both `prev` and `next` links, so a known node can be removed without locating its predecessor first.

## Data Structure

```c
typedef struct Node {
    int key;
    struct Node *prev;
    struct Node *next;
} Node;
```

`Dict` maintains both `head` and `tail`. New elements are linked at the head. Enter distinct keys to preserve dictionary semantics.

## Worst-Case Complexity

| Operation | Time | Reason |
|---|---:|---|
| Search | `O(n)` | The list is unsorted. |
| Insert | `O(1)` | Insert at the head and update one neighbour. |
| Delete | `O(1)` | A provided target node has direct previous and next links. |
| Maximum | `O(n)` | Every key must be examined. |
| Minimum | `O(n)` | Every key must be examined. |
| Predecessor | `O(n)` | Sorted key order must be determined by scanning. |
| Successor | `O(n)` | Sorted key order must be determined by scanning. |

## Build and Run

```bash
cc -std=c11 -Wall -Wextra -Werror main.c -o doubly_unsorted
./doubly_unsorted
```

## Notes

- `Delete(D, target)` is constant time only after a pointer to `target` is available, as specified in the assignment.
- The interactive driver uses `Search` first because a user supplies a key rather than a C pointer.
- `Destroy` frees all dynamically allocated nodes.
