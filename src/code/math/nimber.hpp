#ifndef TIFALIBS_MATH_NIMBER
#define TIFALIBS_MATH_NIMBER

#include "nim_prod.hpp"

namespace tifa_libs::math {

template <std::unsigned_integral T, T (*prod)(T, T)>
struct nimber {
  T x;
  CEXP nimber(T _x = 0) NE : x(_x) {}

  CEXP nimber& operator+=(nimber CR p) NE {
    x ^= p.x;
    return *this;
  }
  CEXP nimber& operator-=(nimber CR p) NE {
    x ^= p.x;
    return *this;
  }
  CEXP nimber& operator*=(nimber CR p) NE {
    x = prod(x, p.x);
    return *this;
  }
  CEXP nimber operator+(nimber CR p) CNE { return x ^ p.x; }
  CEXP nimber operator-(nimber CR p) CNE { return x ^ p.x; }
  CEXP nimber operator*(nimber CR p) CNE { return prod(x, p.x); }
  CEXP bool operator==(nimber CR p) CNE { return x == p.x; }
  friend std::ostream& operator<<(std::ostream& os, nimber CR p) NE { return os << p.x; }
};

using nimber16 = nimber<u16, nimprod16>;
using nimber32 = nimber<u32, nimprod32>;
using nimber64 = nimber<u64, nimprod64>;

}  // namespace tifa_libs::math

#endif