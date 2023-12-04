#ifndef TIFALIBS_MATH_NIMBER
#define TIFALIBS_MATH_NIMBER

#include "nim_prod.hpp"

namespace tifa_libs::math {

template <class uint, uint (*prod)(uint, uint)>
struct nimber {
  uint x;
  constexpr nimber(uint _x = 0) : x(_x) {}

  constexpr nimber& operator+=(nimber const& p) {
    x ^= p.x;
    return *this;
  }
  constexpr nimber& operator-=(nimber const& p) {
    x ^= p.x;
    return *this;
  }
  constexpr nimber& operator*=(nimber const& p) {
    x = prod(x, p.x);
    return *this;
  }
  constexpr nimber operator+(nimber const& p) const { return x ^ p.x; }
  constexpr nimber operator-(nimber const& p) const { return x ^ p.x; }
  constexpr nimber operator*(nimber const& p) const { return prod(x, p.x); }
  constexpr bool operator==(nimber const& p) const { return x == p.x; }
  constexpr bool operator!=(nimber const& p) const { return x != p.x; }
  friend std::ostream& operator<<(std::ostream& os, nimber const& p) { return os << p.x; }
};

using nimber16 = nimber<u16, nimprod16>;
using nimber32 = nimber<u32, nimprod32>;
using nimber64 = nimber<u64, nimprod64>;

}  // namespace tifa_libs::math

#endif