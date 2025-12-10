
用于计算满足如下条件 (Monotone) 的矩阵 $A$ 每行的 $op("argmin")$:

#align(center)[
  令 $h(r) = max op("argmin")_i A_(r,i)$, 则 $h$ 单调不降
]

不难发现可以分治: 对当前矩阵, 找到中间一行的 $op("argmin")$, 然后就可根据这个将矩阵分为更小的两个矩阵

如果 Monotone 矩阵 $A$ 还满足任意 $2 times 2$ 的子矩阵都是 Monotone 的, 则称 $A$ 是 Totally monotone 的

如果 Monotone 矩阵 $A$ 还满足 $forall i, j, space A_(i,j) + A_(i+1,j+1) <= A_(i+1,j) + A_(i,j+1)$, 则称 $A$ 是 Monge 的

显然若 $A$ 是 Monge 的则一定是 Totally monotone 的

=== 复杂度

$O(c(1 + log(r slash c)))$, 其中 $r$ 为矩阵行数, $c$ 为矩阵列数

=== 参考链接

#figure(
  box(stroke: 0.5pt, inset: 8pt, radius: 4pt)[
    #image.decode(read("../../src/qr_cuhk_mordecai.svg", encoding: none), width: 15%, format: "svg")
  ],
  caption: [CUHK Winter School 2010]
)

#figure(
  box(stroke: 0.5pt, inset: 8pt, radius: 4pt)[
    #image.decode(read("../../src/qr_ust_golin_monge.svg", encoding: none), width: 15%, format: "svg")
  ],
  caption: [UST - Revisiting Monge]
)

=== 参考文献

#figure(
  box(stroke: 0.5pt, inset: 8pt, radius: 4pt)[
    #image.decode(read("../../src/qr_aggarwal1986.svg", encoding: none), width: 15%, format: "svg")
  ],
  caption: [Aggarwal et al., 1986]
)

#figure(
  box(stroke: 0.5pt, inset: 8pt, radius: 4pt)[
    #image.decode(read("../../src/qr_enwiki_1033199110.svg", encoding: none), width: 15%, format: "svg")
  ],
  caption: [Wikipedia - SMAWK algorithm]
)
