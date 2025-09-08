#ifndef TIFALIBS_IO_IOS128
#define TIFALIBS_IO_IOS128

#include "../util/traits_math.hpp"
#include "../util/traits_others.hpp"

namespace tifa_libs {

auto &operator>>(tifa_libs::istream_c auto &is, tifa_libs::s128_c auto &n) NE {
  bool neg = false;
  while (!neg && !isdigit(is.peek())) {
    if (is.peek() == '-') neg = true;
    is.get();
  }
  u128 n_ = 0;
  while (isdigit(is.peek())) (n_ *= 10) += is.get() & 15;
  if (neg) n_ = -n_;
  n = (i128)n_;
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
  auto it = end(int_buf);
  do *(--(it)) = char(n % 10) | '0';
  while (n /= 10);
  return os << int_buf.substr(usz(it - begin(int_buf)));
}
auto &operator<<(tifa_libs::ostream_c auto &os, tifa_libs::s128_c auto n) NE {
  if (n < 0) return os << '-' << -(u128)n;
  return os << (u128)n;
}

}  // namespace tifa_libs

#endif