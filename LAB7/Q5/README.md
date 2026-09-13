# Q5 — Hitting a Moving Target

## 📌 Problem Statement

> **[Hitting a moving target]**  
> A computer game has a shooter and a moving target. The shooter can hit any of $n > 1$ hiding spots located along a straight line in which the target can hide. The shooter can never see the target; all he knows is that the target moves to an adjacent hiding spot between every two consecutive shots.
> 
> Design an algorithm that guarantees hitting the target or prove that no such algorithm exists.
>
> If any such algorithm exists, by choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

```text
Hiding spots along a 1D line (1 to n):
[ 1 ] <---> [ 2 ] <---> [ 3 ] <---> ... <---> [ n-1 ] <---> [ n ]

Target movement: x_{t+1} in { x_t - 1, x_t + 1 } (must change spot each turn)
Shooter: fires at one spot s_t at each step t, cannot see target.
```

---

## 💡 Mathematical Analysis & Algorithmic Strategy

### 1. The Parity Invariant

The target must move to an adjacent spot at every step:
$$x_{t+1} \in \{x_t - 1, x_t + 1\} \cap \{1, 2, \dots, n\}$$

Therefore, the parity of the target's position alternates at every single turn:
$$x_{t+1} \equiv x_t + 1 \pmod 2$$

This separates the target's initial state into two distinct possibilities:
1. **Even start:** Target starts at an even position ($x_1 \in \{2, 4, 6, \dots\}$).
2. **Odd start:** Target starts at an odd position ($x_1 \in \{1, 3, 5, \dots\}$).

---

### 2. Two-Phase Deterministic Shooting Strategy

For $n \ge 3$:

#### Phase 1: Catch Target if it Started on an Even Spot
- **Shooting sequence:** $2, 3, 4, \dots, n - 1$.
- Number of shots: $n - 2$.
- At step $t$ ($1 \le t \le n - 2$), shooter fires at $s_t = t + 1$.
- If target started on an even spot, at step $t=1$, target is at an even position $\ge 2$.
- If $x_1 = 2$, target is hit immediately.
- If $x_1 \ge 4$, target is strictly to the right of the shooter.
- Since target parity alternates each step, the parity of $x_t$ matches the parity of $s_t$ at every step.
- The difference $x_t - s_t$ is always a non-negative even integer.
- Target changes position by $\pm 1$ while shooter advances by $+1$, meaning $x_t - s_t$ changes by $0$ or $-2$.
- The target can **never** jump over the shooter without colliding!
- Therefore, if the target started at an even position, it is **guaranteed** to be hit during Phase 1.

#### Phase 2: Catch Target if it Started on an Odd Spot
- If the target survived Phase 1, it must have started at an odd position.
- $n - 2$ shots have taken place.
- Shooter now shoots backwards from right to left: $n - 1, n - 2, \dots, 2$.
- Number of shots: $n - 2$.
- By tracking the parity across the transition, the shooter's shot and the target's location are again perfectly synchronized in parity.
- The target is at or to the left of spot $n - 1$, and as the shooter sweeps left, the target cannot cross the shooter without colliding.
- Therefore, the target is **guaranteed** to be hit during Phase 2.

#### For $n = 2$:
- Sequence is simply $[2, 2]$ ($2$ shots).
  - If target starts at 2: hit on turn 1.
  - If target starts at 1: forced to move to 2, hit on turn 2.

#### Total Worst-Case Shots
$$\boxed{\text{Max Shots} = \begin{cases} 2 & \text{if } n = 2 \\ 2(n - 2) & \text{if } n \ge 3 \end{cases}}$$

---

## 🛠️ Input Representation & Code Design

In [`main.c`](file:///Users/rishav07/Documents/college/SEM3/DAA/LAB7/Q5/main.c):
1. **Belief State Tracker:**
   `bool possible[n + 1]` tracks the subset of spots the target could currently occupy.
2. **State Transition:**
   At each shot $s$:
   - Remove spot $s$: `possible[s] = false`.
   - Propagate remaining candidates to adjacent neighbors.
   - Proves mathematically that the set collapses to $\emptyset$ within $2(n - 2)$ shots.
3. **Interactive Simulation:**
   Runs a simulated game against a secretly placed moving target.

---

## ⏱️ Complexity Analysis

| Metric | Complexity | Explanation |
| :--- | :---: | :--- |
| **Total Shots** | $\mathcal{O}(n)$ | Exactly $2n - 4$ shots in the worst case. |
| **Time Complexity** | $\mathcal{O}(n^2)$ | Simulating belief state updates across $2n - 4$ rounds. |
| **Space Complexity** | $\mathcal{O}(n)$ | Array for shots sequence and belief state tracking. |

---

## ⚙️ Compilation & Execution

```bash
# Compile
gcc -Wall -Wextra -O2 main.c -o main

# Run
./main
```

---

## 🧪 Sample Output ($n = 5$)

```text
Enter number of spots: 5
Shooting sequence: 2 3 4 4 3 2 
Total shots needed: 6

Belief state reduction for n = 5:
Shot 1 at spot 2 -> remaining possible spots: 4
Shot 2 at spot 3 -> remaining possible spots: 4
Shot 3 at spot 4 -> remaining possible spots: 2
Shot 4 at spot 4 -> remaining possible spots: 2
Shot 5 at spot 3 -> remaining possible spots: 1
Shot 6 at spot 2 -> remaining possible spots: 0
Target guaranteed hit by shot 6!

Simulating with target starting at spot 5:
Turn 1: Shooter hits 2, Target is at 5 -> Target moved to 4
Turn 2: Shooter hits 3, Target is at 4 -> Target moved to 5
Turn 3: Shooter hits 4, Target is at 5 -> Target moved to 4
Turn 4: Shooter hits 4, Target is at 4 -> HIT!
```
