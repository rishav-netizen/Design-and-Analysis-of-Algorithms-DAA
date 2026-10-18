# Q2 - Search the Defective Coin

The program assumes at most one coin can be lighter. It divides the current candidates into two equal groups and compares their total weights, which simulates putting the groups on a balance. The lighter side is searched again. If both sides balance, an odd leftover coin is checked; otherwise there is no defective coin.

```sh
cc -std=c11 -Wall -Wextra main.c -o q2
./q2
```

For example, use `8` coins with weights `10 10 10 9 10 10 10 10`. The answer is position 4. The candidate set is halved at each level, so the number of balance operations is `O(log n)`.
