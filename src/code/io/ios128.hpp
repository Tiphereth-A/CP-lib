#ifndef TIFALIBS_IO_IOS128
#define TIFALIBS_IO_IOS128

#include "../util/util.hpp"

inline std::istream &operator>>(std::istream &is, i128 &n) NE {
  bool neg = false;
  while (!neg && !isdigit(is.peek())) {
    if (is.peek() == '-') neg = true;
    is.get();
  }
  n = 0;
  while (isdigit(is.peek())) (n *= 10) += is.get() & 15;
  if (neg) n = -n;
  return is;
}
inline std::istream &operator>>(std::istream &is, u128 &n) NE {
  while (!isdigit(is.peek())) is.get();
  n = 0;
  while (isdigit(is.peek())) (n *= 10) += is.get() & 15;
  return is;
}
inline std::ostream &operator<<(std::ostream &os, u128 n) NE {
  if (n > 9) os << n / 10;
  return os << (uint_fast32_t)(n % 10);
}
inline std::ostream &operator<<(std::ostream &os, i128 n) NE {
  if (n < 0) os << '-', n = -n;
  return os << (u128)n;
}

#endif