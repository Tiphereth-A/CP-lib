
区间修改,区间查询

#table(
  columns: 2,
  stroke: 0.5pt,
  align: (left, left),
  [代码], [备注],
  [`class T`], [维护的数据],
  [`T (*op)(T, T)`], [维护的操作],
  [`class F`], [修改的类型(会用于lazy标记)],
  [`void (*mapping)(T&, F) f(x)`], [即修改怎么应用于数据. 结果直接作用于第一个参数],
  [`void (*composition)(F&, F) f(g(x))`], [即修改的复合. 结果直接作用于第一个参数],
  [`T e`], [T的幺元],
  [`F id; id(x) = x`], [即恒等映射],
)

不需要lazy标记的时候用 `segtree_notag`, 此时 `T = F`, `mapping = composition` 且 `mapping(x,y)` 的效果应等价于 `x = op(x,y)`

=== 例子

另请参阅常用线段树构造

*维护*: 区间min; *操作*: 区间加

`T = {int _min}` 区间和, 长度

```cpp
op(T a, T b) -> T{min(a._min, b._min)}
F = {int add}
mapping(T& a, F f) -> a = T{a.s + f.add * a.l, a.l}
composition(F& f, F g) -> f = F{f.add + g.add}
e = T{INT_MAX}
id = F{0}
```

*维护*: 区间和; *操作*: 区间加,区间乘

`T = {mint s, l}` 区间和, 长度

```cpp
op(T a, T b) -> T{a.s + b.s, a.l + b.l}
F = {mint mul, add}
mapping(T& a, F f) -> a = T{a.s * f.mul + f.add * a.l, a.l}
composition(F& f, F g) -> f = F{f.mul * g.mul, f.mul * g.add + f.add};
// g(x) = g.mul * x + g.add
// f(g(x)) = f.mul * (g.mul * x + g.add) + f.add = f.mul * g.mul * x + f.mul * g.add + f.add
e = T{0, 0}
id = F{1, 0}
```
