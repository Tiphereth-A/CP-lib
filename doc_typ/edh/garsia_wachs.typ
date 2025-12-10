// Garsia-Wachs algorithm - Garsia-Wachs 算法

用于构建最优二叉查找树和 Huffman 码的算法

传入 $n$ 个数 $v_1, dots, v_n$, 每次挑选最小的两个数删除, 并将这两个数的和插入, 直到序列中只剩一个数

=== 输入

`v`: 长度为 $n+2$ 的数组, 其中 $v_0 = v_(n+1) = infinity$, $v_1, dots, v_n$ 为实际参与合并的数据

`f(m0, m1, r, j, a)`: 合并结点时调用的函数, 我们将编号为 `m0` 和 `m1` 的结点合并, 新结点的编号为 `r`, 值为 `a`, 在 `v` 中的下标为 `j`. 其中对于初始的 $v_i$, 其编号为 $i$. 注意编号和 `v` 的下标没有对应关系, 且 $v_j = a$ 只在调用函数时成立

=== 复杂度

在认为 `std::vector` 插入和删除的复杂度都是 $O(1)$ 时为 $O(n log n)$

=== 参考文献

#figure(
  box(stroke: 0.5pt, inset: 8pt, radius: 4pt)[
    #image.decode(read("../../src/qr_garsia1977.svg", encoding: none), width: 15%, format: "svg")
  ],
  caption: [Garsia & Wachs, 1977]
)

#figure(
  box(stroke: 0.5pt, inset: 8pt, radius: 4pt)[
    #image.decode(read("../../src/qr_kingston1988.svg", encoding: none), width: 15%, format: "svg")
  ],
  caption: [Kingston, 1988]
)
