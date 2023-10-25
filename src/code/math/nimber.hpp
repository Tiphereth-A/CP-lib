#ifndef TIFA_LIBS_MATH_NIMBER
#define TIFA_LIBS_MATH_NIMBER

#include "../util/hash_splitmix64.hpp"
#include "crt_mod.hpp"
#include "nim_prod.hpp"

namespace tifa_libs::math {

template <class uint, uint (*prod)(uint, uint)>
struct nimber {
  using N = nimber;
  uint x;
  constexpr nimber() : x(0) {}
  constexpr nimber(uint _x) : x(_x) {}
  static N id0() { return {}; }
  static N id1() { return {1}; }

  constexpr N& operator+=(N const& p) {
    x ^= p.x;
    return *this;
  }
  constexpr N& operator-=(N const& p) {
    x ^= p.x;
    return *this;
  }
  constexpr N& operator*=(N const& p) {
    x = prod(x, p.x);
    return *this;
  }
  constexpr N operator+(N const& p) const { return x ^ p.x; }
  constexpr N operator-(N const& p) const { return x ^ p.x; }
  constexpr N operator*(N const& p) const { return prod(x, p.x); }
  constexpr bool operator==(N const& p) const { return x == p.x; }
  constexpr bool operator!=(N const& p) const { return x != p.x; }
  constexpr N pow(u64 n) const {
    N a = *this, r = 1;
    for (; n; a *= a, n >>= 1)
      if (n & 1) r *= a;
    return r;
  }
  friend std::ostream& operator<<(std::ostream& os, N const& p) { return os << p.x; }

  // calculate log_a (b)
  uint discrete_log(N y) const {
    assert(x != 0 && y != 0);
    vec<uint> rem, mod;
    for (uint p : {3, 5, 17, 257, 641, 65537, 6700417}) {
      if (uint(-1) % p) continue;
      uint q = uint(-1) / p;
      uint STEP = 1;
      while (4 * STEP * STEP < p) STEP *= 2;
      auto inside = [&](N a, N z) -> uint {
        hmap<uint, i32> mp;
        N big = 1, now = 1;  // x^m
        for (u32 i = 0; i < u32(STEP); ++i) mp[z.x] = i, z *= a, big *= a;
        for (i32 step = 0; step < i32(p + 10); step += STEP) {
          now *= big;
          if (mp.find(now.x) != mp.end()) return (step + STEP) - mp[now.x];
        }
        return uint(-1);
      };
      N xq = (*this).pow(q), yq = y.pow(q);
      if (xq == 1 and yq == 1) continue;
      if (xq == 1 and yq != 1) return uint(-1);
      uint res = inside(xq, yq);
      if (res == uint(-1)) return uint(-1);
      rem.push_back(res % p);
      mod.push_back(p);
    }
    return crt_mod(rem, mod).first;
  }
  constexpr uint is_primitive_root() const {
    if (x == 0) return false;
    for (uint p : {3, 5, 17, 257, 641, 65537, 6700417}) {
      if (uint(-1) % p != 0) continue;
      if ((*this).pow(uint(-1) / p) == 1) return false;
    }
    return true;
  }
};

using nimber16 = nimber<u16, nimprod16>;
using nimber32 = nimber<u32, nimprod32>;
using nimber64 = nimber<u64, nimprod64>;

}  // namespace tifa_libs::math

#endif