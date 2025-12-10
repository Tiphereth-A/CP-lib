
- *团数*: 最大团的点数, 记为 $omega(G)$
- *色数*: 最小点染色的颜色数, 记为 $chi(G)$

  显然 $omega(G) <= chi(G)$

- *最大独立集*: 最大的点集使得点集中任意两点都没有边直接相连. 该集合的大小记为 $alpha(G)$
- *最小团覆盖*: 用最少的团覆盖所有的点. 使用团的数量记为 $kappa(G)$

  显然 $alpha(G) <= kappa(G)$

- *弦*: 连接环中不相邻两点的边
- *弦图*: 任意长度大于 $3$ 的环都有一个弦的图
- *单纯点*: 设 $N(x)$ 表示与点 $x$ 相邻的点集, 若 ${x} union N(x)$ 的导出子图是团, 则称点 $x$ 为单纯点
- *完美消除序列(PEO)*: 令 $n=|V|$, 完美消除序列 $v_1, dots, v_n$ 为 $1, dots, n$ 的排列, $v_i$ 在 ${v_i, dots, v_n}$ 的导出子图中为单纯点

#figure(
  image("../../img/Chordal-graph.svg", width: 40%),
  caption: [有两条弦的环(From Wikipedia)]
) <img:c5-with-2-chords>

=== 性质

- 弦图的任意导出子图一定是弦图
- 弦图的任意导出子图一定不可能是一个点数大于 $3$ 的环
- 弦图上任意两点间的极小点割集的导出子图一定为一个团
- 任何一个弦图都至少有一个单纯点, 不是完全图的弦图至少有两个不相邻的单纯点
- 一个无向图是弦图当且仅当其有一个完美消除序列
- 弦图的 $omega(G) = chi(G) = max_(v in V(G)) {|N(v)| + 1}$
- 弦图的 $alpha(G) = kappa(G)$
- 设弦图的最大独立集为 ${v_1, dots, v_t}$, 则 ${{v_1 + N(v_1)}, dots, {v_t + N(v_t)}}$ 为其最小团覆盖

弦图判定: 用最大势算法 (Maximum Cardinality Search) 得到一个序列, 若该序列为 PEO 则图为弦图

弦图的最大独立集找法为: PEO 从前往后, 选择所有没有与已经选择的点有直接连边的点

=== 树分解

对图 $G=(V,E)$, 其树分解 (tree decompositions, junction trees, clique trees, join trees) 定义为 $(X,T)$, 其中 $X={X_1, dots, X_n}$ 为一族 $V$ 的子集, 称为 bags, $T$ 为以 $X$ 为点集的树, 满足:

+ $union.big_(x in X) x = V$.
+ $forall (v, w) in E$, $exists X_i in X$ s.t. $v, w in X_i$.
+ 若 $X_k$ 在 $X_i$ 到 $X_j$ 的路径上, 则 $X_i sect X_j subset.eq X_k$.

#figure(
  image("../../img/Tree_decomposition.svg", width: 40%),
  caption: [树分解(From Wikipedia)]
) <img:tree-decomposition>

=== 复杂度

- MCS, 弦图判定: $O(n+m)$
- 求弦图极大团: $O(n+m)$
- 求弦图色数/团数: $O(n)$
- 求弦图最大独立集/最小团覆盖: $O(n+m)$

=== 参考资料

#figure(
  box(stroke: 0.5pt, inset: 8pt, radius: 4pt)[
    #image.decode(read("../../src/qr_enwiki_1204698483.svg", encoding: none), width: 15%, format: "svg")
  ],
  caption: [Wikipedia - Chordal graph]
)

#figure(
  box(stroke: 0.5pt, inset: 8pt, radius: 4pt)[
    #image.decode(read("../../src/qr_enwiki_1217459734.svg", encoding: none), width: 15%, format: "svg")
  ],
  caption: [Wikipedia - Tree decomposition]
)
