#pragma once

#include "../ge/lib.hpp"

namespace tifa_libs {

template <u32 MAXLEN>
CEXP auto inv_bmat(bitmat<MAXLEN> CR mat, u32 n) NE {
  assert(n <= mat.row() && n <= mat.col());
  bitmat<MAXLEN * 2> _(n, n * 2);
  auto test_aug = [&](u32 i, u32 j) -> bool { return _._Unchecked_test((usz)i * (n * 2) + j); };
  auto row_find_next_mat = [&](u32 i, u32 from) -> u32 {
    const usz base = (usz)i * mat.col();
    usz p;
    if (!from) p = base ? mat._Find_next(base - 1) : mat._Find_first();
    else p = mat._Find_next(base + from - 1);
    return p < (usz)(i + 1) * mat.col() ? (u32)(p - base) : mat.col();
  };
  auto row_find_next_aug = [&](u32 i, u32 from) -> u32 {
    const usz base = (usz)i * (n * 2);
    usz p;
    if (!from) p = base ? _._Find_next(base - 1) : _._Find_first();
    else p = _._Find_next(base + from - 1);
    return p < (usz)(i + 1) * (n * 2) ? (u32)(p - base) : n * 2;
  };
  flt_ (u32, i, 0, n) {
    for (u32 p = row_find_next_mat(i, 0); p < n; p = row_find_next_mat(i, p + 1)) _._Unchecked_set((usz)i * (n * 2) + p);
    _._Unchecked_set((usz)i * (n * 2) + i + n);
  }
  std::optional<bitmat<MAXLEN>> ret;
  if (ge_bmat(_, true) != n) return ret;
  flt_ (u32, i, 0, n)
    if (!test_aug(i, i)) return ret;
  ret.emplace(n, n);
  flt_ (u32, i, 0, n)
    for (u32 p = row_find_next_aug(i, n); p < n * 2; p = row_find_next_aug(i, p + 1)) ret.value()._Unchecked_set((usz)i * n + (p - n));
  return ret;
}

}  // namespace tifa_libs
