// Fermat point using improved Weiszfeld algorithm - 使用改进的 Weiszfeld 算法求费马点

使用改进的 Weiszfeld 算法, 也可以使用模拟退火

=== Weiszfeld 算法

给定点集 $X := {x_1, dots, x_m}$, 设结果为 $y$, $tilde(T)(y) = (sum_(x_i != y) 1 / norm(y - x_i))^(-1) sum_(x_i != y) x_i / norm(y - x_i)$.

则 Weiszfeld 算法迭代格式为 $y arrow.l T_0(y) = cases(
  tilde(T)(y) "if" y in.not {x_1\, dots\, x_m},
  x_i "if" y = x_i
)$

=== 改进的 Weiszfeld 算法

令 $eta(y) = [y in {x_1, dots, x_m}]$, $r(y) = norm(sum_(x_i != y) (y - x_i) / norm(y - x_i))$.

则改进的 Weiszfeld 算法迭代格式为 $y arrow.l T(y) = (1 - eta(y) / r(y)) tilde(T)(y) + min{1, eta(y) / r(y)} y$.

当 $y in.not {x_1, dots, x_m}$ 时有 $T(y) = T_0(y) = tilde(T)(y)$

=== 参考文献

#figure(
  box(stroke: 0.5pt, inset: 8pt, radius: 4pt)[
    #image.decode(read("../../src/qr_katz1974.svg", encoding: none), width: 15%, format: "svg")
  ],
  caption: [Katz, 1974]
)

#figure(
  box(stroke: 0.5pt, inset: 8pt, radius: 4pt)[
    #image.decode(read("../../src/qr_brimberg1992.svg", encoding: none), width: 15%, format: "svg")
  ],
  caption: [Brimberg, 1992]
)

#figure(
  box(stroke: 0.5pt, inset: 8pt, radius: 4pt)[
    #image.decode(read("../../src/qr_vardi2000.svg", encoding: none), width: 15%, format: "svg")
  ],
  caption: [Vardi & Zhang, 2000]
)
