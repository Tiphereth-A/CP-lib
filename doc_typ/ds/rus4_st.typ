
设 $n$ 为数组长度, $b$ 为块长 (常取 $O(log n)$), 则

=== 时间复杂度

$O((n+b) log b)$ 预处理, $O(1)$ 查询

=== 空间复杂度

$O((n+b) log b)$

=== 参考文献

#figure(
  box(stroke: 0.5pt, inset: 8pt, radius: 4pt)[
    #image.decode(read("../../src/qr_arlazarov1970.svg", encoding: none), width: 15%, format: "svg")
  ],
  caption: [Arlazarov et al., 1970]
)

#figure(
  box(stroke: 0.5pt, inset: 8pt, radius: 4pt)[
    #image.decode(read("../../src/qr_aho1974.svg", encoding: none), width: 15%, format: "svg")
  ],
  caption: [Aho et al., 1974]
)
