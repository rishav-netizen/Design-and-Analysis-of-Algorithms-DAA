# Question 3: Convolution Operation on Vectors ($O(n \log n)$)

## 📌 Problem Overview
The convolution of two vectors $A$ and $B$ (of lengths $m$ and $n$) creates a new vector $C$. 
A direct mathematical approach (nested loops) yields a time complexity of $\mathcal{O}(m \cdot n)$. The objective is to design a **Divide and Conquer** algorithm to drop this complexity strictly down to $\mathcal{O}(n \log n)$.

---

## 💡 Why the Fast Fourier Transform (FFT)?

To achieve an $O(n \log n)$ barrier for polynomial/vector convolution, we rely on the **Convolution Theorem**. The theorem states that convolution in the time domain is equivalent to point-wise multiplication in the frequency domain.

1. **FFT ($\mathcal{O}(n \log n)$):** Convert vector $A$ and vector $B$ from the coefficient representation to the point-value (frequency) representation.
2. **Point-wise Multiplication ($\mathcal{O}(n)$):** Multiply the corresponding evaluated points.
3. **Inverse FFT ($\mathcal{O}(n \log n)$):** Convert the result back to coefficient representation.

**Total Time Complexity:** $\mathcal{O}(n \log n)$

---

## 🛠️ Implementation Details
The implementation in [`main.c`](./main.c) natively handles standard C99 `complex.h`:
1. **Dynamic Padding:** FFT requires array lengths to be powers of 2. The code dynamically shifts array bounds to the nearest power of 2 ($N \ge m + n - 1$).
2. **Recursive Divide & Conquer:** Separates arrays into even/odd indices repeatedly.
3. **Roots of Unity:** Computes $e^{2\pi i / N}$ utilizing `<math.h>`.

---

## ⚙️ Compilation & Execution

Math and complex libraries are heavily relied upon.

```bash
# Compile
gcc -o main main.c -lm

# Run
./main
```

---


### 📤 Sample Output
```text
Enter the size of vector A: 3
Enter the elements of vector A:
1 2 3
Enter the size of vector B: 3
Enter the elements of vector B:
4 5 6
Result of Convolution (Vector C):
{4, 13, 28, 27, 18}
```

---

## 📊 Complexity Summary

| Phase | Time Complexity | Space Complexity |
| :--- | :---: | :---: |
| **Padding & Allocation** | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ |
| **FFT Transforms** | **$\mathcal{O}(n \log n)$** | $\mathcal{O}(n)$ |
| **Point-wise Multiplication** | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ |
| **Inverse FFT** | **$\mathcal{O}(n \log n)$** | $\mathcal{O}(n)$ |
