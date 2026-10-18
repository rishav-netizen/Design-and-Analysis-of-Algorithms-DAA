# Question 3: Maximum Weight Component with Size Constraints

<div align="center">

![C](https://img.shields.io/badge/Language-C11-00599C?style=for-the-badge&logo=c)
![Paradigm](https://img.shields.io/badge/Paradigm-Augmented%20DSU%20%2B%20Priority%20Queue-F59E0B?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Complete-059669?style=for-the-badge)

</div>

---

## 📌 Problem Statement

> Given a graph where each vertex $v$ has weight $w_v$, edges are added sequentially with weights. At any point, compute the maximum total vertex weight of any connected component whose size does not exceed a threshold $K$.
>
> By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## 🧠 Theoretical Formulation & Mathematical Foundations

### 1. Connected Component Weight & Size Aggregation

Let $G = (V, E)$ be an undirected graph with vertex weight function $w: V \to \mathbb{Z}$.
Let $\mathcal{C} = \{ C_1, C_2, \dots, C_p \}$ denote the partition of vertices into connected components at any instantaneous time step.

For each component $C \in \mathcal{C}$, we define:
1. **Component Cardinality (Size):**
   $$|C| = \sum_{v \in C} 1$$
2. **Total Vertex Weight:**
   $$W(C) = \sum_{v \in C} w_v$$

### 2. Constrained Optimization Objective

Given a strict size capacity threshold $K \in \mathbb{Z}^+$, the set of **feasible components** $\mathcal{F} \subseteq \mathcal{C}$ is:
$$\mathcal{F} = \{ C \in \mathcal{C} \mid |C| \le K \}$$

The instantaneous optimization objective is to determine:
$$W^* = \begin{cases} \displaystyle\max_{C \in \mathcal{F}} W(C) & \text{if } \mathcal{F} \neq \emptyset \\ -\infty \text{ (or NULL)} & \text{if } \mathcal{F} = \emptyset \end{cases}$$

### 3. Non-Monotonicity Challenge & Solution Architecture

When an edge $(u, v)$ is added between two disjoint components $C_u$ and $C_v$:
- The resulting merged component $C_{new} = C_u \cup C_v$ has:
  $$|C_{new}| = |C_u| + |C_v|, \quad W(C_{new}) = W(C_u) + W(C_v)$$
- If $|C_{new}| \le K$, $C_{new}$ enters the feasible set $\mathcal{F}$, potentially establishing a new global maximum.
- **The Critical Challenge:** If $|C_{new}| > K$, both $C_u$ and $C_v$ vanish from $\mathcal{F}$, and $C_{new}$ is **ineligible**. Thus, the maximum eligible weight $W^*$ can **decrease**, precluding simple monotonic max tracking.

To resolve this with optimal efficiency:
1. **Augmented DSU:** Each component root maintains `compSize`, `compWeight`, and a monotonic `version` counter.
2. **Lazy Max-Heap (Priority Queue):** Whenever a component $r$ is created or updated with $|C_r| \le K$, the tuple $(r, \text{version}[r], W(r))$ is pushed into a binary max-heap.
3. **Lazy Invalidation:** When querying $W^*$, the top heap element is inspected. If its root is no longer a set representative, its version is stale, or its size exceeds $K$, it is popped and discarded. The first valid entry at the heap apex represents the exact constrained maximum.

---

## 🏗️ Algorithm Architecture & Flowchart

```mermaid
flowchart TD
    Start([Edge Arrival: u, v with weight w_e]) --> FindRoots[Find Set Representatives: ru, rv]
    FindRoots --> CheckSame{ru == rv ?}
    
    CheckSame -- Yes --> Skip[Redundant Edge: Query Heap for Current Max]
    
    CheckSame -- No --> Merge[Union ru and rv by Rank<br>newRoot gets: size = size_u + size_v<br>weight = wt_u + wt_v<br>Increment version[newRoot]]
    
    Merge --> CheckThreshold{size[newRoot] <= K ?}
    CheckThreshold -- Yes --> PushHeap[Push to Max-Heap:<br>newRoot, version, weight]
    CheckThreshold -- No --> Exceeds[Component Exceeds K: Not Eligible]
    
    PushHeap --> QueryMax[Lazy Max-Heap Extraction]
    Exceeds --> QueryMax
    
    subgraph Lazy Heap Query
        QueryMax --> PeekTop[Inspect Top of Heap]
        PeekTop --> Valid{Is Root Active & Version Matches & Size <= K?}
        Valid -- No --> PopStale[Pop Stale Entry] --> PeekTop
        Valid -- Yes --> ReturnMax[Return Top Weight as W*]
    end
```

---

## 📊 Complexity Analysis

### Time Complexity
- **DSU Operations:** Each edge insertion triggers 2 `findSet` queries and at most 1 union, taking $\mathcal{O}(\alpha(V))$ amortised time.
- **Heap Maintenance:**
  - Each merge creates at most 1 new heap node, requiring $\mathcal{O}(\log |H|)$ time.
  - Across $M$ edge additions, at most $V + M$ items are ever pushed to the heap.
  - Each item is popped lazily at most once throughout the entire program execution.
  - Total amortised time per edge query: $\mathcal{O}(\alpha(V) + \log(V + M))$.
- **Overall Time Complexity:**
  $$\mathcal{O}(V + M \log(V + M))$$

### Space Complexity
- DSU arrays (`parent`, `rank`, `compSize`, `compWeight`, `version`): $5 \times V \times \text{sizeof}(\text{type}) = \Theta(V)$.
- Max-Heap buffer: $\mathcal{O}(V + M)$ nodes.
- **Total Space Complexity:** $\Theta(V + M)$ auxiliary memory.

---

## 🧪 Verification & Step-by-Step Sample Trace

Consider $V = 5$ vertices with weights:
$$w(1)=10, \; w(2)=20, \; w(3)=15, \; w(4)=30, \; w(5)=25, \quad K = 3$$

```text
Initial State (0 edges):
  Eligible singletons: {1:10}, {2:20}, {3:15}, {4:30}, {5:25}
  Max Weight (Size <= 3): 30 (Root: 4, Size: 1)

[Step 1] Edge arrives: (1, 2)
  -> Merge {1} and {2} => {1, 2}: Size = 2 <= 3, Total Weight = 30.
  => MAX WEIGHT: 30 (Roots 4 and 1)

[Step 2] Edge arrives: (3, 4)
  -> Merge {3} and {4} => {3, 4}: Size = 2 <= 3, Total Weight = 45.
  => MAX WEIGHT: 45 (Root 3, Size: 2)

[Step 3] Edge arrives: (1, 3)
  -> Merge {1, 2} and {3, 4} => {1, 2, 3, 4}: Size = 4 > 3 (EXCEEDS K!).
  -> Heap lazily discards root 1.
  -> Remaining eligible component is {5} of size 1 with weight 25.
  => MAX WEIGHT: 25 (Root 5, Size: 1)

[Step 4] Edge arrives: (4, 5)
  -> Merge into single component of size 5 > 3.
  => MAX WEIGHT: NONE (All components exceed size threshold K = 3).
```

---

## 💻 Compilation & Execution

```bash
# Compile using C11 standard with all warnings enabled
gcc -std=c11 -Wall -Wextra main.c -o program

# Run interactive simulation
./program
```
