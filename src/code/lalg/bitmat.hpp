#ifndef TIFALIBS_LALG_BITMAT
#define TIFALIBS_LALG_BITMAT

#include "mat.hpp"

namespace tifa_libs::math {

#define FOR1_(i, l, r) for (usz i = (l), i##ed__ = (r); i < i##ed__; ++i)
#define FOR2_(i, row_l, row_r, j, col_l, col_r) \
  FOR1_ (i, row_l, row_r)                       \
    FOR1_ (j, col_l, col_r)

template <usz R, usz C = R>
using bitmat = std::array<std::bitset<C>, R>;

template <usz R, usz C>
constexpr matrix<bool> bitmat2mat(bitmat<R, C> const &bmat) {
  matrix<bool> ret(R, C);
  ret.apply([&bmat](u32 i, u32 j, auto &b) { b = bmat[i][j]; });
  return ret;
}

template <usz R, usz C = R>
constexpr bitmat<R, C> mat2bitmat(matrix<bool> const &mat) {
  u32 r = mat.row(), c = mat.col();
  assert(r <= R && c <= C);
  bitmat<R, C> ret;
  FOR2_ (i, 0, r, j, 0, c) ret[i][j] = mat(i, j);
  return ret;
}

template <usz R, usz C>
std::istream &read_bitmat(std::istream &is, bitmat<R, C> &bmat, u32 r, u32 c) {
  assert(r <= R && c <= C);
  char ch;
  FOR2_ (i, 0, r, j, 0, c) {
    is >> ch;
    bmat[i][j] = ch & 1;
  }
  return is;
}
template <usz R, usz C>
std::istream &read_bitmat_trans(std::istream &is, bitmat<R, C> &bmat, u32 r, u32 c) {
  assert(r <= R && c <= C);
  char ch;
  FOR2_ (i, 0, r, j, 0, c) {
    is >> ch;
    bmat[j][i] = ch & 1;
  }
  return is;
}

template <usz R, usz C>
std::ostream &print_bitmat(std::ostream &os, bitmat<R, C> &bmat, u32 r, u32 c) {
  assert(r <= R && c <= C);
  FOR2_ (i, 0, r, j, 0, c) {
    os << bmat[i][j];
    if (j == c - 1 && i != r - 1) os << '\n';
  }
  return os;
}

template <usz R, usz C>
std::istream &operator>>(std::istream &is, bitmat<R, C> &bmat) { return read_bitmat(is, bmat, R, C); }
template <usz R, usz C>
std::ostream &operator<<(std::ostream &os, bitmat<R, C> const &bmat) { return print_bitmat(os, bmat, R, C); }

#undef FOR1_
#undef FOR2_

}  // namespace tifa_libs::math

#endif