#ifndef TIFALIBS_IO_IOS128
#define TIFALIBS_IO_IOS128

#include "../util/traits_math.hpp"
#include "../util/traits_others.hpp"

namespace tifa_libs {
namespace ios128_impl_ {
auto& read(tifa_libs::istream_c auto& is, tifa_libs::u128_c auto& n) {
  static strn int_buf;
  int_buf.reserve(43), n = 0, is >> int_buf;
  for (u32 i = 0; i + 1 < int_buf.size(); i += 2) (n *= 100) += STR2U16[*(u16*)(int_buf.data() + i)];
  if (int_buf.size() & 1) (n *= 10) += int_buf.back() & 15;
  return is;
}
}  // namespace ios128_impl_

auto& operator>>(tifa_libs::istream_c auto& is, tifa_libs::s128_c auto& n) NE {
  bool neg = false;
  if CEXP (requires { is.skip_nnegdigit(); }) neg = (is.skip_nnegdigit().peek() == '-' && is.get_unchk());
  else
    while (!neg && !isdigit(is.peek())) {
      if (is.peek() == '-') neg = true;
      is.get();
    }
  u128 n_ = 0;
  if (ios128_impl_::read(is, n_); neg) n_ = -n_;
  n = (i128)n_;
  return is;
}
auto& operator>>(tifa_libs::istream_c auto& is, tifa_libs::u128_c auto& n) NE {
  if CEXP (requires { is.skip_ndigit(); }) is.skip_ndigit();
  else
    while (!isdigit(is.peek())) is.get();
  return ios128_impl_::read(is, n);
}
auto& operator<<(tifa_libs::ostream_c auto& os, tifa_libs::u128_c auto n) NE {
  static strn int_buf(40, '\0');
  auto it = end(int_buf);
  do *(--(it)) = char(n % 10) | '0';
  while (n /= 10);
  return os << int_buf.substr(usz(it - begin(int_buf)));
}
auto& operator<<(tifa_libs::ostream_c auto& os, tifa_libs::s128_c auto n) NE {
  if (n < 0) return os << '-' << -(u128)n;
  return os << (u128)n;
}

}  // namespace tifa_libs

#endif