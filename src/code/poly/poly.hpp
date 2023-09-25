#ifndef TIFALIBS_POLY_POLY
#define TIFALIBS_POLY_POLY

#include "../math/inverse.hpp"
#include "../math/proot_u32.hpp"
#include "../math/qpow_mod.hpp"
#include "../math/qresidue.hpp"
#include "../util/util.hpp"

namespace tifa_libs::poly {
namespace detail__ {

using namespace ::tifa_libs::math;

struct FFT_INFO_ {
  static inline vec<size_t> root;

  static void init(size_t n) {
    assert((n & (n - 1)) == 0);
    if (root.size() == n) return;
    root.resize(n);
    for (size_t i = 0; i < n; ++i) root[i] = (root[i >> 1] >> 1) | ((i & 1) * (n >> 1));
  }
};

template <u32 MOD>
struct NTT_ {
  constexpr NTT_() = default;
  constexpr void operator()(vec<u32> &g, bool inv = false) {
    size_t n = g.size();
    FFT_INFO_::init(n);
    f.resize(n);
    w.resize(n);
    w[0] = 1;
    for (size_t i = 0; i < n; ++i) f[i] = (((u64)MOD << 5) + g[FFT_INFO_::root[i]]) % MOD;
    for (size_t l = 1; l < n; l <<= 1) {
      u64 tG = qpow_mod(inv ? IG : G, (MOD - 1) / (l + l), MOD);
      for (size_t i = 1; i < l; ++i) w[i] = w[i - 1] * tG % MOD;
      for (size_t k = 0; k < n; k += l + l)
        for (size_t p = 0; p < l; ++p) {
          u32 _ = (u32)(w[p] * f[k | l | p] % MOD);
          f[k | l | p] = f[k | p] + (MOD - _);
          f[k | p] += _;
        }
      if (l == (1 << 10))
        for (size_t i = 0; i < n; ++i) f[i] %= MOD;
    }
    if (inv) {
      u64 in = inverse((u32)n, MOD);
      for (size_t i = 0; i < n; ++i) g[i] = (i32)(f[i] % MOD * in % MOD);
    } else
      for (size_t i = 0; i < n; ++i) g[i] = (i32)(f[i] % MOD);
  }

private:
  constexpr static u32 G = proot_u32(MOD), IG = inverse(G, MOD);

  static inline vec<u64> f, w;
};

template <class DBL>
struct FFT_ {
  static_assert(std::is_floating_point_v<DBL>);

  using comp = std::complex<DBL>;

  constexpr FFT_() = default;
  constexpr void operator()(vec<comp> &g, bool inv = false) {
    size_t n = g.size();
    FFT_INFO_::init(n);
    w.resize(n);
    w[0] = 1;
    for (size_t i = 1; i < n; ++i) w[i] = {std::cos(TAU * (DBL)i / (DBL)n), (inv ? -1 : 1) * std::sin(TAU * (DBL)i / (DBL)n)};
    for (size_t i = 0; i < n; ++i)
      if (i < FFT_INFO_::root[i]) std::swap(g[i], g[FFT_INFO_::root[i]]);
    for (size_t i = 2; i <= n; i <<= 1) {
      for (size_t j = 1; j < i / 2; ++j) w[j] = {std::cos(TAU / (DBL)i * (DBL)j), (inv ? -1 : 1) * std::sin(TAU / (DBL)i * (DBL)j)};
      for (size_t j = 0; j < n; j += i) {
        auto f = g.begin() + j, h = g.begin() + j + i / 2;
        for (size_t k = 0; k < i / 2; ++k) {
          comp p = f[k], q = h[k] * w[k];
          f[k] = p + q;
          h[k] = p - q;
        }
      }
    }
  }

private:
  constexpr static DBL TAU = DBL(std::acos((DBL)1) * 2);

  static inline vec<comp> w;
};

struct PolyBase__ {
  static vec<u32> naive_conv(vec<u32> const &lhs, vec<u32> const &rhs, u32 mod) {
    size_t n = lhs.size(), m = rhs.size();
    vec<u32> ans(n + m - 1);
    if (n < m)
      for (size_t j = 0; j < m; j++)
        for (size_t i = 0; i < n; i++) ans[i + j] = (u32)((ans[i + j] + (u64)lhs[i] * rhs[j]) % mod);
    else
      for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++) ans[i + j] = (u32)((ans[i + j] + (u64)lhs[i] * rhs[j]) % mod);
    return ans;
  }
};
template <u32 MOD>
struct SmodPolyBase_: public PolyBase__ {
  static_assert((MOD & 3) == 1, "MOD must be prime with 4k+1");

  using self = SmodPolyBase_<MOD>;

  static inline NTT_<MOD> ntt;

  vec<u32> data;

  explicit constexpr SmodPolyBase_(size_t sz = 1):
    data(std::max((size_t)1, sz)) {}
  explicit constexpr SmodPolyBase_(std::initializer_list<u32> v):
    data(v) {}
  explicit constexpr SmodPolyBase_(vec<u32> const &v):
    data(v) {}

  constexpr static u32 mod() { return MOD; }

#define OOCR_(op, ...)                                          \
  self &operator op##=(self const &rhs) __VA_ARGS__ friend self \
  operator op(self lhs, self const &rhs) { return lhs op## = rhs; }

  OOCR_(*, {
    if (data.size() + rhs.data.size() < 64) {
      data = naive_conv(data, rhs.data, MOD);
      return *this;
    }
    vec<u32> a__(data), b__(rhs.data);
    data.resize(data.size() + rhs.data.size() - 1);
    size_t n = (size_t)(1) << (size_t)std::max(1., std::ceil(std::log2(data.size())));
    a__.resize(n);
    b__.resize(n);
    ntt(a__);
    ntt(b__);
    for (size_t i = 0; i < n; ++i) a__[i] = (u32)((u64)a__[i] * b__[i] % MOD);
    ntt(a__, true);
    a__.resize(data.size());
    data = a__;
    return *this;
  })

#undef OOCR_
};
template <ptrdiff_t ID, class DBL>
struct DmodPolyBase_: public PolyBase__ {
  using self = DmodPolyBase_<ID, DBL>;

  static inline u32 mod_;
  static u32 mod() { return mod_; }
  static void set_mod(u32 m) {
    assert(1 <= m);
    mod_ = m;
  }

  static inline FFT_<DBL> fft;
  using comp = typename decltype(fft)::comp;

  vec<u32> data;

  explicit DmodPolyBase_(size_t sz = 1):
    data(std::max((size_t)1, sz)) { assert(1 <= mod_); }
  explicit DmodPolyBase_(std::initializer_list<u32> v):
    data(v) { assert(1 <= mod_); }
  explicit DmodPolyBase_(vec<u32> const &v):
    data(v) { assert(1 <= mod_); }

#define OOCR_(op, ...) \
  self &operator op##=(self const &rhs) __VA_ARGS__ friend self operator op(self lhs, self const &rhs) { return lhs op## = rhs; }

  OOCR_(*, {
    if (data.size() + rhs.data.size() < 64) {
      data = naive_conv(data, rhs.data, mod());
      return *this;
    }
    vec<comp> a__(data.size()), b__(rhs.data.size());
    for (size_t i = 0; i < data.size(); ++i) a__[i].real(data[i] & 0x7fff), a__[i].imag(data[i] >> 15);
    for (size_t i = 0; i < rhs.data.size(); ++i) b__[i].real(rhs.data[i] & 0x7fff), b__[i].imag(rhs.data[i] >> 15);
    data.resize(data.size() + rhs.data.size() - 1);
    size_t n = (size_t)(1) << (size_t)std::max(1., std::ceil(std::log2(data.size())));
    a__.resize(n);
    b__.resize(n);
    fft(a__);
    fft(b__);
    vec<comp> p__(n), q__(n);
    for (size_t i = 0; i < n; ++i) p__[i] = b__[i] * (a__[i] + conj(a__[(n - i) % n])) * comp{.5, 0};
    for (size_t i = 0; i < n; ++i) q__[i] = b__[i] * (a__[i] - conj(a__[(n - i) % n])) * comp{0, -.5};
    fft(p__, true);
    fft(q__, true);
    for (size_t i = 0; i < data.size(); ++i) data[i] = (u32)(((u64)(p__[i].real() / (double)n + .5) % mod() + (((u64)((p__[i].imag() + q__[i].real()) / (double)n + .5) % mod()) << 15) + (((u64)(q__[i].imag() / (double)n + .5) % mod()) << 30)) % mod());
    return *this;
  })

#undef OOCR_
};

template <class PBase>
class Poly {
  static_assert(std::is_base_of_v<PolyBase__, PBase>);

  PBase p;

  template <class Fodd, class Feven>
  constexpr void expand_base__(
    Poly &ans, size_t n, u32 val1, Fodd fodd, Feven feven) const {
    if (n == 1) {
      ans.p.data[0] = val1;
      return;
    }
    if (n & 1) {
      expand_base__(ans, n - 1, val1, fodd, feven);
      fodd(ans, n);
      return;
    }
    expand_base__(ans, n / 2, val1, fodd, feven);
    feven(ans, n);
  }

  constexpr void inv_(Poly &ans, size_t n) const {
    expand_base__(
      ans,
      n,
      (u32)inverse(p.data[0], p.mod()),
      [this](Poly &ans, size_t n) -> void {
        --n;
        u64 _ = 0;
        for (size_t i = 0; i < n; ++i) _ = (_ + (u64)ans[i] * p.data[n - i]) % p.mod();
        ans.p.data.push_back((u32)(_ * inverse(p.mod() - p.data[0], p.mod()) % p.mod()));
      },
      [this](Poly &ans, size_t n) -> void {
        Poly sA = *this;
        sA.do_resize(n);
        ans = ans * 2 - (ans * ans * sA).do_resize(n);
      });
  }

  constexpr void exp_(Poly &ans, size_t n) const {
    expand_base__(
      ans,
      n,
      1,
      [this](Poly &ans, size_t n) -> void {
        n -= 2;
        u64 _ = 0;
        for (size_t i = 0; i <= n; ++i) _ = (_ + (u64)(i + 1) * p.data[i + 1] % p.mod() * ans[n - i]) % p.mod();
        ans.p.data.push_back((u32)(_ * inverse((u32)n + 1, p.mod()) % p.mod()));
      },
      [this](Poly &ans, size_t n) -> void {
        Poly ans_ln = ans;
        ans_ln.do_resize(n).do_ln();
        for (size_t i = 0; i < ans_ln.size(); ++i) ans_ln[i] = (p.mod() + p.data[i] - ans_ln[i]) % p.mod();
        ++ans_ln[0];
        (ans *= ans_ln).do_resize(n);
      });
  }

  constexpr void sqrt_(Poly &ans, size_t n) const {
    if (n == 1) {
      i32 qres = qresidue(p.data[0], p.mod());
      assert(qres > 0);
      ans.p.data[0] = std::min(qres, (i32)(p.mod() - qres));
      return;
    }
    sqrt_(ans, (n + 1) / 2);
    Poly sA = *this;
    sA.do_resize(n);
    ans.do_resize(ans.size() * 2);
    ans = (sA + (ans * ans).do_resize(n)) * inverse(ans * 2);
    ans.do_resize(n);
  }

public:
  using base = PBase;

  explicit constexpr Poly(size_t sz = 1):
    p(sz) {}
  explicit constexpr Poly(std::initializer_list<u32> v):
    p(v) {}
  explicit constexpr Poly(vec<u32> const &v):
    p(v) {}

  constexpr friend std::istream &operator>>(std::istream &is, Poly &poly) {
    for (auto &val : poly.p.data) is >> val;
    return is;
  }
  constexpr friend std::ostream &operator<<(std::ostream &os, const Poly &poly) {
    if (!poly.size()) return os;
    for (size_t i = 1; i < poly.size(); ++i) os << poly[i - 1] << ' ';
    return os << poly.p.data.back();
  }

  constexpr u32 &operator[](size_t x) { return p.data[x]; }
  constexpr u32 operator[](size_t x) const { return p.data[x]; }
  [[nodiscard]] constexpr u32 operator()(size_t x) const {
    u32 ans = 0;
    for (size_t i = size() - 1; ~i; --i) ans = (u32)(((u64)ans * x + p.data[i]) % p.mod());
    return ans;
  }

  constexpr size_t size() const { return p.data.size(); }
  constexpr Poly &do_resize(size_t size) {
    p.data.resize(size);
    return *this;
  }
  constexpr Poly &do_strip() {
    while (!p.data.empty() && !p.data.back()) p.data.pop_back();
    if (p.data.empty()) p.data.push_back(0);
    return *this;
  }
  constexpr Poly &do_reverse() {
    std::reverse(p.data.begin(), p.data.end());
    return *this;
  }

  constexpr Poly &operator*=(u32 c) {
    for (u32 &val : p.data) val = (u32)((u64)val * c % p.mod());
    return *this;
  }
  constexpr friend Poly operator*(Poly poly, u32 c) { return poly *= c; }
  constexpr friend Poly operator*(u32 c, Poly poly) { return poly *= c; }

#define OOCR_(op, ...) \
  constexpr Poly &operator op##=(Poly const &rhs) __VA_ARGS__ friend Poly operator op(Poly lhs, Poly const &rhs) { return lhs op## = rhs; }
#define OO_(op, ...)                                                         \
  constexpr Poly &operator op##=(Poly rhs) __VA_ARGS__ constexpr friend Poly \
  operator op(Poly lhs, Poly const &rhs) { return lhs op## = rhs; }

  OOCR_(+, {
    do_resize(std::max(size(), rhs.size()));
    for (size_t i = 0; i < rhs.size(); ++i) p.data[i] = (u32)((u64)p.data[i] + rhs[i]) % p.mod();
    return *this;
  })
  OOCR_(-, {
    do_resize(std::max(size(), rhs.size()));
    for (size_t i = 0; i < rhs.size(); ++i) p.data[i] = (u32)((u64)p.data[i] + (p.mod() - rhs[i])) % p.mod();
    return *this;
  })
  OOCR_(*, {
    p *= rhs.p;
    return *this;
  })
  OO_(/, {
    size_t n = size(), m = rhs.size();
    std::reverse(p.data.begin(), p.data.end());
    std::reverse(rhs.p.data.begin(), rhs.p.data.end());
    (*this *= rhs.do_resize(n - m + 1).do_inverse()).do_resize(n - m + 1);
    std::reverse(p.data.begin(), p.data.end());
    return *this;
  })
  OOCR_(%, {
    auto &&__ = rhs * (*this / rhs);
    return (*this -= __).do_resize(rhs.size() - 1);
  })

#undef OO_
#undef OOCR_

  constexpr Poly &do_shl(size_t offset) {
    if (offset == 0) return *this;
    if (offset >= size()) {
      std::fill(p.data.begin(), p.data.end(), 0);
      return *this;
    }
    std::fill(std::move(p.data.begin() + offset, p.data.end(), p.data.begin()), p.data.end(), 0);
    return *this;
  }

  constexpr Poly &do_shr(size_t offset) {
    if (offset == 0) return *this;
    if (offset >= size()) {
      std::fill(p.data.begin(), p.data.end(), 0);
      return *this;
    }
    std::fill(p.data.begin(), std::move_backward(p.data.begin(), p.data.end() - offset, p.data.end()), 0);
    return *this;
  }

#define FUNC_(name, ...)                                        \
  constexpr Poly &do_##name() __VA_ARGS__ constexpr friend Poly \
  name(Poly poly) { return poly.do_##name(); }
#define FUNCP1_(name, type1, var1, ...)                                   \
  constexpr Poly &do_##name(type1 var1) __VA_ARGS__ constexpr friend Poly \
  name(Poly poly, type1 var1) { return poly.do_##name(var1); }

  FUNC_(inverse, {
    Poly ret;
    inv_(ret, size());
    return *this = ret;
  })
  FUNC_(derivative, {
    for (size_t i = 1; i < size(); ++i) p.data[i - 1] = (u32)((u64)p.data[i] * i % p.mod());
    p.data.back() = 0;
    return *this;
  })
  FUNC_(integral, {
    p.data.push_back(0);
    for (size_t i = size() - 1; i; --i) p.data[i] = (u32)((u64)p.data[i - 1] * inverse(i, p.mod()) % p.mod());
    p.data[0] = 0;
    p.data.pop_back();
    return *this;
  })
  FUNC_(ln, {
    assert(p.data[0] == 1);
    size_t n = size();
    return *this = (derivative(*this) * inverse(*this)).do_resize(n).do_integral();
  })
  FUNC_(exp, {
    assert(p.data[0] == 0);
    Poly ret;
    exp_(ret, size());
    return *this = ret;
  })
  FUNC_(sqrt, {
    Poly ret;
    sqrt_(ret, size());
    return *this = ret;
  })
  FUNC_(sin, {
    size_t n = size();
    u32 i = qpow_mod(proot(p.mod()), (p.mod() - 1) / 4, p.mod());
    *this *= i;
    return (*this = (exp(*this * (p.mod() - 1)) - exp(*this)) * (u32)((u64)i * inverse(2, p.mod()) % p.mod())).do_resize(n);
  })
  FUNC_(cos, {
    size_t n = size();
    u32 i = qpow_mod(proot(p.mod()), (p.mod() - 1) / 4, p.mod());
    *this *= i;
    return (*this = (exp(*this) + exp(*this * (p.mod() - 1))) * (u32)inverse(2, p.mod())).do_resize(n);
  })
  FUNC_(tan, {
    size_t n = size();
    u32 i = 2 * qpow_mod(proot(p.mod()), (p.mod() - 1) / 4, p.mod());
    (*this *= i).do_exp();
    Poly _1 = *this, _2 = *this;
    if (--_1[0] < 0) _1[0] += p.mod();
    if (++_2[0] == p.mod()) _2[0] = 0;
    return (*this = _1 * (_2.do_inverse() * (p.mod() - i))).do_resize(n);
  })
  FUNC_(asin, {
    size_t n = size();
    Poly _1 = (*this * (*this * (p.mod() - 1))).do_resize(n);
    if (++_1[0] == p.mod()) _1[0] = 0;
    return (*this = (derivative(*this) * _1.do_sqrt().do_inverse()).do_resize(n).do_integral());
  })
  FUNC_(acos, {
    size_t n = size();
    Poly _1 = (*this * *this * (p.mod() - 1)).do_resize(n);
    if (++_1[0] == p.mod()) _1[0] = 0;
    return (*this = (derivative(*this) * (_1.do_sqrt().do_inverse() * (p.mod() - 1))).do_resize(n).do_integral()).do_resize(n);
  })
  FUNC_(atan, {
    size_t n = size();
    Poly _1 = (*this * *this).do_resize(n);
    if (++_1[0] == p.mod()) _1[0] = 0;
    return (*this = (derivative(*this) * _1.do_inverse()).do_resize(n).do_integral()).do_resize(n);
  })
  FUNCP1_(pow, u32, y, {
    assert(p.data[0] == 1);
    if (y == 0) {
      std::fill(p.data.begin() + 1, p.data.end(), 0);
      return *this;
    }
    if (y == 1) return *this;
    return *this = (ln(*this) * (i32)y).do_exp();
  })

#undef FUNC_
#undef FUNCP1_
};
}  // namespace detail__

#define POLYT_ detail__::Poly<T>

// @return {q, r} s.t. f = qg + r && deg(r) < deg(g)
template <class T>
constexpr std::pair<POLYT_, POLYT_> divmod(POLYT_ const &f, POLYT_ const &g) {
  auto div_ = f / g;
  return {div_, (f - g * div_).do_resize(g.size() - 1)};
}

// Chirp Z-Transform
// @return {f(c^0), f(c^1), ..., f(c^{m-1})}
template <class T>
constexpr POLYT_ czt(POLYT_ const &f, u32 c, size_t m) {
  class Rpow_ {
    u32 a, mod;
    std::array<u32, 65536> block1, block2;

  public:
    explicit constexpr Rpow_():
      a(0), mod(0) {}
    constexpr Rpow_(u32 a, u32 p):
      Rpow_() { reset(a, p); }
    constexpr void reset(u32 a_, u32 p_) {
      assert(p_ > 1);
      if (a == a_ && mod == p_) return;
      a = a_;
      mod = p_;
      block1[0] = block2[0] = 1;
      for (u32 i = 1; i < 65536; i++) block1[i] = (u32)((u64)block1[i - 1] * a % mod);
      u32 _ = (u32)((u64)block1.back() * a % mod);
      for (u32 i = 1; i < 65536; i++) block2[i] = (u32)((u64)block2[i - 1] * _ % mod);
    }
    constexpr u32 operator()(size_t exponent) { return (u32)((u64)block1[exponent & 65535] * block2[exponent >> 16] % mod); }
  };

  u32 mod = POLYT_::base::mod();
  c %= mod;
  Rpow_ rp(c, mod);
  size_t n = f.size();
  POLYT_ cc(n + m - 1), g(n);
  for (size_t i = 0; i < n + m - 1; ++i) cc[n + m - 2 - i] = rp((u64)(i - 1) * i / 2 % (mod - 1));
  for (size_t i = 0; i < n; ++i) g[i] = (u32)((u64)rp(mod - 1 - ((u64)i * (i - 1) / 2) % (mod - 1)) * f[i] % mod);
  cc *= g;
  POLYT_ ans(m);
  for (size_t i = 0; i < m; ++i) ans[i] = (u32)((u64)cc[n + m - 2 - i] * rp(mod - 1 - ((u64)i * (i - 1) / 2) % (mod - 1)) % mod);
  return ans;
}

// Multi-point evaluation based on Tellegen's Principle
// @return {f(a[0]), f(a[1]), ..., f(a.back())}
template <class T>
constexpr POLYT_ mpe(POLYT_ f, POLYT_ a) {
  class SegTree {
    vec<POLYT_> t;

    constexpr void init_(POLYT_ const &a, size_t k, size_t l, size_t r) {
      if (l == r) {
        t[k] = POLYT_{1, a[l] ? POLYT_::base::mod() - a[l] : 0};
        return;
      }
      size_t m = l + (r - l) / 2;
      init_(a, k * 2, l, m);
      init_(a, k * 2 + 1, m + 1, r);
      t[k] = t[k * 2] * t[k * 2 + 1];
    }
    constexpr static POLYT_ mult(POLYT_ const &f, POLYT_ g) {
      size_t m = g.size();
      return (f * g.do_reverse()).do_shl(m - 1).do_resize(f.size());
    }
    constexpr void calc_(POLYT_ f, POLYT_ &res, size_t k, size_t l, size_t r) const {
      f.do_resize(r - l + 1);
      if (l == r) {
        res[l] = f[0];
        return;
      }
      size_t m = l + (r - l) / 2;
      calc_(mult(f, t[k * 2 + 1]), res, k * 2, l, m);
      calc_(mult(f, t[k * 2]), res, k * 2 + 1, m + 1, r);
    }

  public:
    explicit constexpr SegTree(POLYT_ const &a):
      t(a.size() * 4) { init_(a, 1, 0, a.size() - 1); }

    constexpr POLYT_ operator()(POLYT_ const &f) const {
      POLYT_ res(f.size());
      calc_(mult(f, inverse(t[1])), res, 1, 0, t.size() / 4 - 1);
      return res;
    }
  };

  size_t n = f.size(), m = a.size();
  f.do_resize(std::max(n, m));
  a.do_resize(std::max(n, m));
  return SegTree(a)(f).do_resize(m);
}

// Lagrange interpolation in O(n \log^2 n)
// @return f s.t. f(x[i]) = y[i]
template <class T>
constexpr POLYT_ interp(POLYT_ const &x, POLYT_ const &y) {
  class SegTree {
    constexpr void init_(POLYT_ const &a, size_t k, size_t l, size_t r) {
      if (l == r) {
        t[k] = POLYT_{a[l] ? POLYT_::base::mod() - a[l] : 0, 1};
        return;
      }
      size_t m = l + (r - l) / 2;
      init_(a, k * 2, l, m);
      init_(a, k * 2 + 1, m + 1, r);
      t[k] = t[k * 2] * t[k * 2 + 1];
    }
    constexpr POLYT_ calc_(POLYT_ const &f, size_t k, size_t l, size_t r) const {
      if (l == r) return POLYT_{f[l]};
      size_t m = l + (r - l) / 2;
      return calc_(f, k * 2, l, m) * t[2 * k + 1] + calc_(f, k * 2 + 1, m + 1, r) * t[2 * k];
    }

  public:
    vec<POLYT_> t;

    explicit constexpr SegTree(POLYT_ const &a):
      t(a.size() * 4) { init_(a, 1, 0, a.size() - 1); }

    constexpr POLYT_ operator()(POLYT_ const &f) const { return calc_(f, 1, 0, t.size() / 4 - 1); }
  };

  assert(x.size() == y.size());
  size_t n = x.size();
  SegTree sgt(x);
  POLYT_ t = mpe(sgt.t[1].do_derivative(), x);
  for (size_t i = 0; i < n; ++i) t[i] = (u32)(y[i] * detail__::inverse(t[i], POLYT_::base::mod()) % POLYT_::base::mod());
  return sgt(t);
}

// Kth term of Linearly Recurrent Sequence
// @return u(k), which u(n+d)=\sum_{i=0}^{d-1} u(n+i)c(i) and u(i) = a[i] for i = 0 .. d-1;
// template <class T>
// constexpr u32 lrs(POLYT_ const &c, POLYT_ const &a, u64 k) {
//     assert(c.size() == a.size());
// }

#undef POLYT_

//! MOD MUST be prime with 4k+1
template <i32 MOD>
using s_poly = detail__::Poly<detail__::SmodPolyBase_<MOD>>;
//! mod MUST be prime, MUST call d_poly::base::set_mod() first
template <ptrdiff_t ID, class DBL = double>
using d_poly = detail__::Poly<detail__::DmodPolyBase_<ID, DBL>>;
}  // namespace tifa_libs::poly

#endif