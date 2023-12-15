#ifndef TIFALIBS_MATH_SBT
#define TIFALIBS_MATH_SBT

#include "../util/abs_constexpr.hpp"
#include "../util/util.hpp"

namespace tifa_libs::math {

// x / y (x > 0, y > 0). default 1 / 1
template <class T>
class SBT {
  static_assert(std::is_integral_v<T> && std::is_signed_v<T>);

  T lx, ly, x, y, rx, ry;
  vec<T> seq;

 public:
  explicit constexpr SBT() : lx(0), ly(1), x(1), y(1), rx(1), ry(0) {}
  constexpr SBT(T X, T Y) : SBT() {
    assert(x > 0 && Y > 0);
    if (T g = std::gcd(X, Y); g > 1) X /= g, Y /= g;
    while (std::min(X, Y))
      if (X > Y) {
        T _ = X / Y;
        movr(_ - !(X -= _ * Y));
      } else {
        T _ = Y / X;
        movl(_ - !(Y -= _ * X));
      }
  }
  explicit constexpr SBT(vec<T> const &seq_) : SBT() {
    for (auto &&d : seq_) {
      assert(d != 0);
      if (d > 0) movr(d);
      if (d < 0) movl(d);
    }
  }

  friend constexpr bool operator<(SBT const &l, SBT const &r) { return l.x * r.y < r.x * l.y; }
  friend constexpr bool operator==(SBT const &l, SBT const &r) { return l.x == r.x && l.y == r.y; }

  constexpr ptt<T> current() const { return {x, y}; }
  constexpr ptt<T> lbound() const { return {lx, ly}; }
  constexpr ptt<T> rbound() const { return {rx, ry}; }
  // path from (1, 1) to @current(). rchild be positive and vice versa
  constexpr vec<T> path() const { return seq; }

  constexpr T dep() const {
    T res = 0;
    for (auto &&s : seq) res += abs(s);
    return res;
  }
  // move towards lchild with @d steps
  constexpr void movl(T d = 1) {
    if (d <= 0) return;
    if (seq.empty() || seq.back() > 0) seq.push_back(0);
    seq.back() -= d;
    rx += lx * d, ry += ly * d;
    x = rx + lx, y = ry + ly;
  }
  // move towards rchild with @d steps
  constexpr void movr(T d = 1) {
    if (d <= 0) return;
    if (seq.empty() || seq.back() < 0) seq.push_back(0);
    seq.back() += d;
    lx += rx * d, ly += ry * d;
    x = rx + lx, y = ry + ly;
  }
  // move towards fa with @d steps
  // @return true if succeed, or false if falied
  constexpr bool movf(T d = 1) {
    if (d <= 0) return true;
    while (d) {
      if (seq.empty()) return false;
      T _ = std::min(d, abs(seq.back()));
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

  static constexpr SBT lca(SBT const &l, SBT const &r) {
    SBT ret;
    for (u32 i = 0; i < std::min((u32)l.seq.size(), (u32)r.seq.size()); ++i) {
      T val1 = l.seq[i], val2 = r.seq[i];
      if ((val1 < 0) != (val2 < 0)) break;
      if (val1 < 0) ret.movl(std::min(-val1, -val2));
      if (val1 > 0) ret.movr(std::min(val1, val2));
      if (val1 != val2) break;
    }
    return ret;
  }
};

}  // namespace tifa_libs::math

#endif