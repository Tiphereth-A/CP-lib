#ifndef TIFALIBS_IO_IOS128
#define TIFALIBS_IO_IOS128

#include "../util/traits_math.hpp"
#include "../util/traits_others.hpp"

auto &operator>>(tifa_libs::istream_c auto &is, tifa_libs::s128_c auto &n) NE {
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
auto &operator>>(tifa_libs::istream_c auto &is, tifa_libs::u128_c auto &n) NE {
  while (!isdigit(is.peek())) is.get();
  n = 0;
  while (isdigit(is.peek())) (n *= 10) += is.get() & 15;
  return is;
}
auto &operator<<(tifa_libs::ostream_c auto &os, tifa_libs::u128_c auto n) NE {
  static strn int_buf(40, '\0');
  auto it = int_buf.end();
  do *(--(it)) = char(n % 10) | '0';
  while (n /= 10);
  return os << int_buf.substr(usz(it - int_buf.begin()));
}
auto &operator<<(tifa_libs::ostream_c auto &os, tifa_libs::s128_c auto n) NE {
  if (n < 0) os << '-', n = -n;
  return os << (u128)n;
}

#endif