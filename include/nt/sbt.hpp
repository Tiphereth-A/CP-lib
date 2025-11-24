#ifndef TIFALIBS_MATH_SBT
#define TIFALIBS_MATH_SBT

#include "../util/consts.hpp"
#include "../util/traits_math.hpp"

namespace tifa_libs::math {

template <uint_c T>
struct sbt {
  T x{1}, y{1};    // now
  T lx{0}, ly{1};  // lbound
  T rx{1}, ry{0};  // rbound

  CEXP sbt() NE = default;

  CEXP void movl(int_c auto step = 1) NE {
    using W = std::conditional_t<sint_c<decltype(step)>, to_sint_t<decltype(step * x)>, decltype(step * x)>;
    rx += T((W)lx * step), ry += T((W)ly * step), x = rx + lx, y = ry + ly;
  }
  CEXP void movr(int_c auto step = 1) NE {
    using W = std::conditional_t<sint_c<decltype(step)>, to_sint_t<decltype(step * x)>, decltype(step * x)>;
    lx += T((W)rx * step), ly += T((W)ry * step), x = rx + lx, y = ry + ly;
  }

  // dir: true -> move to rchild; false -> move to lchil
  template <class F>
  requires requires(F f, bool dir, T step) { f(dir, step); }
  static CEXP sbt walk_to(T x, T y, F&& f) NE {
    sbt sbt;
    bool dir = false;
    while (y) {
      T step = x / y;
      if (dir = !dir, std::swap(x %= y, y); !y) --step;
      if (!step) continue;
      if (f(dir, step); dir) sbt.movr(step);
      else sbt.movl(step);
    }
    return sbt;
  }
  static CEXP sbt walk_to(T x, T y) NE { return walk_to(x, y, fn_0); }
  // dir: true -> move to rchild; false -> move to lchil
  template <class F>
  requires requires(F f, bool dir, T step) { f(dir, step); }
  static CEXP sbt walk_to_lca(T x1, T y1, T x2, T y2, F&& f) NE {
    sbt sbt;
    bool dir = false;
    while (y1 && y2) {
      T step1 = x1 / y1, step2 = x2 / y2;
      if (dir = !dir, std::swap(x1 %= y1, y1); !y1) --step1;
      if (std::swap(x2 %= y2, y2); !y2) --step2;
      if (T step = min(step1, step2); step) {
        if (f(dir, step); dir) sbt.movr(step);
        else sbt.movl(step);
      }
      if (step1 != step2) break;
    }
    return sbt;
  }
  static CEXP sbt walk_to_lca(T x1, T y1, T x2, T y2) NE { return walk_to_lca(x1, y1, x2, y2, fn_0); }
};

}  // namespace tifa_libs::math

#endif