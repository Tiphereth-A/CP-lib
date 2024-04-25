#ifndef TIFALIBS_MATH_SBT
#define TIFALIBS_MATH_SBT

#include "../nt/gcd.hpp"

namespace tifa_libs::math {

// x / y (x > 0, y > 0). default 1 / 1
template <std::signed_integral T>
class SBT {
  T lx, ly, x, y, rx, ry;
  vec<T> seq;

 public:
  explicit CEXP SBT() : lx(0), ly(1), x(1), y(1), rx(1), ry(0) {}
  CEXP SBT(T X, T Y) : SBT() {
    assert(x > 0 && Y > 0);
    if (T g = gcd(X, Y); g > 1) X /= g, Y /= g;
    while (min(X, Y))
      if (X > Y) {
        T _ = X / Y;
        movr(_ - !(X -= _ * Y));
      } else {
        T _ = Y / X;
        movl(_ - !(Y -= _ * X));
      }
  }
  explicit CEXP SBT(vec<T> CR seq_) : SBT() {
    for (auto &&d : seq_) {
      assert(d != 0);
      if (d > 0) movr(d);
      if (d < 0) movl(d);
    }
  }

  friend CEXP auto operator<=>(SBT CR l, SBT CR r) { return l.x * r.y - r.x * l.y; }
  friend CEXP bool operator==(SBT CR l, SBT CR r) { return l.x == r.x && l.y == r.y; }

  CEXP ptt<T> current() const { return {x, y}; }
  CEXP ptt<T> lbound() const { return {lx, ly}; }
  CEXP ptt<T> rbound() const { return {rx, ry}; }
  // path from (1, 1) to @current(). rchild be positive and vice versa
  CEXP vec<T> path() const { return seq; }

  CEXP T dep() const {
    T res = 0;
    for (auto &&s : seq) res += abs(s);
    return res;
  }
  // move towards lchild with @d steps
  CEXP void movl(T d = 1) {
    if (d <= 0) return;
    if (seq.empty() || seq.back() > 0) seq.push_back(0);
    seq.back() -= d;
    rx += lx * d, ry += ly * d;
    x = rx + lx, y = ry + ly;
  }
  // move towards rchild with @d steps
  CEXP void movr(T d = 1) {
    if (d <= 0) return;
    if (seq.empty() || seq.back() < 0) seq.push_back(0);
    seq.back() += d;
    lx += rx * d, ly += ry * d;
    x = rx + lx, y = ry + ly;
  }
  // move towards fa with @d steps
  // @return true if succeed, or false if falied
  CEXP bool movf(T d = 1) {
    if (d <= 0) return true;
    while (d) {
      if (seq.empty()) return false;
      T _ = min(d, abs(seq.back()));
      if (seq.back() > 0) {
        x -= rx * _, y -= ry * _;
        lx = x - rx, ly = y - ry;
        seq.back() -= _;
      } else {
        x -= lx * _, y -= ly * _;
        rx = x - lx, ry = y - ly;
        seq.back() += _;
      }
      d -= _;
      if (!seq.back()) seq.pop_back();
      if (!_) break;
    }
    return true;
  }

  static CEXP SBT lca(SBT CR l, SBT CR r) {
    SBT ret;
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