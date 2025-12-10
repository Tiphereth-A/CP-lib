// Extended Euclidean path - 扩展欧几里得路径

考虑直线 $s = (p x + r) / q, space x in (0, l]$, 以及所有的竖线 $x = k, space k in ZZ$ 与横线 $y = h, space h in ZZ$

从左向右扫描直线 $s$, 若遇到与横线的交点, 则执行操作 $a$; 若遇到与竖线的交点, 则执行操作 $b$;

若同时遇到横线与竖线的交点, 则先执行操作 $a$ 再执行操作 $b$.

用 $F(p, q, r, l, a, b)$ 表示上述操作的序列, 如 $F(3, 5, 2, 6, a, b) = a b b a b b a b a b$

则迭代方式如下:

+ $p >= q$ 时, 令 $b' = a^(p slash q) b$, 则 $F(p, q, r, l, a, b) = F(p mod q, q, r, l, a, b')$
+ $p < q$ 时, 交换 $p, q$ 并回到上一步

  注意到第 $d$ 个 $b$ 前有 $floor((p d + r) / q)$ 个 $a$, 设第 $alpha$ 个 $a$ 在第 $beta$ 个 $b$ 之前, 则 $beta > floor((p alpha + r) / q) arrow.r.double alpha <= floor((q beta - r - 1) / p)$

  即第 $beta$ 个 $b$ 之前有 $floor((q beta - r - 1) / p)$ 个 $a$

  迭代子问题应与原问题形式相同, 所以截掉第一个 $a$ 之前的操作, 对之后的部分递归

  假设现在去掉了第一个 $a$ 以及它之前的 $b$, 则剩余的第 $c$ 个 $a$ 与第 $c-1$ 个 $a$ 之间剩余的 $b$ 的个数为

  $
  floor((q(c+1) - r - 1) / p) - floor((q c - r - 1) / p) = floor((q c + q - r - 1) / p) - floor((q(c-1) + q - r - 1) / p)
  $

  从而 $F(p, q, r, l, a, b) = b^(floor((q-r-1) slash p)) a F(q, p, (q-r-1) mod p, c-1, b, a) b^(l - floor((q c - r - 1) slash p))$

  其中 $c = floor((p l + r) / q)$

=== 数据类示例

```cpp
#include "../../src/exeuclid_node.cpp"
```

=== 参考链接

#figure(
  box(stroke: 0.5pt, inset: 8pt, radius: 4pt)[
    #image.decode(read("../../src/qr_luogu_225005.svg", encoding: none), width: 15%, format: "svg")
  ],
  caption: [洛谷博客: 扩展欧几里得路径]
)
