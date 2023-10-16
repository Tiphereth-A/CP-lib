#ifndef TIFA_LIBS_UTIL_IOS128
#define TIFA_LIBS_UTIL_IOS128

#include "util.hpp"

inline std::istream &operator>>(std::istream &is, tifa_libs::i128 &n) {
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
inline std::istream &operator>>(std::istream &is, tifa_libs::u128 &n) {
  while (!isdigit(is.peek())) is.get();
  n = 0;
  while (isdigit(is.peek())) (n *= 10) += is.get() & 15;
  return is;
}
inline std::ostream &operator<<(std::ostream &os, tifa_libs::i128 n) {
  if (n < 0) {
    os << '-';
    n = -n;
  }
  if (n > 9) os << n / 10;
  os << (uint_fast32_t)(n % 10);
  return os;
}
inline std::ostream &operator<<(std::ostream &os, tifa_libs::u128 n) {
  if (n > 9) os << n / 10;
  os << (uint_fast32_t)(n % 10);
  return os;
}

#endif