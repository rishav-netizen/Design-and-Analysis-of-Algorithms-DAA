## ✅ Q001 — Put Them in Order
Given a list of mathematical functions, implement a program in **C** to arrange them in **increasing order of asymptotic growth** (Big-O) for sufficiently large values of **n**.

---

## 📈 Growth Comparison Graph

The graph below was generated using the accompanying **Python (Matplotlib)** script from the values produced by the C program.

![Growth Comparison](growth_comparison.png)

> **Note:** The Y-axis is plotted on a logarithmic scale so that all functions remain visible on the same graph. Without a log scale, rapidly growing functions such as \(3^n\) would completely dominate the plot.

---

## 📊 Experimental Observations

The generated graph illustrates how each function grows for values of **n = 1 to 200**.

Some functions appear larger than others because of their constant multipliers. For example, **2³²·n** has a very large constant factor, making it much larger than **2n³** within the tested range. However, asymptotic analysis ignores constant factors when considering sufficiently large values of **n**.

Similarly:

- **12√n** and **50√n** belong to the same asymptotic class because they differ only by a constant multiplier.
- **100n² + 6n** and **n² − 324** both have quadratic growth, as lower-order terms and constants become insignificant for large values of **n**.
- **n^0.51** grows slightly faster than **√n**, even though the difference is small over the tested range.

---

## ✅ Increasing Order of Growth

For **sufficiently large values of n**, the functions are ordered as:

1. **1 / n**
2. **log₂(n)**
3. **12√n**
4. **50√n**
5. **n^0.51**
6. **2³² · n**
7. **n log₂(n)**
8. **100n² + 6n**
9. **n² − 324**
10. **2n³**
11. **n^(log₂ n)**
12. **3ⁿ**

---

## 📝 Conclusion

The graph provides an experimental visualization of how the functions behave for finite values of **n**, while the final ordering is determined using **asymptotic analysis (Big-O/Big-Theta)**. Constant multipliers, additive constants and lower-order terms do not affect the long-term growth rate. As a result, the theoretical ordering may differ from the ordering observed for small values of **n**, but it correctly represents the behaviour of the functions as **n → ∞**.