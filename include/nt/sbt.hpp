#ifndef TIFALIBS_MATH_SBT
#define TIFALIBS_MATH_SBT

#include "../nt/gcd.hpp"
#include "../util/alias_others.hpp"

namespace tifa_libs::math {

// x / y (x > 0, y > 0). default 1 / 1
template <std::signed_integral T>
class sbt {
  T lx, ly, x, y, rx, ry;
  vec<T> seq;

 public:
  CEXP sbt() NE : lx{0}, ly{1}, x{1}, y{1}, rx{1}, ry{0} {}
  CEXPE sbt(spn<T> seq_) NE : sbt() {
    for (auto d : seq_) {
      if (assert(d != 0); d > 0) movr(d);
      if (d < 0) movl(d);
    }
  }
  CEXP sbt(T x_, T y_) NE : sbt() {
    assert(x_ > 0 && y_ > 0);
    if (T g = gcd(x_, y_); g > 1) x_ /= g, y_ /= g;
    while (min(x_, y_))
      if (x_ > y_) {
        const T _ = x_ / y_;
        movr(_ - !(x_ -= _ * y_));
      } else {
        const T _ = y_ / x_;
        movl(_ - !(y_ -= _ * x_));
      }
  }

  friend CEXP auto operator<=>(sbt CR l, sbt CR r) NE { return l.x * r.y - r.x * l.y; }
  friend CEXP bool operator==(sbt CR l, sbt CR r) NE { return l.x == r.x && l.y == r.y; }
  CEXP ptt<T> current() CNE { return {x, y}; }
  CEXP ptt<T> lbound() CNE { return {lx, ly}; }
  CEXP ptt<T> rbound() CNE { return {rx, ry}; }
  // path from (1, 1) to @current(). rchild be positive and vice versa
  CEXP vec<T> path() CNE { return seq; }
  CEXP T dep() CNE {
    T res = 0;
    for (auto &&s : seq) res += abs(s);
    return res;
  }
  // move towards lchild with @d steps
  CEXP void movl(T d = 1) NE {
    if (d <= 0) return;
    if (seq.empty() || seq.back() > 0) seq.push_back(0);
    seq.back() -= d, rx += lx * d, ry += ly * d, x = rx + lx, y = ry + ly;
  }
  // move towards rchild with @d steps
  CEXP void movr(T d = 1) NE {
    if (d <= 0) return;
    if (seq.empty() || seq.back() < 0) seq.push_back(0);
    seq.back() += d, lx += rx * d, ly += ry * d, x = rx + lx, y = ry + ly;
  }
  // move towards fa with @d steps
  // @return true if succeed, or false if falied
  CEXP bool movf(T d = 1) NE {
    retif_((d <= 0) [[unlikely]], true);
    while (d) {
      if (seq.empty()) return false;
      T _ = min(d, abs(seq.back()));
      if (seq.back() > 0) x -= rx * _, y -= ry * _, lx = x - rx, ly = y - ry, seq.back() -= _;
      else x -= lx * _, y -= ly * _, rx = x - lx, ry = y - ly, seq.back() += _;
      if (d -= _; !seq.back()) seq.pop_back();
      if (!_) break;
    }
    return true;
  }
  static CEXP sbt lca(sbt CR l, sbt CR r) NE {
    sbt ret;
    for (u32 i = 0; i < min((u32)l.seq.size(), (u32)r.seq.size()); ++i) {
      T val1 = l.seq[i], val2 = r.seq[i];
      if ((val1 < 0) != (val2 < 0)) break;
      if (val1 < 0) ret.movl(min(-val1, -val2));
      if (val1 > 0) ret.movr(min(val1, val2));
      if (val1 != val2) break;
    }
    return ret;
  }
};

}  // namespace tifa_libs::math

#endif