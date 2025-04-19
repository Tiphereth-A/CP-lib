#ifndef TIFALIBS_DS_DSU_WEIGHTED
#define TIFALIBS_DS_DSU_WEIGHTED

#include "../util/alias_others.hpp"

namespace tifa_libs::ds {

//! T should be a group with op and inv
template <class T = i64, auto op = std::plus<>{}, auto inv = std::negate<>{}>
requires requires(T x, T y) {
  { op(x, y) } -> std::same_as<T>;
  { inv(x) } -> std::same_as<T>;
}
class dsu_weighted {
  const T E;
  veci p;
  vec<T> val;  // $a_{root}^{-1}a_i$

 public:
  CEXPE dsu_weighted(u32 n, cT_(T) E = T{}) NE : E{E}, p(n, -1), val(n, E) {}

  CEXP i32 find(u32 x) NE {
    if (p[x] < 0) return (i32)x;
    const auto _ = find((u32)p[x]);
    val[x] = op(val[(u32)p[x]], val[x]), p[x] = _;
    return _;
  }
  CEXP u32 size() CNE { return (u32)p.size(); }
  CEXP u32 size(u32 x) NE { return (u32)-p[(u32)find(x)]; }
  CEXP T CR weight(u32 x) NE {
    find(x);
    return val[x];
  }
  // $a_y^{-1}a_x$
  CEXP T diff(u32 x, u32 y) NE { return op(inv(weight(y)), weight(x)); }
  CEXP bool same(u32 x, u32 y) NE { return find(x) == find(y); }
  CEXP bool merge(u32 x, u32 y, T w) NE {
    w = op(weight(x), inv(op(weight(y), w)));
    if ((x = (u32)find(x)) == (y = (u32)find(y))) return w == E;
    if (p[x] > p[y]) swap(x, y), w = inv(w);
    p[x] += p[y], p[y] = (i32)x, val[y] = w;
    return true;
  }
};

}  // namespace tifa_libs::ds

#endif