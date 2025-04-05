#ifndef TIFALIBS_UTIL_BITSET_GETDATA
#define TIFALIBS_UTIL_BITSET_GETDATA

#include "util.hpp"

namespace tifa_libs {

template <size_t N>
struct bitset_getdata {
  using word_t = std::_Base_bitset<2>::_WordT;
  static CEXP size_t Nw = (N / (8 * sizeof(word_t)) + !!(N % (8 * sizeof(word_t))));
  static_assert(Nw > 0);

  static CEXP word_t* getdata(std::bitset<N>& x) NE {
    if CEXP (Nw == 1) return &(c_(x)->_M_w);
    else return c_(x)->_M_w;
  }
  static CEXP auto getdata(std::bitset<N> CR x) NE { return cc_(x)->_M_getdata(); }
  static CEXP word_t& getword(std::bitset<N>& x, size_t pos) NE { return c_(x)->_M_getword(pos); }
  static CEXP word_t getword(std::bitset<N> CR x, size_t pos) NE { return cc_(x)->_M_getword(pos); }

 private:
  static CEXP auto c_(std::bitset<N>& x) NE { return (std::_Base_bitset<Nw>*)(&x); }
  static CEXP auto cc_(std::bitset<N> CR x) NE { return (std::_Base_bitset<Nw> const*)(&x); }
};

}  // namespace tifa_libs

#endif