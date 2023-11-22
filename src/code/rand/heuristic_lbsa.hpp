#ifndef TIFA_LIBS_UTIL_HEURISTIC_LBSA
#define TIFA_LIBS_UTIL_HEURISTIC_LBSA

#include "gen.hpp"

namespace tifa_libs::rand {

// Ff: Ft(T const &)
template <class Cont, class Ff, class Ft = f64, class Tt = f64>
class heuristic_lbsa {
  Ff f;
  Gen<std::uniform_int_distribution<u32>> g_idx;
  Gen<std::uniform_real_distribution<Tt>> g;
  Cont x;
  Ff fx;
  pq<Tt> tlist;

 public:
  // Find minimum argument of f(x)
  explicit heuristic_lbsa(Ff f, Cont x, u32 L, Tt p0 = .2) : f(f), g_idx(0, x.size() - 1), g(0, 1), x(x), fx(f(x)), tlist() {
    const Tt lp0 = std::log(p0);
    while (tlist.size() < L) {
      auto [fy, y] = gen(x);
      if (fy < fx) std::swap(fx, fy), std::swap(x, y);
      else tlist.push((fx - fy) / lp0);
    }
  }

  std::pair<Ft, Cont> operator()(u32 K, u32 M) {
    for (u32 k = 0; k < K; ++k) {
      Tt tmax = tlist.top(), t = 0;
      u32 c = 0;
      for (u32 m = 0; m < M; ++m) {
        auto [fy, y] = gen();
        if (fy < fx) std::swap(fx, fy), std::swap(x, y);
        else if (Tt r = g(); std::exp((fx - fy) / tmax) > r) t = (t - fy + fx) / std::log(r), ++c;
      }
      if (c) tlist.pop(), tlist.push(t / c);
    }
    return {fx, x};
  }

 private:
  static void inv_(typename Cont::iterator l, typename Cont::iterator r) { std::reverse(l, r); }
  static void ins_(typename Cont::iterator l, typename Cont::iterator r) {
    auto x = *r;
    std::move_backward(l, std::prev(r), r);
    *l = x;
  }
  static void swap_(typename Cont::iterator l, typename Cont::iterator r) { std::iter_swap(l, r); }
  std::pair<Ft, Cont> gen() {
    u32 l = g_idx(), r = g_idx();
    while (l == r || l + 1 == r || l == r + 1) r = g_idx();
    if (l > r) std::swap(l, r);
    Cont c0 = inv_(x.begin() + l, x.begin() + r),
         c1 = ins_(x.begin() + l, x.begin() + r),
         c2 = swap_(x.begin() + l, x.begin() + r);
    Ft f0 = f(c0), f1 = f(c1), f2 = f(c2);
    if (f0 > f1) std::swap(f0, f1), std::swap(c0, c1);
    if (f0 > f2) std::swap(f0, f2), std::swap(c0, c2);
    return {f0, c0};
  }
};

}  // namespace tifa_libs::rand

#endif