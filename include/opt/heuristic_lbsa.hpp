#ifndef TIFALIBS_OPT_HEURISTIC_LBSA
#define TIFALIBS_OPT_HEURISTIC_LBSA

#include "../rand/gen.hpp"
#include "../util/alias_others.hpp"

namespace tifa_libs::opt {

template <class Cont, class Ff, class Ft = f64, class Tt = f64>
requires requires(Ff f, cT_(Cont) t) {
  { f(t) } -> std::same_as<Ft>;
}
class heuristic_lbsa {
  Ff f;
  rand::gen<u32> g_idx;
  rand::gen<Tt> g;
  Cont x;
  Ft fx;
  pq<Tt> tlist;

 public:
  // Find minimum argument of f(x)
  CEXP heuristic_lbsa(Ff f, cT_(Cont) init, u32 L, Tt p0 = .2) NE : f(f), g_idx(0, (u32)init.size() - 1), g(0, 1), x(init), fx(f(init)), tlist() {
    const Tt lp0 = std::log(p0);
    while (tlist.size() < L)
      if (auto [fy, y] = gen(); fy < fx) swap(fx, fy), swap(x, y);
      else tlist.push((fx - fy) / lp0);
  }

  std::pair<Ft, Cont> operator()(u32 K, u32 M) NE {
    flt_ (u32, k, 0, K) {
      Tt tmax = tlist.top(), t = 0;
      u32 c = 0;
      flt_ (u32, m, 0, M)
        if (auto [fy, y] = gen(); fy < fx) swap(fx, fy), swap(x, y);
        else if (Tt r = g.next(); std::exp((fx - fy) / tmax) > r) t += (fx - fy) / std::log(r), ++c;
      if (c) tlist.pop(), tlist.push(t / c);
    }
    return {fx, x};
  }

 private:
  static CEXP void inv_(TPN Cont::iterator l, TPN Cont::iterator r) NE { reverse(l, std::next(r)); }
  static CEXP void ins_(TPN Cont::iterator l, TPN Cont::iterator r) NE {
    auto x = *r;
    move_backward(l, r, std::next(r)), *l = x;
  }
  static CEXP void swap_(TPN Cont::iterator l, TPN Cont::iterator r) NE { std::iter_swap(l, r); }
  std::pair<Ft, Cont> gen() NE {
    u32 l = g_idx(), r = g_idx();
    while (l == r) r = g_idx();
    if (l > r) swap(l, r);
    Cont c0 = x, c1 = x, c2 = x;
    inv_(begin(c0) + l, begin(c0) + r);
    ins_(begin(c1) + l, begin(c1) + r);
    swap_(begin(c2) + l, begin(c2) + r);
    Ft f0 = f(c0), f1 = f(c1), f2 = f(c2);
    if (f0 > f1) swap(f0, f1), swap(c0, c1);
    if (f0 > f2) swap(f0, f2), swap(c0, c2);
    return {f0, c0};
  }
};

}  // namespace tifa_libs::opt

#endif