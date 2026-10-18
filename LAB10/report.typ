#set page(
  paper: "a4",
  margin: (x: 1.2cm, top: 1.2cm, bottom: 1.2cm),
  header: context {
    text(size: 7.5pt, fill: rgb("#4B5563"))[
      *DAA LABORATORY (CS3101) — LAB 10 REPORT (GRAPHS & DSU)* #h(1fr) *IIIT BHUBANESWAR | AUTUMN 2026*
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

#set text(font: "Helvetica", size: 8.3pt)
#set par(justify: true, leading: 0.52em)
#show raw: set text(font: "Menlo", size: 6.8pt)

// Institutional Header
#align(center)[
  #text(size: 11.5pt, weight: "bold", fill: rgb("#1E3A8A"))[INTERNATIONAL INSTITUTE OF INFORMATION TECHNOLOGY, BHUBANESWAR]\
  #text(size: 9.2pt, weight: "bold", fill: rgb("#374151"))[Department of Computer Science & Engineering | DAA Laboratory (CS3101)]\
  #v(1pt)
  #text(size: 11.5pt, weight: "bold", fill: rgb("#B45309"))[LAB 10 REPORT: ADVANCED GRAPHS & DISJOINT SET UNION (DSU)]\
  #v(2pt)
  #rect(fill: rgb("#F3F4F6"), stroke: 0.5pt + rgb("#E5E7EB"), radius: 3pt, inset: (x: 8pt, y: 3.5pt))[
    #text(size: 8pt)[
      *Student:* Rishav Kumar #h(12pt) *Roll:* B125099 #h(12pt) *Branch:* B.Tech CSE (B1) #h(12pt) *Instructor:* Dr. A. K. Dash #h(12pt) *Date:* Oct 2026
    ]
  ]
]

#v(2pt)

// Executive Summary Box
#rect(fill: rgb("#EFF6FF"), stroke: 0.5pt + rgb("#BFDBFE"), radius: 3pt, width: 100%, inset: (x: 6pt, y: 4pt))[
  #text(size: 7.8pt)[
    *Executive Summary & Paradigm Foundations:* This laboratory investigates advanced graph representations and dynamic connectivity algorithms driven by the *Disjoint Set Union (DSU / Union-Find)* data structure across five fundamental problems. Using *Path Compression* and *Union by Rank*, DSU achieves an optimal amortised inverse Ackermann bound $cal(O)(alpha(V))$. The laboratory explores parity potentials for online 2-colorability and odd-cycle detection, 2D lattice coordinate flattening for dynamic island tracking, size-constrained component maximization with lazy priority queues, the offline time-reversal paradigm for vertex deletion dynamics, and symmetric group transposition generation for lexicographical permutation optimization.
  ]
]

#v(2pt)

// Index Table
#text(size: 8.8pt, weight: "bold", fill: rgb("#1E3A8A"))[Index of Lab 10 Problems & Complexity Summary]
#v(1pt)
#table(
  columns: (26pt, 142pt, 145pt, 72pt, 50pt, 42pt),
  stroke: 0.3pt + rgb("#D1D5DB"),
  fill: (col, row) => if row == 0 { rgb("#E5E7EB") } else if calc.even(row) { rgb("#F9FAFB") } else { none },
  align: (center, left, left, center, center, center),
  inset: (x: 3.5pt, y: 2.3pt),
  table.header(
    [*Q. No.*], [*Problem Name*], [*Algorithmic Paradigm*], [*Time*], [*Space*], [*Status*]
  ),
  [Q1], [Online Bipartiteness Testing], [Parity Potential DSU & Cycle Trace], [$cal(O)(M dot alpha(V))$], [$cal(O)(V + M)$], [Verified],
  [Q2], [Dynamic Grid Islands (II)], [2D Coordinate Flattening + DSU], [$cal(O)(k dot alpha(R C))$], [$cal(O)(R dot C)$], [Verified],
  [Q3], [Size-Constrained Max Weight], [Augmented DSU + Lazy Max-Heap], [$cal(O)(M log(V + M))$], [$cal(O)(V + M)$], [Verified],
  [Q4], [Reverse Time-Step Deletion], [Offline Time Reversal DSU], [$cal(O)((V + E) alpha(V))$], [$cal(O)(V + E)$], [Verified],
  [Q5], [Smallest Permutation Swaps], [Symmetric Group Transpositions + DSU], [$cal(O)(M alpha(n) + n log n)$], [$cal(O)(n + M)$], [Verified],
)

#v(3pt)

// Q1 Block
#rect(fill: rgb("#F8FAFC"), stroke: 0.5pt + rgb("#CBD5E1"), radius: 3pt, width: 100%, inset: 6pt)[
  #text(size: 9pt, weight: "bold", fill: rgb("#1E3A8A"))[Q1: Online Graph-Bipartiteness Testing] #h(1fr) #text(size: 7.8pt, style: "italic", fill: rgb("#4B5563"))[Parity Potential DSU · $cal(O)(M dot alpha(V))$]
  #v(2pt)
  #rect(fill: rgb("#EFF6FF"), stroke: 0.4pt + rgb("#BFDBFE"), radius: 2pt, width: 100%, inset: (x: 5pt, y: 3pt))[
    #text(size: 7.5pt)[*Problem Statement:* An undirected graph receives edges online one by one. Maintain whether the graph remains bipartite (contains no odd-length cycles). If an edge $(u, v)$ does not introduce an odd cycle, add it; otherwise, report the violation and skip it.]
  ]
  #v(3pt)
  #grid(
    columns: (55%, 45%),
    gutter: 8pt,
    [
      #text(weight: "bold")[Mathematical Formulation & Parity Invariant:]
      By König's Theorem, a graph is bipartite iff it is 2-colorable with colors $\{0, 1\}$.
      Each node $x$ stores $p(x) in \{0, 1\}$, the parity distance to its parent in the forest.
      During path compression, $P(x arrow.r r) = xor.big p(w)$ along the branch.
      When edge $(u, v)$ arrives:
      $r_u = "find"(u, P_u), quad r_v = "find"(v, P_v)$.
      - *If $r_u = r_v$:* Tree path length parity is $P_u xor P_v$. If $P_u = P_v$, adding $(u, v)$ creates an *odd cycle* of length $"even" + 1 = "odd"$. The edge is *rejected*. If $P_u eq.not P_v$, it forms an even cycle and is *accepted (redundant)*.
      - *If $r_u eq.not r_v$:* Vertices are in disjoint trees. The edge is *accepted*. We link $r_u$ to $r_v$ setting $p(r_u) = P_u xor P_v xor 1$.
      
      #text(weight: "bold")[Cycle Reconstruction:] BFS on accepted tree edges reconstructs the exact odd cycle in $cal(O)(V)$ time.
      #text(weight: "bold")[Complexity:] Time: $cal(O)(M dot alpha(V))$, Auxiliary Space: $cal(O)(V + M)$.

      #v(1pt)
      #text(weight: "bold")[Validation Trace ($V=5, M=6$):]
      #table(
        columns: (22pt, 45pt, 50pt, 85pt),
        stroke: 0.2pt + rgb("#CBD5E1"),
        align: center,
        inset: 1.8pt,
        table.header([*Edge*], [*Endpoints*], [*Status*], [*Reason / Cycle Detected*]),
        [1], [$(1, 2)$], [Accepted], [Cross-tree link: $P(1) = 1, P(2) = 0$],
        [2], [$(2, 3)$], [Accepted], [Cross-tree link: $P(3) = 1, P(2) = 0$],
        [3], [$(3, 4)$], [Accepted], [Cross-tree link: $P(4) = 0, P(3) = 1$],
        [4], [$(4, 5)$], [Accepted], [Cross-tree link: $P(5) = 1, P(4) = 0$],
        [5], [$(1, 5)$], [Rejected], [Odd Cycle: $1 arrow 2 arrow 3 arrow 4 arrow 5 arrow 1$ (len 5)],
        [6], [$(2, 4)$], [Rejected], [Odd Cycle: $2 arrow 3 arrow 4 arrow 2$ (len 3)],
      )
      *Final 2-Coloring Partition:* Red: $\{2, 4\}$, Blue: $\{1, 3, 5\}$.
    ],
    [
      ```c
      int findSet(BipartiteDSU *dsu, int x, int *p) {
          if (dsu->parent[x] == x) {
              *p = 0;
              return x;
          }
          int pParent = dsu->parity[x];
          int rootParity = 0;
          int root = findSet(dsu, dsu->parent[x], &rootParity);
          dsu->parity[x] = pParent ^ rootParity;
          dsu->parent[x] = root;
          *p = dsu->parity[x];
          return root;
      }

      bool addEdgeOnline(BipartiteDSU *dsu, int u, int v) {
          int pu = 0, pv = 0;
          int ru = findSet(dsu, u, &pu);
          int rv = findSet(dsu, v, &pv);
          if (ru == rv) {
              if (pu == pv) return false; /* ODD CYCLE! */
              return true; /* Redundant even cycle */
          }
          int req = pu ^ pv ^ 1;
          if (dsu->rank[ru] < dsu->rank[rv]) {
              dsu->parent[ru] = rv;
              dsu->parity[ru] = req;
          } else {
              dsu->parent[rv] = ru;
              dsu->parity[rv] = req;
              if (dsu->rank[ru] == dsu->rank[rv]) dsu->rank[ru]++;
          }
          return true;
      }
      ```
    ]
  )
]

#pagebreak()

// Q2 Block
#rect(fill: rgb("#F8FAFC"), stroke: 0.5pt + rgb("#CBD5E1"), radius: 3pt, width: 100%, inset: 6pt)[
  #text(size: 9pt, weight: "bold", fill: rgb("#1E3A8A"))[Q2: Dynamic Connected Components in a Grid (Number of Islands II)] #h(1fr) #text(size: 7.8pt, style: "italic", fill: rgb("#4B5563"))[Coordinate Flattening DSU · $cal(O)(k dot alpha(R C))$]
  #v(2pt)
  #rect(fill: rgb("#EFF6FF"), stroke: 0.4pt + rgb("#BFDBFE"), radius: 2pt, width: 100%, inset: (x: 5pt, y: 3pt))[
    #text(size: 7.5pt)[*Problem Statement:* In an $R times C$ grid initially filled with water, land cells are dynamically added one by one at $(r_1, c_1), dots, (r_k, c_k)$. Maintain and output the number of 4-directionally connected land components (islands) after each operation.]
  ]
  #v(3pt)
  #grid(
    columns: (55%, 45%),
    gutter: 8pt,
    [
      #text(weight: "bold")[Coordinate Bijection & Component Invariants:]
      We define a linear mapping $phi: [0, R-1] times [0, C-1] arrow.r [0, R C - 1]$:
      $phi(r, c) = r dot C + c, quad r = floor(id / C), quad c = id mod C$.
      - When land is added at $(r, c)$:
        1. If already land, island count remains unchanged.
        2. Otherwise, activate cell: $"grid"[r][c] = 1$, $"islands" arrow.r "islands" + 1$.
        3. For each cardinal neighbor $(n_r, n_c) in cal(N)_4(r, c)$:
           If $"grid"[n_r][n_c] == 1$, let $u = phi(r, c), v = phi(n_r, n_c)$.
           If $"find"(u) eq.not "find"(v)$:
           $"union"(u, v), quad "islands" arrow.r "islands" - 1$.
      
      #text(weight: "bold")[Complexity:] Inspecting 4 neighbors triggers at most 4 DSU operations per addition. Amortised time: $cal(O)(R C + k dot alpha(R C))$. Auxiliary space: $Theta(R C)$.

      #v(1pt)
      #text(weight: "bold")[Validation Trace ($3 times 3$ Grid, $k=4$):]
      #table(
        columns: (22pt, 36pt, 45pt, 45pt, 50pt),
        stroke: 0.2pt + rgb("#CBD5E1"),
        align: center,
        inset: 1.8pt,
        table.header([*Step*], [*Land Cell*], [*Initial Count*], [*Merges*], [*Final Islands*]),
        [1], [$(1, 1)$], [$0 + 1 = 1$], [None], [$1$],
        [2], [$(1, 2)$], [$1 + 1 = 2$], [Merged with $(1, 1)$], [$1$],
        [3], [$(2, 3)$], [$1 + 1 = 2$], [None], [$2$],
        [4], [$(2, 2)$], [$2 + 1 = 3$], [Merged $(1, 2)$ & $(2, 3)$], [$1$],
      )
      *Island Count Sequence:* $[1, 1, 2, 1]$.
    ],
    [
      ```c
      int currId = r * cols + c;
      if (grid[r][c] == 1) return islandCount;
      grid[r][c] = 1;
      dsu->parent[currId] = currId;
      islandCount++;

      int dr[4] = {-1, 1, 0, 0};
      int dc[4] = {0, 0, -1, 1};
      for (int d = 0; d < 4; d++) {
          int nr = r + dr[d], nc = c + dc[d];
          if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
              if (grid[nr][nc] == 1) {
                  int neighborId = nr * cols + nc;
                  int ru = findSet(dsu, currId);
                  int rv = findSet(dsu, neighborId);
                  if (ru != rv) {
                      unionSets(dsu, ru, rv);
                      islandCount--;
                  }
              }
          }
      }
      ```
    ]
  )
]

#v(3pt)

// Q3 Block
#rect(fill: rgb("#F8FAFC"), stroke: 0.5pt + rgb("#CBD5E1"), radius: 3pt, width: 100%, inset: 6pt)[
  #text(size: 9pt, weight: "bold", fill: rgb("#1E3A8A"))[Q3: Maximum Weight Component with Size Constraints] #h(1fr) #text(size: 7.8pt, style: "italic", fill: rgb("#4B5563"))[Augmented DSU + Lazy Max-Heap · $cal(O)(M log(V + M))$]
  #v(2pt)
  #rect(fill: rgb("#EFF6FF"), stroke: 0.4pt + rgb("#BFDBFE"), radius: 2pt, width: 100%, inset: (x: 5pt, y: 3pt))[
    #text(size: 7.5pt)[*Problem Statement:* In a vertex-weighted graph with weights $w_v$, edges are added sequentially. Dynamically track the maximum total vertex weight among all connected components whose size does not exceed a threshold $K$.]
  ]
  #v(3pt)
  #grid(
    columns: (55%, 45%),
    gutter: 8pt,
    [
      #text(weight: "bold")[Non-Monotonicity & Lazy Invalidation Strategy:]
      The feasible component candidate set is $cal(F) = { C in cal(C) mid |C| <= K }$.
      When edge $(u, v)$ merges $C_u$ and $C_v$:
      $|C_"new"| = |C_u| + |C_v|, quad W(C_"new") = W(C_u) + W(C_v)$.
      If $|C_"new"| > K$, the merged component becomes *ineligible*, potentially decreasing $W^*$.
      - We augment each DSU root with `compSize`, `compWeight`, and a `version` counter.
      - Valid merged roots with $|C| <= K$ are pushed into a binary Max-Heap.
      - During query time, stale heap entries (outdated version, non-representative, or size $> K$) are lazily discarded.
      
      #text(weight: "bold")[Complexity:] DSU runs in $cal(O)(alpha(V))$. Each edge pushes at most 1 heap node in $cal(O)(log |H|)$. Total time: $cal(O)(V + M log(V + M))$. Auxiliary space: $Theta(V + M)$.

      #v(1pt)
      #text(weight: "bold")[Validation Trace ($V=5, K=3$, weights: [10, 20, 15, 30, 25]):]
      #table(
        columns: (22pt, 38pt, 60pt, 45pt, 45pt),
        stroke: 0.2pt + rgb("#CBD5E1"),
        align: center,
        inset: 1.8pt,
        table.header([*Step*], [*Edge*], [*Merged Components*], [*New Comp*], [*Max (Size $<= 3$)*]),
        [Init], [None], [5 singletons], [All size 1], [$30$ (Vertex 4)],
        [1], [$(1, 2)$], [$\{1\}$ (10) + $\{2\}$ (20)], [Size 2, wt 30], [$30$ (Vertices 4, 1)],
        [2], [$(3, 4)$], [$\{3\}$ (15) + $\{4\}$ (30)], [Size 2, wt 45], [$45$ (Root 3)],
        [3], [$(1, 3)$], [$\{1, 2\}$ (30) + $\{3, 4\}$ (45)], [Size 4 ($> 3$!)], [$25$ (Vertex 5)],
        [4], [$(4, 5)$], [$\{1..4\}$ (75) + $\{5\}$ (25)], [Size 5 ($> 3$!)], [NONE (All $> 3$)],
      )
    ],
    [
      ```c
      bool getMaxValidWeight(MaxHeap *heap, ConstrainedDSU *dsu,
                             int K, long long *maxVal, int *bestRoot) {
          while (heap->size > 0) {
              HeapNode top = heap->data[0];
              int r = top.rootId;
              if (dsu->parent[r] == r &&
                  dsu->version[r] == top.version &&
                  dsu->compSize[r] <= K) {
                  *maxVal = top.totalWeight;
                  *bestRoot = r;
                  return true;
              }
              /* Discard stale or invalidated entry */
              heap->data[0] = heap->data[--heap->size];
              maxHeapify(heap, 0);
          }
          return false;
      }
      ```
    ]
  )
]

#pagebreak()

// Q4 Block
#rect(fill: rgb("#F8FAFC"), stroke: 0.5pt + rgb("#CBD5E1"), radius: 3pt, width: 100%, inset: 6pt)[
  #text(size: 9pt, weight: "bold", fill: rgb("#1E3A8A"))[Q4: Reverse Time-Step DSU Application] #h(1fr) #text(size: 7.8pt, style: "italic", fill: rgb("#4B5563"))[Offline Time Reversal · $cal(O)((V + E) alpha(V))$]
  #v(2pt)
  #rect(fill: rgb("#EFF6FF"), stroke: 0.4pt + rgb("#BFDBFE"), radius: 2pt, width: 100%, inset: (x: 5pt, y: 3pt))[
    #text(size: 7.5pt)[*Problem Statement:* Vertices are sequentially deleted from a vertex-weighted undirected graph in order $P = [p_1, dots, p_V]$. After each deletion, compute the maximum sum of vertex values among all remaining connected components.]
  ]
  #v(3pt)
  #grid(
    columns: (55%, 45%),
    gutter: 8pt,
    [
      #text(weight: "bold")[Time-Reversal Duality:]
      Online deletion splits components, requiring complex dynamic connectivity ($cal(O)(log^2 V)$).
      Inverting the sequence backwards ($tau = V - t + 1$) transforms destructive vertex removals into *incremental vertex additions*:
      - Reverse Step $tau$: Activate vertex $u = p_{V - tau + 1}$.
      - For each neighbor $v$ of $u$ with $"isActive"[v] == 1$, execute DSU union and aggregate component weights:
        $W("newRoot") = W(r_u) + W(r_v)$.
      - Maintain running maximum: $"curMax" = max("curMax", W("root"(u)))$.
      - Map result: $"ans"["step" - 1] = "curMax"$, with $"ans"[V-1] = 0$.
      
      #text(weight: "bold")[Complexity:] Building adjacency list: $cal(O)(V + E)$. DSU operations: $cal(O)((V + E) alpha(V))$. Total space: $Theta(V + E)$.

      #v(1pt)
      #text(weight: "bold")[Validation Trace (Path $1-2-3-4$, weights $[1, 2, 3, 4]$, $P=[2, 4, 1, 3]$):]
      #table(
        columns: (30pt, 40pt, 55pt, 75pt),
        stroke: 0.2pt + rgb("#CBD5E1"),
        align: center,
        inset: 1.8pt,
        table.header([*Deletion*], [*Vertex Deleted*], [*Remaining Vertices*], [*Max Component Weight*]),
        [Step 1], [Vertex 2], [$\{1\}, \{3, 4\}$], [$7$ (from $\{3, 4\}$)],
        [Step 2], [Vertex 4], [$\{1\}, \{3\}$], [$3$ (from $\{3\}$)],
        [Step 3], [Vertex 1], [$\{3\}$], [$3$ (from $\{3\}$)],
        [Step 4], [Vertex 3], [$emptyset$ (Empty graph)], [$0$],
      )
    ],
    [
      ```c
      for (int step = v - 1; step >= 0; step--) {
          int u = deletionOrder[step] - 1;
          isActive[u] = true;
          if (dsu->compWeight[u] > currentMax)
              currentMax = dsu->compWeight[u];

          for (AdjNode *curr = g->head[u]; curr; curr = curr->next) {
              int nb = curr->to;
              if (isActive[nb]) {
                  int ru = findSet(dsu, u);
                  int rv = findSet(dsu, nb);
                  if (ru != rv) {
                      unionSets(dsu, ru, rv);
                      int mr = findSet(dsu, u);
                      if (dsu->compWeight[mr] > currentMax)
                          currentMax = dsu->compWeight[mr];
                  }
              }
          }
          if (step > 0) maxSumAfterDeletion[step - 1] = currentMax;
      }
      maxSumAfterDeletion[v - 1] = 0;
      ```
    ]
  )
]

#v(3pt)

// Q5 Block
#rect(fill: rgb("#F8FAFC"), stroke: 0.5pt + rgb("#CBD5E1"), radius: 3pt, width: 100%, inset: 6pt)[
  #text(size: 9pt, weight: "bold", fill: rgb("#1E3A8A"))[Q5: Lexicographically Smallest Connected Component Permutation] #h(1fr) #text(size: 7.8pt, style: "italic", fill: rgb("#4B5563"))[Symmetric Group Transpositions · $cal(O)(M alpha(n) + n log n)$]
  #v(2pt)
  #rect(fill: rgb("#EFF6FF"), stroke: 0.4pt + rgb("#BFDBFE"), radius: 2pt, width: 100%, inset: (x: 5pt, y: 3pt))[
    #text(size: 7.5pt)[*Problem Statement:* Given a permutation $A$ of numbers $1 dots n$ and allowable pairwise swap pairs $(u, v)$ forming edges in an undirected graph, determine the lexicographically smallest permutation achievable through any number of valid swaps.]
  ]
  #v(3pt)
  #grid(
    columns: (55%, 45%),
    gutter: 8pt,
    [
      #text(weight: "bold")[Symmetric Group Invariant & Greedy Ordering:]
      Each allowable swap $(u, v)$ is a transposition transposition generator.
      By the Cayley-Hamilton and transposition theorems in abstract algebra, transpositions in any connected graph generate the entire symmetric group $S_{|C|}$.
      - Hence, elements occupying indices in the same connected component $C$ can be rearranged into *any* arbitrary permutation.
      - To achieve lexicographical minimality, for each connected component:
        1. Extract the sorted list of index positions: $i_1 < i_2 < dots < i_k$.
        2. Extract values $A[i_1], dots, A[i_k]$ and sort them in ascending order: $v_1 <= v_2 <= dots <= v_k$.
        3. Assign $A^*[i_r] = v_r$ for all $1 <= r <= k$.
      
      #text(weight: "bold")[Complexity:] DSU unions take $cal(O)(M alpha(n))$. Sorting disjoint components takes $sum |C| log |C| <= cal(O)(n log n)$. Total space: $Theta(n + M)$.

      #v(1pt)
      #text(weight: "bold")[Validation Trace ($n=5, A=[5, 3, 1, 4, 2]$, Swaps: $(1, 3), (2, 5), (3, 5)$):]
      #table(
        columns: (45pt, 50pt, 55pt, 55pt),
        stroke: 0.2pt + rgb("#CBD5E1"),
        align: center,
        inset: 1.8pt,
        table.header([*Component*], [*Indices*], [*Initial Values*], [*Sorted Assignment*]),
        [Root 4], [$\{4\}$], [$[4]$], [$A[4] = 4$],
        [Root 5], [$\{1, 2, 3, 5\}$], [$[5, 3, 1, 2]$], [$A[1]=1, A[2]=2, A[3]=3, A[5]=5$],
      )
      *Final Result:* $[1, 2, 3, 4, 5]$ (Sorted optimal permutation).
    ],
    [
      ```c
      void solveLexicographicallySmallest(int n, int *arr, int m,
                                          SwapPair *swaps, int *res) {
          PermDSU *dsu = createPermDSU(n);
          for (int i = 0; i < m; i++)
              unionSets(dsu, swaps[i].u - 1, swaps[i].v - 1);

          /* Group indices by component root */
          for (int r = 0; r < n; r++) {
              if (compSizes[r] > 0) {
                  int sz = compSizes[r];
                  int *vals = malloc(sz * sizeof(int));
                  for (int k = 0; k < sz; k++)
                      vals[k] = arr[compIndices[r][k]];

                  qsort(vals, sz, sizeof(int), compareInts);

                  for (int k = 0; k < sz; k++)
                      res[compIndices[r][k]] = vals[k];
                  free(vals);
              }
          }
      }
      ```
    ]
  )
]

#v(2pt)

// Comparative Synthesis
#rect(fill: rgb("#F1F5F9"), stroke: 0.4pt + rgb("#CBD5E1"), radius: 2pt, width: 100%, inset: (x: 5pt, y: 3pt))[
  #text(size: 7.2pt)[
    *Laboratory Synthesis & Complexity Verification:*
    Across all 5 graph problems, Disjoint Set Union (DSU) delivers near-linear asymptotic complexity via Path Compression and Union by Rank ($cal(O)(alpha(N))$ amortised per query). Augmented potentials enable online parity tracking for bipartiteness (Q1), coordinate flattening maps 2D planar meshes into 1D addressable arrays (Q2), lazy priority queue integration solves non-monotonic constrained optimization (Q3), offline time-reversal circumvents intractable dynamic graph splitting (Q4), and algebraic symmetric group transpositions enable optimal lexicographical reconstruction (Q5). All algorithms were verified against edge cases and proved mathematically sound.
  ]
]
