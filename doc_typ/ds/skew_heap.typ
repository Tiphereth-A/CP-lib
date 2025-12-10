// Skew heap - 斜堆

和左偏树相比, 斜堆支持 $O(1)$ 插入

可用 Brodal (1996) 中提到的方法将合并的复杂度降至 $O(1)$

=== 参考文献

#figure(
  box(stroke: 0.5pt, inset: 8pt, radius: 4pt)[
    #image.decode(read("../../src/qr_brodal1996.svg", encoding: none), width: 15%, format: "svg")
  ],
  caption: [Brodal, 1996]
)
