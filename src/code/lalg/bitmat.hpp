#ifndef TIFALIBS_LALG_BITMAT
#define TIFALIBS_LALG_BITMAT

#include "mat.hpp"

namespace tifa_libs::math {

#define FOR1_(i, l, r) for (usz i = (l), i##ed__ = (r); i < i##ed__; ++i)
#define FOR2_(i, row_l, row_r, j, col_l, col_r) \
  FOR1_ (i, row_l, row_r)                       \
    FOR1_ (j, col_l, col_r)

template <usz R, usz C = R>
using bitmat = arr<std::bitset<C>, R>;

template <usz R, usz C>
CEXP matrix<bool> bitmat2mat(cT_(bitmat<R, C>) bmat) NE {
  matrix<bool> ret(R, C);
  ret.apply([&bmat](u32 i, u32 j, auto &b) NE { b = bmat[i][j]; });
  return ret;
}
template <usz R, usz C = R>
CEXP bitmat<R, C> mat2bitmat(cT_(matrix<bool>) mat) NE {
  const u32 r = mat.row(), c = mat.col();
  assert(r <= R && c <= C);
  bitmat<R, C> ret;
  FOR2_ (i, 0, r, j, 0, c) ret[i][j] = mat(i, j);
  return ret;
}
template <usz R, usz C>
std::istream &read_bitmat(std::istream &is, bitmat<R, C> &bmat, u32 r, u32 c) NE {
  assert(r <= R && c <= C);
  char ch;
  FOR2_ (i, 0, r, j, 0, c) is >> ch, bmat[i][j] = ch & 1;
  return is;
}
template <usz R, usz C>
std::istream &read_bitmat_trans(std::istream &is, bitmat<R, C> &bmat, u32 r, u32 c) NE {
  assert(r <= R && c <= C);
  char ch;
  FOR2_ (i, 0, r, j, 0, c) is >> ch, bmat[j][i] = ch & 1;
  return is;
}
template <usz R, usz C>
std::ostream &print_bitmat(std::ostream &os, bitmat<R, C> &bmat, u32 r, u32 c) NE {
  assert(r <= R && c <= C);
  FOR2_ (i, 0, r, j, 0, c)
    if (os << bmat[i][j]; j == c - 1 && i != r - 1) os << '\n';
  return os;
}
template <usz R, usz C>
std::istream &operator>>(std::istream &is, bitmat<R, C> &bmat) NE { return read_bitmat(is, bmat, R, C); }
template <usz R, usz C>
std::ostream &operator<<(std::ostream &os, bitmat<R, C> CR bmat) NE { return print_bitmat(os, bmat, R, C); }

#undef FOR1_
#undef FOR2_

}  // namespace tifa_libs::math

#endif