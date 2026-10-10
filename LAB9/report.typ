#set page(
  paper: "a4",
  margin: (x: 1.2cm, top: 1.3cm, bottom: 1.3cm),
  header: context {
    text(size: 7.5pt, fill: rgb("#4B5563"))[
      *DAA LABORATORY (CS3101) — LAB 09 REPORT (GREEDY PARADIGM)* #h(1fr) *IIIT BHUBANESWAR | AUTUMN 2026*
    ]
    v(-4pt)
    line(length: 100%, stroke: 0.5pt + rgb("#D1D5DB"))
  },
  footer: context {
    line(length: 100%, stroke: 0.5pt + rgb("#D1D5DB"))
    v(-4pt)
    text(size: 7.5pt, fill: rgb("#4B5563"))[
      Instructor: Dr. Ajaya Kumar Dash · Student: Rishav Kumar (Roll: B125099, CSE B1) #h(1fr) Page #counter(page).display() of #counter(page).final().first()
    ]
  }
)

#set text(font: "Helvetica", size: 8.5pt)
#set par(justify: true, leading: 0.52em)

// Header Block
#align(center)[
  #text(size: 11pt, weight: "bold", fill: rgb("#1E3A8A"))[INTERNATIONAL INSTITUTE OF INFORMATION TECHNOLOGY, BHUBANESWAR]\
  #text(size: 9.5pt, weight: "bold", fill: rgb("#374151"))[Department of Computer Science & Engineering | DAA Laboratory (CS3101)]\
  #v(2pt)
  #text(size: 12pt, weight: "bold", fill: rgb("#B45309"))[LAB 09 REPORT: GREEDY DESIGN PARADIGM]\
  #v(2pt)
  #rect(fill: rgb("#F3F4F6"), stroke: 0.5pt + rgb("#E5E7EB"), radius: 3pt, inset: (x: 8pt, y: 4pt))[
    #text(size: 8pt)[
      *Student:* Rishav Kumar #h(12pt) *Roll:* B125099 #h(12pt) *Branch:* B.Tech CSE (B1) #h(12pt) *Instructor:* Dr. A. K. Dash #h(12pt) *Date:* Oct 2026
    ]
  ]
]

#v(4pt)

// Index Table
#text(size: 9pt, weight: "bold", fill: rgb("#1E3A8A"))[Index of Questions & Algorithmic Summary]
#v(2pt)
#table(
  columns: (30pt, 135pt, 140pt, 65pt, 50pt, 45pt),
  stroke: 0.3pt + rgb("#D1D5DB"),
  fill: (col, row) => if row == 0 { rgb("#E5E7EB") } else if calc.even(row) { rgb("#F9FAFB") } else { none },
  align: (center, left, left, center, center, center),
  inset: (x: 4pt, y: 3pt),
  table.header(
    [*Q. No.*], [*Problem Name*], [*Algorithmic Paradigm*], [*Time*], [*Space*], [*Status*]
  ),
  [Q1], [Fractional Knapsack (Decay)], [Deteriorating Resource Greedy], [$cal(O)(n log n)$], [$cal(O)(n)$], [Verified],
  [Q2], [Canonical Huffman Coding], [Min-Heap Prefix Tree & Canonical], [$cal(O)(n log n)$], [$cal(O)(n)$], [Verified],
  [Q3], [Minimum Refueling Stops], [Retroactive Max-Heap (Reverse)], [$cal(O)(n log n)$], [$cal(O)(n)$], [Verified],
  [Q4], [Minimum Cost Sticks], [Min-Heap Huffman Merge Tree], [$cal(O)(n log n)$], [$cal(O)(n)$], [Verified],
  [Q5], [Candy Distribution], [Bi-directional Slope Greedy], [$Theta(n)$], [$Theta(n)$], [Verified],
  [Q6], [Reorganise String K-Apart], [Max-Heap + FIFO Cooldown Queue], [$cal(O)(N log |Sigma|)$], [$cal(O)(N + |Sigma|)$], [Verified],
  [Q7], [Minimise Array Deviation], [Two-Way Greedy Monotonic Descent], [$cal(O)(n log(M) log n)$], [$cal(O)(n)$], [Verified],
  [Q8], [Meeting Rooms Allocation], [Interval Coloring / Min-Heap], [$cal(O)(n log n)$], [$cal(O)(n)$], [Verified],
  [Q9], [Hu-Tucker Tree Simulation], [3-Phase Compatible Greedy Merge], [$cal(O)(n^2)$], [$cal(O)(n)$], [Verified],
  [Q10], [Greedy Superstring Open], [SCS Heuristic & 2026 AI Disproof], [$cal(O)(n^3 L)$], [$cal(O)(n L)$], [Explored],
)

#v(6pt)

// Q1
#text(size: 9.5pt, weight: "bold", fill: rgb("#1E3A8A"))[Q1: Fractional Knapsack with Deterioration Rate] #h(1fr) #text(size: 8pt, style: "italic")[Greedy Exchange Priority · $cal(O)(n log n)$]
#v(1pt)
*Problem Statement:* $n$ items with base values $v_i$, weights $w_i$, decay rates $lambda_i > 0$. At time $t$, value density decays to $(v_i/w_i) - lambda_i t$. Knapsack capacity is $W$. Determine optimal scheduling order and fractional choices to maximize total value.

*Exchange Proof & Formulation:* Consuming weight $w'_i$ starting at $t_s$ yields $V_i = w'_i [v_i/w_i - lambda_i (t_s + w'_i/2)]$. For two consecutive items $A$ and $B$, $V(A arrow.r B) - V(B arrow.r A) = w_A w_B (lambda_A - lambda_B)$. Since $w_A, w_B > 0$, items with higher decay rates $lambda_i$ *must strictly precede* items with lower decay rates to minimize waiting losses. Items are truncated at $t_("max") = v_i / (w_i lambda_i)$ when marginal density reaches zero.
- *Complexity:* Time: $cal(O)(n log n)$ (dominated by `qsort`), Auxiliary Space: $cal(O)(n)$.
- *Verification Trace:* Items $[(60, 10, 0.5), (100, 20, 0.8), (120, 30, 0.2)]$, $W = 50$: Scheduled Item 2 ($31.25%$, val $15.625$), Item 1 ($57.50%$, val $8.266$), Item 3 ($26.67%$, val $6.400$). Max Total Value = $30.2906$.

```c
int compareItems(const void *a, const void *b) {
    const Item *ia = (const Item *)a, *ib = (const Item *)b;
    if (ib->lambda > ia->lambda) return 1;
    if (ib->lambda < ia->lambda) return -1;
    return (ib->density > ia->density) ? 1 : -1;
}
```

#pagebreak()

// Q2
#text(size: 9.5pt, weight: "bold", fill: rgb("#1E3A8A"))[Q2: Canonical Huffman Coding] #h(1fr) #text(size: 8pt, style: "italic")[Prefix Tree & Canonical Codebook · $cal(O)(n log n)$]
#v(1pt)
*Problem Statement:* Given symbol frequencies, construct a prefix-free binary code of minimum expected length, and output the canonical Huffman codebook (where codes are ordered lexicographically by length).

*Theoretical Invariant & Canonical Generation:* Huffman builds an optimal full binary tree bottom-up by repeatedly merging the two smallest frequency nodes (CLRS Lemma 16.2 & 16.3). Canonical codes standardize transmission by sorting symbols by code length $L_i$ ascending and symbol ASCII:
$C_0 = 0, quad C_i = (C_{i-1} + 1) lt.double (L_i - L_{i-1})$. Decompressors only require the length array.
- *Complexity:* Time: $cal(O)(n log n)$ (min-heap + sorting), Auxiliary Space: $cal(O)(n)$.
- *Verification Trace (CLRS 16 Benchmark):* $A:45, B:13, C:12, D:16, E:9, F:5$ ($N = 100$):
  Canonical codes: $A (L=1): bold("0"), B (L=3): bold("100"), C (L=3): bold("101"), D (L=3): bold("110"), E (L=4): bold("1110"), F (L=4): bold("1111")$.
  Total bits: $224$, Entropy: $2.2199$, Expected Length: $2.2400$, Coding Efficiency: $99.10%$.

```c
void buildCanonicalCodes(SymbolCode *codes, int n) {
    qsort(codes, n, sizeof(SymbolCode), compareCanonical);
    unsigned int cur = 0; int curLen = codes[0].length;
    for (int i = 0; i < n; i++) {
        if (codes[i].length > curLen) { cur <<= (codes[i].length - curLen); curLen = codes[i].length; }
        codes[i].canonicalCode = cur++;
    }
}
```

#v(8pt)

// Q3
#text(size: 9.5pt, weight: "bold", fill: rgb("#1E3A8A"))[Q3: Minimum Initial Fuel (Reverse Greedy)] #h(1fr) #text(size: 8pt, style: "italic")[Retroactive Max-Heap Simulation · $cal(O)(n log n)$]
#v(1pt)
*Problem Statement:* A vehicle needs to reach target $D$ starting with fuel $F$. Along the way are stations $(d_i, f_i)$ (distance from origin and fuel stock). Find the minimum number of refueling stops required.

*Reverse Greedy Strategy:* Drive forward as far as possible. Whenever current fuel is insufficient to reach the next station $d_i$ or destination $D$, retroactively refuel at the passed station offering the *maximum fuel capacity* using a Max-Heap. This guarantees maximal reachable horizon at every step. If heap is empty during a deficit, destination is unreachable ($-1$).
- *Complexity:* Time: $cal(O)(n log n)$ (sorting stations + heap ops), Auxiliary Space: $cal(O)(n)$.
- *Verification Trace:* Target $D = 100, F = 10$, Stations $[(10, 60), (20, 30), (30, 30), (60, 40)]$:
  At $x=10$: refuels at Station 1 ($+60 L arrow.r 60$). At $x=60$: refuels at Station 4 ($+40 L arrow.r 50$). Reaches $D=100$ with $10 L$ fuel. Minimum stops: *2* (Stations 1 and 4).

```c
while (currentFuel < distNeeded) {
    if (heap->size == 0) { possible = 0; break; }
    HeapElement best = extractMax(heap);
    currentFuel += best.station.fuel;
    chosenStops[stopsCount++] = best.station;
}
```

#pagebreak()

// Q4
#text(size: 9.5pt, weight: "bold", fill: rgb("#1E3A8A"))[Q4: Minimum Cost to Connect Sticks] #h(1fr) #text(size: 8pt, style: "italic")[Huffman Merge Equivalence · $cal(O)(n log n)$]
#v(1pt)
*Problem Statement:* Given sticks of lengths $L_1, dots, L_n$, connecting two sticks of lengths $x$ and $y$ costs $x + y$, leaving a stick of length $x + y$. Find the minimum total connection cost to merge all sticks into one.

*Mathematical Equivalence to Huffman:* Each pairwise merge builds an internal node in a full binary merge tree. Leaf stick $L_i$ contributes $L_i dot d_T(i)$ to the total cost. Hence, $"Total Cost" = sum_{i=1}^n L_i dot d_T(i)$, which is mathematically identical to Huffman tree external path length. Greedily extracting the two smallest sticks via a Min-Heap minimizes the sum.
- *Complexity:* Time: $cal(O)(n log n)$ (Floyd heap build in $cal(O)(n) + n - 1$ extractions), Space: $cal(O)(n)$. 64-bit `long long` prevents overflow.
- *Verification Trace:* Sticks $[1, 8, 3, 5]$:
  Step 1: Merge $1 + 3 = 4$ (Cost $4$). Step 2: Merge $4 + 5 = 9$ (Cost $13$). Step 3: Merge $8 + 9 = 17$ (Cost $30$).
  Final stick length: $17$, Minimum Total Cost: *30*.

```c
while (heap->size > 1) {
    long long a = extractMin(heap), b = extractMin(heap);
    long long cost = a + b; totalCost += cost;
    insertMinHeap(heap, cost);
}
```

#v(8pt)

// Q5
#text(size: 9.5pt, weight: "bold", fill: rgb("#1E3A8A"))[Q5: Candy Distribution Problem] #h(1fr) #text(size: 8pt, style: "italic")[Bi-directional Slope Greedy · $Theta(n)$]
#v(1pt)
*Problem Statement:* $n$ children stand in line with ratings $r_0, dots, r_{n-1}$. Each child gets at least 1 candy. Children rated strictly higher than immediate neighbors must receive more candies than them. Minimize total candies.

*Bi-directional Decomposition:* A single pass fails because descending slopes create right-to-left dependencies.
1. Forward Pass (Left-to-Right): If $r_i > r_{i-1}$, $c_i = c_{i-1} + 1$, else $c_i = 1$. (Satisfies left neighbor).
2. Backward Pass (Right-to-Left): If $r_i > r_{i+1}$, $c_i = max(c_i, c_{i+1} + 1)$. (Satisfies right neighbor while preserving left).
Optimality follows because $c_i = max(c_i^L, c_i^R)$ is component-wise minimal.
- *Complexity:* Time: $Theta(n)$ (two linear scans), Auxiliary Space: $Theta(n)$ (`ratings` and `candies` arrays).
- *Verification Trace:* Ratings $[1, 0, 2] arrow.r$ Candies: ${2, 1, 2}$. Ratings $[12, 8, 5, 2, 1] arrow.r$ Candies: ${5, 4, 3, 2, 1}$.

```c
for (int i = 1; i < n; i++)
    if (ratings[i] > ratings[i - 1]) candies[i] = candies[i - 1] + 1;
for (int i = n - 2; i >= 0; i--)
    if (ratings[i] > ratings[i + 1] && candies[i] < candies[i + 1] + 1)
        candies[i] = candies[i + 1] + 1;
```

#pagebreak()

// Q6
#text(size: 9.5pt, weight: "bold", fill: rgb("#1E3A8A"))[Q6: Reorganise String with K-Distance Apart] #h(1fr) #text(size: 8pt, style: "italic")[Max-Heap & Cooldown Queue · $cal(O)(N log |Sigma|)$]
#v(1pt)
*Problem Statement:* Given string $S$ and integer $K$, rearrange $S$ such that identical characters are at least distance $K$ apart ($j - i >= K$). If impossible, return an empty string.

*Greedy Strategy & Cooldown Barrier:* Count character frequencies. At each slot $i$, greedily place the eligible character with the highest remaining frequency from a Max-Heap (most constrained first). Placed characters enter a circular FIFO cooldown queue of size $K$ with release time $i + K$. If the heap becomes empty while characters remain, pigeonhole deadlock is detected (impossible).
- *Complexity:* Time: $cal(O)(N log |Sigma|) = cal(O)(N)$ (since $|Sigma| <= 256$), Space: $cal(O)(N + |Sigma| + K)$.
- *Verification Trace:* $S = "aabbcc", K = 3 arrow.r$ Result: $"acbacb"$ (Valid, distance between occurrences is 3).
  $S = "aaabc", K = 3 arrow.r$ Frequency of `'a'` is 3, requiring $(3-1) times 3 + 1 = 7 > 5$ slots $arrow.r.double$ Returns `""` (Impossible).

```c
for (int i = 0; i < n; i++) {
    while (!isQueueEmpty(q) && q->array[q->front].releaseTime <= i)
        insertMaxHeap(heap, dequeue(q).item);
    if (heap->size == 0) { possible = 0; break; }
    CharFreq best = extractMax(heap); result[i] = best.ch;
    if (--best.freq > 0) enqueue(q, (CooldownItem){best, i + k});
}
```

#v(8pt)

// Q7
#text(size: 9.5pt, weight: "bold", fill: rgb("#1E3A8A"))[Q7: Minimise Deviation in Array] #h(1fr) #text(size: 8pt, style: "italic")[Two-Way Greedy Monotonic Descent · $cal(O)(n log M log n)$]
#v(1pt)
*Problem Statement:* Positive integer array $A$. Operations: multiply odd by 2, or divide even by 2. Minimize deviation $(max(A) - min(A))$.

*Monotonic Reduction to One-Way Greedy:* Since odd elements can be doubled at most once and evens can only be halved, we pre-multiply every odd element by 2. All elements are now at their upper ceiling! From this state, the *only legal operation is division by 2*. In a Max-Heap, repeatedly pop the maximum $M$. Update $Delta = min(Delta, M - "minVal")$. If $M$ is even, push $M/2$ and update $"minVal"$. If $M$ is odd, it cannot be reduced further; search terminates at global optimum.
- *Complexity:* Time: $cal(O)(n log(M) log n)$, Auxiliary Space: $cal(O)(n)$ for Max-Heap.
- *Verification Trace:* Input $[4, 1, 5, 20, 3] arrow.r$ Doubled odds: $[4, 2, 10, 20, 6]$ (Dev $18$). Halve $20 arrow.r 10$ (Dev $8$), halve $10 arrow.r 5$ (Dev $4$), halve $6 arrow.r 3$ (Dev $3$). Top is $5$ (odd). Search stops. Minimum Deviation = *3*.

```c
while (heap->size > 0) {
    int maxV = extractMax(heap);
    if (maxV - minVal < minDev) minDev = maxV - minVal;
    if (maxV % 2 == 0) {
        int half = maxV / 2; if (half < minVal) minVal = half;
        insertMaxHeap(heap, half);
    } else break;
}
```

#pagebreak()

// Q8
#text(size: 9.5pt, weight: "bold", fill: rgb("#1E3A8A"))[Q8: Minimum Number of Meeting Rooms] #h(1fr) #text(size: 8pt, style: "italic")[Interval Graph Coloring · $cal(O)(n log n)$]
#v(1pt)
*Problem Statement:* Given meeting intervals $[[s_1, e_1], [s_2, e_2], dots]$, find the minimum number of conference rooms required.

*Interval Graph Perfection:* Conflict graph $G$ is an interval graph, where chromatic number equals clique size: $chi(G) = omega(G) = d = max_t |{i: s_i <= t < e_i}|$. Sort meetings by start time $s_i$. Maintain a Min-Heap of room end times. If earliest room end time $<= s_i$, reuse the room; otherwise allocate a new room. Kleinberg & Tardos Theorem 4.4 guarantees optimality.
- *Complexity:* Time: $cal(O)(n log n)$ (start-time sorting + heap), Auxiliary Space: $cal(O)(n)$.
- *Verification Trace:* Meetings $[[0, 30], [5, 10], [15, 20]]$: Meeting 1 creates Room 1 ($e=30$). Meeting 2 creates Room 2 ($e=10$). Meeting 3 arrives at $s=15 >= 10$, reuses Room 2 ($e=20$). Minimum Rooms Needed: *2*.

```c
for (int i = 0; i < n; i++) {
    if (heap->size > 0 && heap->array[0].endTime <= meetings[i].start) {
        Room r = extractMinRoom(heap); r.endTime = meetings[i].end;
        insertMinHeap(heap, r); meetings[i].assignedRoom = r.roomId;
    } else {
        Room nr = {++roomCount, meetings[i].end};
        insertMinHeap(heap, nr); meetings[i].assignedRoom = nr.roomId;
    }
}
```

#v(8pt)

// Q9
#text(size: 9.5pt, weight: "bold", fill: rgb("#1E3A8A"))[Q9: Hu-Tucker Greedy Simulation (Alphabetic Trees)] #h(1fr) #text(size: 8pt, style: "italic")[3-Phase Alphabetic Tree Merge · $cal(O)(n^2)$]
#v(1pt)
*Problem Statement:* Given ordered weights $w_1, dots, w_n$, construct an optimal alphabetic binary search tree minimizing $sum w_i dot "depth"(i)$ while maintaining strict in-order sequence of leaves.

*The Three Hu-Tucker Phases:*
1. Combination Phase: In working sequence, merge compatible pair $(u, v)$ with minimum $w(u) + w(v)$. Two nodes are compatible iff no unmerged original leaves exist between them. Replace $u$ with composite node and delete $v$.
2. Level Assignment Phase: Extract leaf depths $d_i$ from Phase 1 tree (Hu-Tucker theorem guarantees optimal levels).
3. Reconstruction Phase: Bottom-up level-by-level merge pairing adjacent nodes at maximum level. Result preserves planar in-order.
- *Complexity:* Simulation: $cal(O)(n^2)$, reducible to $cal(O)(n log n)$ with priority queues. Space: $cal(O)(n)$.
- *Verification Trace:* Weights $[10, 2, 3, 1, 5] arrow.r$ Levels: $d = [1, 3, 4, 4, 2]$. Cost: $10(1) + 2(3) + 3(4) + 1(4) + 5(2) = bold(42)$.
  Unrestricted Huffman Cost: $41$. Alphabetic Preservation Penalty: $+1$ ($2.44%$ overhead for key order).

```c
/* Compatible Check: all elements between i and j must be internal nodes */
int compatible = 1;
for (int k = i + 1; k < j; k++)
    if (seq[k]->isLeaf) { compatible = 0; break; }
```

#pagebreak()

// Q10
#text(size: 9.5pt, weight: "bold", fill: rgb("#1E3A8A"))[Q10: Greedy Superstring Conjecture (Open Problem)] #h(1fr) #text(size: 8pt, style: "italic")[SCS Overlap & Sept 2026 Disproof · $cal(O)(n^3 L)$]
#v(1pt)
*Problem Statement:* Given strings $cal(S) = {s_1, dots, s_n}$, find the shortest superstring containing every $s_i$. Explore the 40-year-old 2-approximation greedy conjecture and the recent September 2026 ArXiv disproof paper.

*Theoretical Formulation & Modern Disproof:*
- *SCS Problem:* NP-hard and APX-hard. Dual to finding the Maximum-Weight Hamiltonian Path in the overlap digraph.
- *Greedy Overlap Heuristic:* Repeatedly merges the pair $(u, v)$ with maximum suffix-to-prefix overlap $"ov"(u, v)$.
- *The 40-Year-Old Conjecture:* Hypothesized $|T_("greedy")| / |T_("opt")| <= 2.0$ (Gallant et al. 1980, Tarhio & Ukkonen 1988).
- *September 2026 Disproof:* An ArXiv paper constructed a counterexample family with even string length $k >= 10$ yielding:
  $R(k) >= (9k + 2) / (4k + 4) arrow.r 9/4 = 2.25 " as " k arrow.r infinity$.
  This strictly disproves the 2-approximation conjecture! The complex counterexample was discovered using AI automated reasoning.
- *Verification Trace:* Fragments `{"CATG", "ATGC", "TGCA", "GCAT"}` $arrow.r$ Greedy merges with overlap 3 producing `"CATGCAT"` (Length 7, $"OPT" = 7$, Ratio $1.000$). Pathological trap instances demonstrate greedy overlap lock-in.

```c
char *greedySuperstring(int n, char **inputStrings) {
    int count = n; char **active = cloneStrings(inputStrings, n);
    while (count > 1) {
        int bestU = -1, bestV = -1, maxOv = -1;
        for (int i = 0; i < count; i++)
            for (int j = 0; j < count; j++)
                if (i != j && computeOverlap(active[i], active[j]) > maxOv)
                    { maxOv = computeOverlap(active[i], active[j]); bestU = i; bestV = j; }
        active[bestU] = mergeStrings(active[bestU], active[bestV], maxOv);
        deleteString(active, &count, bestV);
    }
    return active[0];
}
```

#v(10pt)

// Synthesis Section
#text(size: 9.5pt, weight: "bold", fill: rgb("#1E3A8A"))[Algorithmic Synthesis & Concluding Remarks]
#v(2pt)

#table(
  columns: (22pt, 125pt, 160pt, 105pt, 65pt),
  stroke: 0.3pt + rgb("#D1D5DB"),
  fill: (col, row) => if row == 0 { rgb("#E5E7EB") } else if calc.even(row) { rgb("#F9FAFB") } else { none },
  align: (center, left, left, left, center),
  inset: (x: 4pt, y: 3pt),
  table.header(
    [*Q. No.*], [*Problem Name*], [*Key Theoretical Invariant*], [*Core Data Structure*], [*Efficiency*]
  ),
  [Q1], [Fractional Knapsack], [Decay exchange priority ($lambda_i$) ordering], [Sorted Array + Cutoff], [$cal(O)(n log n)$],
  [Q2], [Canonical Huffman], [Sibling optimality at maximum depth], [Min-Heap + Bitwise Shifts], [$cal(O)(n log n)$],
  [Q3], [Refueling Stops], [Retroactive maximal fuel replenishment], [Max-Heap (Reverse Greedy)], [$cal(O)(n log n)$],
  [Q4], [Connect Sticks], [Huffman merge tree external path length], [Min-Heap (64-bit int)], [$cal(O)(n log n)$],
  [Q5], [Candy Distribution], [Bi-directional slope constraint decoupling], [Two Linear Pass Arrays], [$Theta(n)$],
  [Q6], [Reorganise String], [Most-constrained character priority + barrier], [Max-Heap + FIFO Queue], [$cal(O)(N log |Sigma|)$],
  [Q7], [Array Deviation], [Monotonic descent from upper bound ceiling], [Max-Heap Priority Queue], [$cal(O)(n log M log n)$],
  [Q8], [Meeting Rooms], [Interval chromatic number $chi(G) = omega(G) = d$], [Min-Heap of End Times], [$cal(O)(n log n)$],
  [Q9], [Hu-Tucker Trees], [Compatible pair merge preserves optimal depth], [Working Sequence List], [$cal(O)(n^2)$],
  [Q10], [Superstring Open], [Max-overlap Hamiltonian path & 2026 disproof], [Overlap Digraph / Greedy], [$cal(O)(n^3 L)$],
)

#v(4pt)
*Key Pedagogical Takeaways:*
1. *Greedy Choice Property & Exchange Arguments:* Proven in Q1 and Q3; exchanging an optimal solution's choice with the greedy choice never degrades the objective value.
2. *Matroids & Independence Systems:* Greedy guarantees exact optimality when the search space forms a matroid (e.g. Huffman codes in Q2/Q4, Interval coloring in Q8).
3. *Priority Queue Dynamics:* Min/Max-heaps efficiently track dynamic bounds in $cal(O)(log n)$ time, turning quadratic searches into log-linear scans.
4. *Limits of Heuristics (Q10):* Overlap-greedy heuristics can suffer from myopic choices, illustrating why approximation proofs require rigorous bounds and can be challenged by modern AI-assisted disproofs.

#v(8pt)
#grid(
  columns: (1fr, 1fr),
  gutter: 15pt,
  rect(stroke: 0.5pt + rgb("#9CA3AF"), inset: 6pt, radius: 3pt)[
    #text(size: 7.5pt)[
      *STUDENT CERTIFICATION:*
      I hereby certify that all mathematical formulations, greedy exchange proofs, C implementations, and traces in this Lab 09 report represent my verified academic work.
      #v(6pt)
      *Signature:* Rishav Kumar (Roll: B125099, CSE-B1)
    ]
  ],
  rect(stroke: 0.5pt + rgb("#9CA3AF"), inset: 6pt, radius: 3pt)[
    #text(size: 7.5pt)[
      *FACULTY EVALUATION:*
      Verified algorithmic correctness, greedy exchange arguments, priority queue invariants, and test traces for Lab 09.
      #v(6pt)
      *Instructor Signature:* Dr. Ajaya Kumar Dash
    ]
  ]
)
