
求解如下线性规划问题:

$ 
mat(
  max, c^T x;
  "s.t.", A x <= b comma x >= 0
)
$

若无解则返回 `-inf`, 若无界则返回 `inf`, 否则返回 $c^T x$ 的最大值. 输入的 `x` 会被修改为解. 不保证数值稳定性. $x = 0$ 最好在可行域中.

=== 使用

```cpp
using T = double;
vvec<T> A{{1, -1}, {-1, 1}, {-1, -2}};
vec<T> b{1, 1, -4}, c{-1, -1}, x;
T val = LPSolver(A, b, c).solve(x);
```

=== 原问题与对偶问题

#table(
  columns: 2,
  stroke: 0.5pt,
  align: center + horizon,
  [原问题], [对偶问题],
  [$max_x c^T x$], [$min_y b^T y$],
  [$n$ 个变量 $x_1, dots, x_n$], [$n$ 个限制条件 $A^T y gtreqqless c$],
  [$x_i >= 0$], [第 $i$ 个限制条件为 $>= c_i$],
  [$x_i <= 0$], [第 $i$ 个限制条件为 $<= c_i$],
  [$x_i in RR$], [第 $i$ 个限制条件为 $= c_i$],
  [$m$ 个限制条件 $A x gtreqqless b$], [$m$ 个变量 $y_1, dots, y_m$],
  [第 $i$ 个限制条件为 $>= b_i$], [$y_i <= 0$],
  [第 $i$ 个限制条件为 $<= b_i$], [$y_i >= 0$],
  [第 $i$ 个限制条件为 $= b_i$], [$y_i in RR$],
)

#table(
  columns: 4,
  stroke: 0.5pt,
  align: center + horizon,
  table.cell(colspan: 2)[原问题], table.cell(colspan: 2)[对偶问题],
  [$max$], [$3x_1+4x_2$], [$min$], [$7y_1$],
  [s.t.], [$5x_1+6x_2=7$], [s.t.], [$5y_1 >= 3$],
  [], [], [], [$6y_2 >= 4$],
  [], [$x_1 >= 0, x_2 >= 0$], [], [$y_1 in RR$],
)

=== 复杂度

$O(N M dot "pivots")$, where a pivot may be e.g. an edge relaxation. $O(2^N)$ in the general case.

=== 参考

#figure(
  box(stroke: 0.5pt, inset: 8pt, radius: 4pt)[
    #image.decode(read("../../src/qr_bqi343cp.svg", encoding: none), width: 15%, format: "svg")
  ],
  caption: [Reference: bqi343cp]
)
