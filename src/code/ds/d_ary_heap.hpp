#ifndef TIFALIBS_DS_D_ARY_HEAP
#define TIFALIBS_DS_D_ARY_HEAP

#include "../util/util.hpp"

namespace tifa_libs::ds {

// Copyright Malte Skarupke 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See http://www.boost.org/LICENSE_1_0.txt)
namespace d_ary_heap_impl_ {
template <int D>
CEXP u32 ch1idx_(u32 i) { return i * D + 1; }
template <int D>
CEXP u32 chls_idx_(u32 i) { return i * D + D; }
template <int D>
CEXP u32 gchls_idx_(u32 i) { return i * (D * D) + (D * D + D); }
template <int D>
CEXP u32 pidx_(u32 i) { return (i - 1) / D; }
template <int D>
CEXP u32 gpidx_(u32 i) { return (i - (D + 1)) / (D * D); }
template <int D>
CEXP u32 idx_ngch_(u32 l) { return gpidx_<D>(l - 1) + 1; }
template <int D, class I, class C>
CEXP I l_ch_(I it_ch1, C &&c) {
  if CEXP (D == 1) return it_ch1;
  else if CEXP (D == 2) return it_ch1 + !!c(it_ch1[0], it_ch1[1]);
  else {
    I hl1 = l_ch_<D / 2>(it_ch1, c), hl2 = l_ch_<D - D / 2>(it_ch1 + D / 2, c);
    return c(*hl1, *hl2) ? hl2 : hl1;
  }
}
template <int D, class I, class C>
CEXP I l_ch_(I it_ch1, int num_ch, C &&c) {
  if CEXP (D == 2) return it_ch1;
  else if CEXP (D == 3) {
    if (num_ch == 1) return it_ch1;
    return it_ch1 + !!c(it_ch1[0], it_ch1[1]);
  } else if CEXP (D == 4) {
    switch (num_ch) {
      case 1: return it_ch1;
      case 2: return it_ch1 + !!c(it_ch1[0], it_ch1[1]);
      default: I largest = it_ch1 + !!c(it_ch1[0], it_ch1[1]); return c(*largest, it_ch1[2]) ? it_ch1 + 2 : largest;
    }
  } else {
    switch (num_ch) {
      case 1: return it_ch1;
      case 2: return it_ch1 + !!c(it_ch1[0], it_ch1[1]);
      case 3: {
        I l = it_ch1 + !!c(it_ch1[0], it_ch1[1]);
        return c(*l, it_ch1[2]) ? it_ch1 + 2 : l;
      }
      case 4: {
        I hl1 = it_ch1 + !!c(it_ch1[0], it_ch1[1]), hl2 = it_ch1 + 2 + !!c(it_ch1[2], it_ch1[3]);
        return c(*hl1, *hl2) ? hl2 : hl1;
      }
      default:
        int h = num_ch / 2;
        I hl1 = l_ch_<D>(it_ch1, h, c), hl2 = l_ch_<D>(it_ch1 + h, num_ch - h, c);
        return c(*hl1, *hl2) ? hl2 : hl1;
    }
  }
}
}  // namespace d_ary_heap_impl_

template <int D, class I, class C = std::less<>>
CEXP void make_dary_heap(I begin, I end, C &&comp = C{}) {
  u32 len = u32(end - begin);
  if (len <= 1) return;
  u32 idx = (len - 2) / D;
  if (int num_ch_end = (len - 1) % D; num_ch_end) {
    if (I chl = d_ary_heap_impl_::l_ch_<D>(begin + d_ary_heap_impl_::ch1idx_<D>(idx), num_ch_end, comp); comp(begin[idx], *chl)) swap(begin[idx], *chl);
    if (idx == 0) return;
    --idx;
  }
  if (idx > 0)
    for (u32 lidx_ngcd = d_ary_heap_impl_::idx_ngch_<D>(len);;) {
      if (I ch = d_ary_heap_impl_::l_ch_<D>(begin + d_ary_heap_impl_::ch1idx_<D>(idx), comp); comp(begin[idx], *ch)) swap(begin[idx], *ch);
      if (idx-- == lidx_ngcd) break;
    }
  for (;; --idx) {
    TPN std::iterator_traits<I>::value_type value = std::move(begin[idx]);
    u32 mdidx = idx;
    for (;;) {
      u32 idx_ch = d_ary_heap_impl_::chls_idx_<D>(mdidx), idx_ch1 = idx_ch - (D - 1);
      I ch = begin;
      if (idx_ch < len) ch = d_ary_heap_impl_::l_ch_<D>(begin + idx_ch1, comp);
      else if (idx_ch1 >= len) break;
      else ch = d_ary_heap_impl_::l_ch_<D>(begin + idx_ch1, int(len - idx_ch1), comp);
      if (!comp(value, *ch)) break;
      begin[mdidx] = std::move(*ch), mdidx = u32(ch - begin);
    }
    if (begin[mdidx] = std::move(value); idx == 0) break;
  }
}
template <int D, class I, class C = std::less<>>
CEXP bool is_dary_heap(I begin, I end, C &&comp = C{}) {
  flt_ (u32, i, 1, u32(end - begin))
    if (u32 p = d_ary_heap_impl_::pidx_<D>(i); comp(begin[p], begin[i])) return false;
  return true;
}
template <int D, class I, class C = std::less<>>
CEXP void push_dary_heap(I begin, I end, C &&comp = C{}) {
  TPN std::iterator_traits<I>::value_type val = std::move(end[-1]);
  u32 idx = u32(end - begin) - 1;
  while (idx > 0) {
    u32 p = d_ary_heap_impl_::pidx_<D>(idx);
    if (!comp(begin[p], val)) break;
    begin[idx] = std::move(begin[p]), idx = p;
  }
  begin[idx] = std::move(val);
}
template <int D, class I, class C = std::less<>>
CEXP void pop_dary_heap(I begin, I end, C &&comp = C{}) {
  u32 len = u32(end - begin) - 1;
  TPN std::iterator_traits<I>::value_type val = std::move(end[-1]);
  u32 idx = 0;
  for (end[-1] = std::move(begin[0]);;) {
    if (u32 chls = d_ary_heap_impl_::chls_idx_<D>(idx), ch1 = chls - (D - 1); chls < len) {
      I ch = d_ary_heap_impl_::l_ch_<D>(begin + ch1, comp);
      if (!comp(val, *ch)) break;
      begin[idx] = std::move(*ch), idx = u32(ch - begin);
    } else if (ch1 < len) {
      if (I ch = d_ary_heap_impl_::l_ch_<D>(begin + ch1, int(len - ch1), comp); comp(val, *ch)) begin[idx] = std::move(*ch), idx = u32(ch - begin);
      break;
    } else break;
  }
  begin[idx] = std::move(val);
}

}  // namespace tifa_libs::ds

#endif