#ifndef TIFALIBS_OPT_KNAPSACK_MIXED
#define TIFALIBS_OPT_KNAPSACK_MIXED

#include "../util/util.hpp"

namespace tifa_libs::opt {

template <class T>
class knapsack_mixed {
  vec<T> f;

 public:
  CEXPE knapsack_mixed(u32 max_weight) NE : f(max_weight + 1) {}
  // count = 0 -> inf
  CEXP void add(u32 weight, T value, u32 count = 1) NE {
    if (const u32 M = (u32)f.size() - 1; !count)
      flt_ (u32, i, weight, M + 1) f[i] = max(f[i], f[i - weight] + value);
    else
      flt_ (u32, w, 0, weight) {
        vec<T> q1, q2;
        u32 l = 0;
        flt_ (u32, i, 0, (M - w) / weight + 1) {
          T &x = f[w + weight * i];
          while (l < q1.size() && (T)x - value * (T)i >= q2.back()) q1.pop_back(), q2.pop_back();
          q1.push_back((T)i), q2.push_back((T)x - value * (T)i);
          while (l < q1.size() && q1[l] < T(i - count)) ++l;
          x = max(x, q2[l] + value * (T)i);
        }
      }
  }
  vec<T> CR result() CNE { return f; }
};

}  // namespace tifa_libs::opt

#endif