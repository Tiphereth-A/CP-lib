
应用了 BFS 优化与 GAP 优化

#figure(
  image("../../img/hlpp.png", width: 100%),
  caption: [运行示例 (From OI-Wiki)]
) <img:hlpp>

其中 pic13 到 pic14 执行了 Relabel(4), 并进行了 GAP 优化

=== 复杂度

$O(|V|^2 sqrt(|E|))$

=== 参考资料

#figure(
  box(stroke: 0.5pt, inset: 8pt, radius: 4pt)[
    #image.decode(read("../../src/qr_oiwiki.svg", encoding: none), width: 15%, format: "svg")
  ],
  caption: [OI-Wiki]
)

#figure(
  box(stroke: 0.5pt, inset: 8pt, radius: 4pt)[
    #image.decode(read("../../src/qr_ahuja1997computational.svg", encoding: none), width: 15%, format: "svg")
  ],
  caption: [Ahuja et al., 1997]
)
