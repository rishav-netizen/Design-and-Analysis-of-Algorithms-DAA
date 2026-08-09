# 📦 Q1.1 — Unsorted Array Dictionary

<div align="center">

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Git](https://img.shields.io/badge/Git-F05032?style=for-the-badge&logo=git&logoColor=white)
![GitHub](https://img.shields.io/badge/GitHub-181717?style=for-the-badge&logo=github&logoColor=white)
![Structure](https://img.shields.io/badge/Structure-Unsorted%20Array-D97706?style=for-the-badge)

</div>

[← Q1 overview](../README.md) · [Source code](main.c) · [Next implementation →](../02_sortedList/README.md)


This program implements a simple dictionary using an unsorted array. It supports insertion, linear search, deletion, maximum/minimum lookup, and predecessor/successor queries.

**Tags:** `#C` `#Git` `#GitHub` `#DAA` `#DataStructures` `#Array` `#Dictionary` `#UnsortedList` `#LinearSearch` `#Deletion` `#MaxMin` `#Predecessor` `#Successor`

## Overview

The dictionary is stored in a fixed-size array. Since the array is unsorted, operations that need to inspect values usually require a full scan of the list.

This makes the code simple and easy to understand, but not optimized for fast searching.

## Data Structure Used

The program defines a `Dict` structure:

```c
typedef struct Dict
{
    int *A;
    int size;
    int length;
} Dict;
```

### Meaning of each field

- `A`: dynamically allocated integer array that stores the elements
- `size`: maximum capacity of the dictionary
- `length`: current number of elements stored

## Supported Operations

### `Insert(Dict *D, int x)`
Adds `x` at the end of the array if there is space.

### `Search(Dict *D, int key)`
Performs a linear search and returns the index of `key` if found, otherwise `-1`.

### `Delete(Dict *D, int key)`
Finds `key`, then shifts later elements left by one position to remove it.

### `Max(Dict *D)`
Finds and returns the largest element in the dictionary.

### `Min(Dict *D)`
Finds and returns the smallest element in the dictionary.

### `Predecessor(Dict *D, int key)`
Finds the largest element smaller than `key`.

### `Successor(Dict *D, int key)`
Finds the smallest element greater than `key`.

## Time Complexity

Let `n = length` be the number of stored elements.

| Function | Time Complexity | Notes |
|---|---:|---|
| `Insert` | `O(1)` | Appends to the end if space is available |
| `Search` | `O(n)` | Linear scan |
| `Delete` | `O(n)` | Search plus shifting elements |
| `Max` | `O(n)` | One pass through the array |
| `Min` | `O(n)` | One pass through the array |
| `Predecessor` | `O(n)` | One pass through the array |
| `Successor` | `O(n)` | One pass through the array |

## How the Program Works

1. The user enters the dictionary size.
2. Memory is allocated dynamically for the array.
3. The user enters the initial elements.
4. The program demonstrates:
   - insertion
   - search
   - maximum and minimum lookup
   - predecessor and successor lookup
   - deletion
5. The allocated memory is freed before exit.

## Input and Output Behavior

- The program validates the number of input elements so it does not exceed the allocated size.
- If the dictionary is full, insertion is rejected.
- If a searched or deleted key does not exist, the program prints an error message.
- If the dictionary is empty, `Max` and `Min` return `-1`.

## Build and Run

Compile with:

```bash
cc main.c -o unsorted_list
```

Run with:

```bash
./unsorted_list
```

## Example Use Case

This implementation is useful for learning:

- dynamic arrays
- linear search
- element deletion by shifting
- predecessor and successor logic on unsorted data

## Notes

- The list is unsorted, so search-related operations are not optimized.
- If faster search is needed, a sorted array, linked list variant, or hash table would be a better choice.
