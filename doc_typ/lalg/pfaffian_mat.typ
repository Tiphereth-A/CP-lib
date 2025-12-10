
对长度为 $2n$ 的排列 $pi$, 若

- $forall 1 <= i <= n, space pi_(2i-1) < pi_(2i)$
- $forall 1 <= i < n, space pi_(2i-1) < pi_(2i+1)$

则称 $pi$ 为完美匹配. 对 $2n times 2n$ 的反对称矩阵 $A$, 其 Pfaffian $op("pf")(A)$ 定义为 $op("pf")(A) := 1 / (n! 2^n) sum_(pi in frak(M)_(2n)) op("sgn")(pi) product_(i=1)^n a_(pi(2j-1), pi(2j))$

其中 $frak(M)_(2n)$ 为全体长度为 $2n$ 的完美匹配构成的集合. $op("sgn")(pi)$ 为排列 $pi$ 逆序对数的奇偶性, 奇数为 $-1$, 偶数为 $1$

=== 性质

若以 $A$ 为邻接矩阵的有向图为平面图, 则 $op("pf")(A)$ 为该图的完美匹配数量 (FKT 算法)

类似行列式,

- 对一行和一列乘同一个常数, Pfaffian 也会乘相同的常数
- 同时互换两个不同的行和相应的列会改变 Pfaffian 的符号
- 一行和相应列的倍数与另一行和相应列相加不会改变 Pfaffian

另外,

- $op("pf")(A^T) = (-1)^n op("pf")(A)$
- $op("pf")(lambda A) = lambda^n op("pf")(A)$
- $op("pf")(A)^2 = det(A)$
- 对 $2n times 2n$ 的反对称矩阵 $B$, $op("pf")(B A B^T) = det(B) op("pf")(A)$
- 对非负整数 $m$, $op("pf")(A^(2m+1)) = (-1)^(n m) op("pf")(A)^(2m+1)$

和矩阵的 Hafnian 的关系相当于行列式与积和式的关系

=== 输入

`mat`: $2n times 2n$ 反对称矩阵的 *上三角矩阵*

=== 输出

`mat` 的 Pfaffian

=== 复杂度

$O(n^3)$

=== 参考资料

#figure(
  box(stroke: 0.5pt, inset: 8pt, radius: 4pt)[
    #image.decode(read("../../src/qr_enwiki_1229899175.svg", encoding: none), width: 15%, format: "svg")
  ],
  caption: [Wikipedia - Pfaffian]
)

#figure(
  box(stroke: 0.5pt, inset: 8pt, radius: 4pt)[
    #image.decode(read("../../src/qr_enwiki_1216412359.svg", encoding: none), width: 15%, format: "svg")
  ],
  caption: [Wikipedia - FKT algorithm]
)
