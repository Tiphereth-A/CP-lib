#pragma once

#include "../../../util/traits/others/lib.hpp"

namespace tifa_libs {

#define FOR1_(i, l, r) for (u32 i = (l), i##ed__ = (r); i < i##ed__; ++i)
#define FOR2_(i, row_l, row_r, j, col_l, col_r) \
  FOR1_ (i, row_l, row_r)                       \
    FOR1_ (j, col_l, col_r)

template <u32 MAXLEN>
class bitmat {
  std::bitset<MAXLEN> data;
  u32 r_ = 0, c_ = 0;

  CEXP u32 idx_(u32 r, u32 c) CNE { return r * c_ + c; }

 public:
  CEXP bitmat() NE = default;
  CEXP bitmat(u32 row, u32 col) NE : r_(row), c_(col) { assert(r_ * c_ <= MAXLEN); }

  CEXP u32 row() CNE { return r_; }
  CEXP u32 col() CNE { return c_; }
  CEXP usz capacity() CNE { return MAXLEN; }

  CEXP void reshape(u32 row, u32 col, bool clear = true) NE {
    r_ = row, c_ = col;
    assert(r_ * c_ <= MAXLEN);
    if (clear) data.reset();
  }
  CEXP void reset() NE { data.reset(); }

  CEXP bool test(u32 r, u32 c) CNE { return data._Unchecked_test(idx_(r, c)); }
  CEXP void set(u32 r, u32 c) NE { data._Unchecked_set(idx_(r, c)); }
  CEXP void reset(u32 r, u32 c) NE { data._Unchecked_reset(idx_(r, c)); }
  CEXP void flip(u32 r, u32 c) NE { data._Unchecked_flip(idx_(r, c)); }

  CEXP bool _Unchecked_test(usz p) CNE { return data._Unchecked_test(p); }
  CEXP void _Unchecked_set(usz p) NE { data._Unchecked_set(p); }
  CEXP void _Unchecked_reset(usz p) NE { data._Unchecked_reset(p); }
  CEXP void _Unchecked_flip(usz p) NE { data._Unchecked_flip(p); }
  CEXP usz _Find_first() CNE { return data._Find_first(); }
  CEXP usz _Find_next(usz p) CNE { return data._Find_next(p); }

  CEXP std::istream& read(std::istream& is, u32 r, u32 c) NE {
    reshape(r, c, true);
    char ch;
    FOR2_ (i, 0, r, j, 0, c) {
      is >> ch;
      if (ch & 1) _Unchecked_set((usz)i * c + j);
    }
    return is;
  }
  CEXP std::istream& read_trans(std::istream& is, u32 r, u32 c) NE {
    reshape(c, r, true);
    char ch;
    FOR2_ (i, 0, r, j, 0, c) {
      is >> ch;
      if (ch & 1) _Unchecked_set((usz)j * r + i);
    }
    return is;
  }
  CEXP std::ostream& print(std::ostream& os, u32 r, u32 c) CNE {
    assert(r <= row() && c <= col());
    const u32 C = col();
    FOR2_ (i, 0, r, j, 0, c)
      if (os << _Unchecked_test((usz)i * C + j); j == c - 1 && i != r - 1) os << '\n';
    return os;
  }

  friend auto& operator>>(istream_c auto& is, bitmat& bmat) NE {
    assert(bmat.row() && bmat.col());
    return bmat.read(is, bmat.row(), bmat.col());
  }
  friend auto& operator<<(ostream_c auto& os, bitmat CR bmat) NE { return bmat.print(os, bmat.row(), bmat.col()); }
};

#undef FOR1_
#undef FOR2_

}  // namespace tifa_libs
