# Q4 — Security Switches (Baguenaudier / Gray Code)

## 📌 Problem Statement

> **[Security switches]**  
> There is a row of $n$ security switches protecting a military installation entrance. The switches can be manipulated as follows:
> 
> 1. The rightmost switch may be turned on or off at will.
> 2. Any other switch may be turned on or off only if the switch to its immediate right is on and all the other switches to its right, if any, are off.
> 3. Only one switch may be toggled at a time.
> 
> Devise an algorithm to turn off all the switches, which are initially all on, in the minimum number of moves. (Toggling one switch is considered one move.)
>
> By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

```text
Military Security Switches (n switches, initially ALL ON):
[ S_n ]  [ S_{n-1} ]  ...  [ S_3 ]  [ S_2 ]  [ S_1 ]
 (ON)      (ON)              (ON)    (ON)    (ON)
                                              ^
                                     (Rightmost: toggled at will)

Rule for switch S_k (k >= 2):
  Can toggle S_k  <===>  S_{k-1} is ON  AND  S_{k-2}...S_1 are all OFF!
```

---

## 💡 Mathematical Analysis & Derivation of Compact Formula

### 1. Equivalence to the Classical Baguenaudier (Chinese Rings) Puzzle

Number the switches $1, 2, \dots, n$ from right to left, so:
- Switch $1$ is the **rightmost** switch.
- Switch $n$ is the **leftmost** switch.

The manipulation rules state:
1. Switch $1$ can be flipped at any time: $\text{flip}(1)$ is always legal.
2. Switch $k$ ($k \ge 2$) can be flipped **if and only if**:
   $$\text{Switch } k-1 \text{ is ON (1)} \quad \text{and} \quad \text{Switches } 1, 2, \dots, k-2 \text{ are all OFF (0)}$$

This is the exact transition rule of the ancient **Baguenaudier** (also known as the Chinese Rings puzzle) and corresponds to traversing adjacent codewords in the **Binary Reflected Gray Code (BRGC)**.

---

### 2. Recurrence Relation Derivation

Let $M(n)$ be the minimum number of moves required to turn OFF all switches $1 \dots n$ given that they are all initially ON.

To turn OFF switch $n$:
1. Switch $n$ can only be toggled when switch $n-1$ is ON and switches $1 \dots n-2$ are OFF.
   - Since all switches start ON, switches $1 \dots n-2$ must first be turned OFF.
   - This takes $M(n - 2)$ moves.
2. Toggle switch $n$ from ON to OFF.
   - This takes $1$ move.
3. Now switches $1 \dots n-2$ are OFF and switch $n-1$ is ON. To turn off switch $n-1$, we first need to re-enable switches $1 \dots n-2$ into an ON state to serve as stepping stones:
   - Turning switches $1 \dots n-2$ back ON takes $M(n - 2)$ moves (by reversibility).
4. Finally, turn OFF all switches $1 \dots n-1$:
   - This takes $M(n - 1)$ moves.

Summing all steps gives the second-order linear recurrence:
$$\boxed{M(n) = M(n - 1) + 2 \cdot M(n - 2) + 1} \quad \text{for } n \ge 3$$

with base cases:
- $n = 1$: Toggle switch $1$ $\implies M(1) = 1$.
- $n = 2$: Toggle switch $2$, then switch $1$ $\implies M(2) = 2$.

---

### 3. Closed-Form Derivation

Computing the first few values:
- $M(1) = 1$
- $M(2) = 2$
- $M(3) = 2 + 2(1) + 1 = 5$
- $M(4) = 5 + 2(2) + 1 = 10$
- $M(5) = 10 + 2(5) + 1 = 21$
- $M(6) = 21 + 2(10) + 1 = 42$
- $M(7) = 42 + 2(21) + 1 = 85$
- $M(8) = 85 + 2(42) + 1 = 170$

The sequence satisfies the compact closed-form formula:
$$\boxed{M(n) = \left\lfloor \frac{2^{n+1}}{3} \right\rfloor = \begin{cases} \frac{2^{n+1} - 1}{3} & \text{if } n \text{ is odd} \\[8pt] \frac{2^{n+1} - 2}{3} & \text{if } n \text{ is even} \end{cases}}$$

---

## 🛠️ Input Representation & Algorithm Design

In [`main.c`](file:///Users/rishav07/Documents/college/SEM3/DAA/LAB07/Q4/main.c):
1. **Switch Representation:**
   `int switches[MAX_SWITCHES + 1]` where index $1$ is the rightmost switch and $n$ is the leftmost switch ($1 = \text{ON}, 0 = \text{OFF}$).
2. **Mutual Recursive Procedures:**
   - `turnOffSwitches(k)`: Turns OFF switches $1 \dots k$ from all ON.
   - `turnOnSwitches(k)`: Turns ON switches $1 \dots k$ from all OFF.
3. **Strict Invariant Validation:**
   `toggleSwitch(k)` enforces the military installation rules at runtime, aborting if any illegal move is attempted.

---

## ⏱️ Complexity Analysis

| Metric | Complexity | Explanation |
| :--- | :---: | :--- |
| **Move Count / Time Complexity** | $\Theta(2^n)$ | Generates $\lfloor 2^{n+1}/3 \rfloor$ switch transitions. |
| **Space Complexity** | $\mathcal{O}(n)$ | Recursion call stack depth bounded by $n$. |

---

## ⚙️ Compilation & Execution

```bash
# Compile
gcc -Wall -Wextra -O2 main.c -o main

# Run
./main
```

---

## 🧪 Sample Output & Execution Trace ($n = 4$)

```text
====================================================
       Security Switches (DAA Lab 07, Q4)           
====================================================
Enter number of security switches n (default 4): 4

[Initial Configuration: All 4 Switches ON]
Switches layout: [S_4 S_3 ... S_1] (S_1 is rightmost)
Initial state:   [1 1 1 1]

[Deactivation Sequence Execution]
  Move   1: Toggle Switch  2 (ON  -> OFF) => State: [1 1 0 1]
  Move   2: Toggle Switch  1 (ON  -> OFF) => State: [1 1 0 0]
  Move   3: Toggle Switch  4 (ON  -> OFF) => State: [0 1 0 0]
  Move   4: Toggle Switch  1 (OFF -> ON ) => State: [0 1 0 1]
  Move   5: Toggle Switch  2 (OFF -> ON ) => State: [0 1 1 1]
  Move   6: Toggle Switch  1 (ON  -> OFF) => State: [0 1 1 0]
  Move   7: Toggle Switch  3 (ON  -> OFF) => State: [0 0 1 0]
  Move   8: Toggle Switch  1 (OFF -> ON ) => State: [0 0 1 1]
  Move   9: Toggle Switch  2 (ON  -> OFF) => State: [0 0 0 1]
  Move  10: Toggle Switch  1 (ON  -> OFF) => State: [0 0 0 0]

[Final Configuration]
Final state:     [0 0 0 0]

[Validation]
  Total moves executed: 10
  Theoretical minimum:  10 moves (floor(2^(4+1)/3))
  Result: SUCCESS! All switches successfully turned off in minimum moves.

--- Theoretical Move Counts: M(n) = floor(2^(n+1) / 3) ---
Switches | Minimum Moves    | Formula Closed-Form 
---------+------------------+---------------------
 1       | 1                | (2^2 - 1) / 3
 2       | 2                | (2^3 - 2) / 3
 3       | 5                | (2^4 - 1) / 3
 4       | 10               | (2^5 - 2) / 3
 5       | 21               | (2^6 - 1) / 3
 6       | 42               | (2^7 - 2) / 3
 7       | 85               | (2^8 - 1) / 3
 8       | 170              | (2^9 - 2) / 3
 9       | 341              | (2^10 - 1) / 3
 10      | 682              | (2^11 - 2) / 3
```
