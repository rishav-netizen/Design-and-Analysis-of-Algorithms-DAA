# Sorted Array Dictionary

[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Data Structure](https://img.shields.io/badge/Data%20Structure-Sorted%20Array-brightgreen.svg)](https://en.wikipedia.org/wiki/Array_data_structure)
[![Topic](https://img.shields.io/badge/Topic-Dictionary%20Operations-orange.svg)](https://en.wikipedia.org/wiki/Associative_array)

`#C` `#DataStructures` `#Dictionary` `#SortedArray` `#BinarySearch` `#Algorithms` `#DAA` `#Predecessor` `#Successor`

## Overview

This program implements the dictionary abstract data type using a fixed-capacity **sorted array**. A dictionary stores unique keys and supports search, insertion, deletion, maximum, minimum, predecessor, and successor operations.

Keys are always maintained in ascending order. The input may be entered in any order; the program inserts each valid key into its correct sorted position.

## Data Structure

```c
typedef struct
{
    int *A;
    int size;
    int length;
} Dict;
```

| Field | Meaning |
|---|---|
| `A` | Dynamically allocated array that stores the keys in ascending order |
| `size` | Maximum capacity of the dictionary |
| `length` | Number of keys currently stored |

## Dictionary Rules

- Keys are stored in ascending order.
- Duplicate keys are rejected.
- The dictionary has a fixed maximum capacity selected by the user.
- Empty-dictionary cases are handled safely for `Max`, `Min`, predecessor, and successor.

## Supported Operations

| Function | Description |
|---|---|
| `Search(D, key)` | Finds a key using binary search and returns its index, or `-1`. |
| `Insert(D, key)` | Finds the sorted position, shifts later keys right, and inserts a unique key. |
| `Delete(D, key)` | Finds the key, shifts later keys left, and removes it. |
| `Max(D, &value)` | Retrieves the final array element. |
| `Min(D, &value)` | Retrieves the first array element. |
| `Predecessor(D, index, &value)` | Retrieves the key immediately before an item's array position. |
| `Successor(D, index, &value)` | Retrieves the key immediately after an item's array position. |

`Max`, `Min`, `Predecessor`, and `Successor` return `true` when a result exists and store it through `value`. This avoids using a special integer such as `-1`, which could itself be a valid key.

## Worst-Case Time Complexity

Let `n` be the current number of keys.

| Primary operation | Worst-case time | Why |
|---|---:|---|
| Search | `O(log n)` | Binary search halves the remaining search range each step. |
| Insert | `O(n)` | Locating the position is `O(log n)`, but shifting elements can take `O(n)`. |
| Delete | `O(n)` | Binary search is `O(log n)`, but closing the gap can require `O(n)` shifts. |
| Maximum | `O(1)` | The largest key is at index `length - 1`. |
| Minimum | `O(1)` | The smallest key is at index `0`. |
| Predecessor | `O(1)` | Given the item's index/pointer, it is at `index - 1`. |
| Successor | `O(1)` | Given the item's index/pointer, it is at `index + 1`. |

The sorted order makes search and boundary queries fast, but makes insertion and deletion expensive because array elements may need to move.

## Program Flow

1. Enter the maximum dictionary size.
2. Enter the initial number of keys and their values in any order.
3. The program keeps the array sorted while reading the keys.
4. It demonstrates insertion, search, maximum/minimum, predecessor/successor, and deletion.
5. Dynamically allocated memory is released before the program exits.

## Build and Run

From this directory:

```bash
cc -std=c11 -Wall -Wextra -Werror main.c -o sorted_list
./sorted_list
```

## Example

If the initial input is `40, 10, 30, 20`, the dictionary is stored as:

```text
{ 10, 20, 30, 40 }
```

For key `30`, the predecessor is `20` and the successor is `40`.

## Notes

- The implementation uses `LowerBound` for binary search and sorted insertion.
- Since it is a dictionary, each key must be unique.
- This is a learning implementation using integers as keys. A more general dictionary could store key-value pairs.
