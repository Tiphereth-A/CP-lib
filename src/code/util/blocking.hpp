#ifndef TIFALIBS_UTIL_BLOCKING
#define TIFALIBS_UTIL_BLOCKING

#include "util.hpp"

namespace tifa_libs {

template <class T>
class blocking {
  const u32 bsz;
  vec<T> dt, bs;

  constexpr auto block_l(u32 id) { return dt.begin() + std::min((u32)dt.size(), id * bsz); }

 public:
  // @param block_func init function for block: block_func(block, data.begin() + xl, data.begin() + xr); change value of block with range [xl, xr)
  template <class FB>
  requires requires(FB f) {
    f(bs[0], dt.begin(), dt.end());
  }
  constexpr blocking(u32 block_size, vec<T> const& data, FB&& block_func) : bsz(block_size), dt(data), bs((data.size() + block_size - 1) / block_size) {
    assert(block_size && block_size <= data.size());
    for (u32 i = 0; i < bs.size(); ++i) block_func(bs[i], block_l(i), block_l(i + 1));
  }
  constexpr vec<T> const& data() const { return dt; }

  //! range: [l, r)
  // @param upd update function for single element: upd(block, data.begin() + xl, data.begin() + xr); update data in [xl, xr), change value of block
  // @param updb update function for block: updb(block, data.begin() + xl, data.begin() + xr); change value of block with range [xl, xr)
  template <class FD, class FDB>
  requires requires(FD upd, FDB updb) {
    upd(bs[0], dt.begin(), dt.end());
    updb(bs[0], dt.begin(), dt.end());
  }
  constexpr void run(u32 l, u32 r, FD&& upd, FDB&& updb) {
    assert(l < r);
    u32 bl = (l + bsz - 1) / bsz, br = (r + bsz - 1) / bsz;
    for (u32 i = bl; i < br; ++i) updb(bs[i], block_l(i), block_l(i + 1));
    if (r <= bl * bsz) {
      if (bl) upd(bs[bl - 1], dt.begin() + l, dt.begin() + r);
    } else {
      if (l < bl * bsz) upd(bs[bl - 1], dt.begin() + l, block_l(bl));
      if (br * bsz < r) upd(bs[br + 1], block_l(br), dt.begin() + r);
    }
  }
};

}  // namespace tifa_libs

#endif