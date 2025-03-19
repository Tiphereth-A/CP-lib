#ifndef TIFALIBS_DS_DEPQ
#define TIFALIBS_DS_DEPQ

#include "../util/alias_num.hpp"

namespace tifa_libs::ds {

// Copyright Malte Skarupke 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See http://www.boost.org/LICENSE_1_0.txt)
namespace depq_impl_ {
CEXP int hib_(u32 i) NE { return std::bit_width(i) - 1; }
CEXP bool is_minni(u32 l) NE { return (hib_(l) & 1) == 0; }
CEXP bool is_mini(u32 i) NE { return is_minni(i + 1); }
CEXP u32 gpidx_(u32 i) NE { return (i - 3) / 4; }
CEXP u32 pidx_(u32 i) NE { return (i - 1) / 2; }
CEXP u32 ch1idx_(u32 i) NE { return (i * 2) + 1; }
CEXP u32 gchls_idx_(u32 i) NE { return (i * 4) + 6; }
template <class I, class C>
CEXP u32 s_dec_(I b, u32 l, u32 ch1, u32 gch1, C &&c) NE {
  u32 ch2 = ch1 + 1;
  if (gch1 >= l) return ch1 + (ch2 != l && c(b[ch2], b[ch1]));
  u32 gch2 = gch1 + 1;
  if (gch2 == l) return c(b[gch1], b[ch2]) ? gch1 : ch2;
  u32 gchm = gch1 + !!c(b[gch2], b[gch1]), gch3 = gch2 + 1;
  if (gch3 == l) return c(b[gchm], b[ch2]) ? gchm : ch2;
  return c(b[gchm], b[gch3]) ? gchm : gch3;
}
template <class I, class C>
CEXP u32 l_dec_(I b, u32 l, u32 ch1, u32 gch1, C &&c) NE {
  u32 ch2 = ch1 + 1;
  if (gch1 >= l) return ch1 + (ch2 != l && c(b[ch1], b[ch2]));
  u32 gch2 = gch1 + 1;
  if (gch2 == l) return c(b[ch2], b[gch1]) ? gch1 : ch2;
  u32 gchm = gch1 + !!c(b[gch1], b[gch2]), gch3 = gch2 + 1;
  if (gch3 == l) return c(b[ch2], b[gchm]) ? gchm : ch2;
  return c(b[gchm], b[gch3]) ? gch3 : gchm;
}
template <class I, class C>
CEXP void pdmin_(I b, TPN std::iterator_traits<I>::value_type v, u32 i, u32 l, C &&c) NE {
  for (;;)
    if (u32 gch_lst = gchls_idx_(i); gch_lst < l) {
      auto it = b + gch_lst;
      u32 h1m = gch_lst - 2 - !!c(it[-3], it[-2]),
          h2m = gch_lst - !!c(it[-1], it[0]),
          s = c(b[h2m], b[h1m]) ? h2m : h1m;
      if (!c(b[s], v)) break;
      b[i] = std::move(b[s]);
      if (u32 p = pidx_(i = s); c(b[p], v)) swap(b[p], v);
    } else {
      u32 ch1 = ch1idx_(i);
      if (ch1 >= l) break;
      u32 gch1 = gch_lst - 3, s = s_dec_(b, l, ch1, gch1, c);
      if (!c(b[s], v)) break;
      if (b[i] = std::move(b[s]); (i = s) < gch1) break;
      if (u32 p = pidx_(i); c(b[p], v)) b[i] = std::move(b[p]), i = p;
      break;
    }
  b[i] = std::move(v);
}
template <class I, class C>
CEXP void pdmin_1ch_(I b, u32 i, C &&c) NE {
  if (u32 ch = ch1idx_(i); c(b[ch], b[i])) swap(b[i], b[ch]);
}
template <class I, class C>
CEXP void pdmin_1lvl_(I b, u32 i, C &&c) NE {
  if (u32 ch1 = ch1idx_(i), chs = ch1 + !!c(b[ch1 + 1], b[ch1]); c(b[chs], b[i])) swap(b[i], b[chs]);
}
template <class I, class C>
CEXP void pdmax_(I b, TPN std::iterator_traits<I>::value_type v, u32 i, u32 l, C &&c) NE {
  for (;;)
    if (u32 gch_lst = gchls_idx_(i); gch_lst < l) {
      auto it = b + gch_lst;
      u32 h1m = gch_lst - 2 - !!c(it[-2], it[-3]),
          h2m = gch_lst - !!c(it[0], it[-1]),
          s = c(b[h1m], b[h2m]) ? h2m : h1m;
      if (!c(v, b[s])) break;
      b[i] = std::move(b[s]);
      if (u32 p = pidx_(i = s); c(v, b[p])) swap(b[p], v);
    } else {
      u32 ch1 = ch1idx_(i);
      if (ch1 >= l) break;
      u32 gch1 = gch_lst - 3, s = l_dec_(b, l, ch1, gch1, c);
      if (!c(v, b[s])) break;
      if (b[i] = std::move(b[s]); (i = s) < gch1) break;
      if (u32 p = pidx_(i); c(v, b[p])) b[i] = std::move(b[p]), i = p;
      break;
    }
  b[i] = std::move(v);
}
template <class I, class C>
CEXP void pdmax_1ch_(I b, u32 i, C &&c) NE {
  if (u32 ch = ch1idx_(i); c(b[i], b[ch])) swap(b[i], b[ch]);
}
template <class I, class C>
CEXP void pdmax_1lvl_(I b, u32 i, C &&c) NE {
  u32 ch1 = ch1idx_(i), chb = ch1 + !!c(b[ch1], b[ch1 + 1]);
  if (c(b[i], b[chb])) swap(b[i], b[chb]);
}
}  // namespace depq_impl_

template <class I, class C = std::less<>>
CEXP bool is_minmax_heap(I begin, I end, C &&comp = C{}) NE {
  u32 l = u32(end - begin);
  auto f = [](u32 i, auto cf) NE {
    u32 ch1 = depq_impl_::ch1idx_(i), ch2 = ch1 + 1,
        gch1 = depq_impl_::ch1idx_(ch1),
        gch2 = gch1 + 1,
        gch3 = depq_impl_::ch1idx_(ch2),
        gch4 = gch3 + 1;
    return cf(ch1) && cf(ch2) && cf(gch1) && cf(gch2) && cf(gch3) && cf(gch4);
  };
  flt_ (u32, i, 0, l)
    if (depq_impl_::is_mini(i)) {
      if (!f(i, [&](u32 c) { return c >= l || !comp(begin[c], begin[i]); })) return false;
    } else if (!f(i, [&](u32 c) { return c >= l || !comp(begin[i], begin[c]); })) return false;
  return true;
}
template <common_range R, class C = std::less<>>
CEXP bool is_minmax_heap(R CR r, C &&comp = C{}) NE { return is_minmax_heap(r.begin(), r.end(), std::forward<C>(comp)); }
template <class I, class C = std::less<>>
void push_minmax_heap(I begin, I end, C &&comp = C{}) NE {
  u32 len = u32(end - begin), idx = len - 1, parent = depq_impl_::pidx_(idx);
  TPN std::iterator_traits<I>::value_type value = std::move(end[-1]);
  if (depq_impl_::is_minni(len)) {
    if (idx == 0) static_cast<void>(0);
    else if (comp(begin[parent], value)) {
      begin[idx] = std::move(begin[parent]), idx = parent;
      goto push_up_max;
    } else {
      for (;;) {
        if (u32 gp = depq_impl_::gpidx_(idx); comp(value, begin[gp])) {
          begin[idx] = std::move(begin[gp]);
          idx = gp;
        } else break;
      push_up_min:
        if (!idx) break;
      }
    }
  } else if (comp(value, begin[parent])) {
    begin[idx] = std::move(begin[parent]), idx = parent;
    goto push_up_min;
  } else
  push_up_max:
    while (idx > 2)
      if (u32 gp = depq_impl_::gpidx_(idx); comp(begin[gp], value)) {
        begin[idx] = std::move(begin[gp]);
        idx = gp;
      } else break;
  begin[idx] = std::move(value);
}
template <common_range R, class C = std::less<>>
CEXP bool push_minmax_heap(R CR r, C &&comp = C{}) NE { return push_minmax_heap(r.begin(), r.end(), std::forward<C>(comp)); }
template <class I, class C = std::less<>>
CEXP void pop_minmax_heap_min(I begin, I end, C &&comp = C{}) NE {
  u32 l = u32(end - begin) - 1;
  if (l == 0) return;
  depq_impl_::pdmin_(begin, std::exchange(end[-1], std::move(begin[0])), 0, l, comp);
}
template <common_range R, class C = std::less<>>
CEXP bool pop_minmax_heap_min(R CR r, C &&comp = C{}) NE { return pop_minmax_heap_min(r.begin(), r.end(), std::forward<C>(comp)); }
template <class I, class C = std::less<>>
CEXP void pop_minmax_heap_max(I begin, I end, C &&comp = C{}) NE {
  u32 l = u32(end - begin) - 1;
  if (l <= 1) return;
  u32 idx = 1 + !!comp(begin[1], begin[2]);
  depq_impl_::pdmax_(begin, std::exchange(end[-1], std::move(begin[idx])), idx, l, std::forward<C>(comp));
}
template <common_range R, class C = std::less<>>
CEXP bool pop_minmax_heap_max(R CR r, C &&comp = C{}) NE { return pop_minmax_heap_max(r.begin(), r.end(), std::forward<C>(comp)); }
template <class I, class C = std::less<>>
CEXP void make_minmax_heap(I begin, I end, C &&comp = C{}) NE {
  u32 l = u32(end - begin), idx = l / 2;
  if (idx == 0) return;
  if ((l & 1) == 0) {
    if (--idx; depq_impl_::is_mini(idx)) depq_impl_::pdmin_1ch_(begin, idx, comp);
    else depq_impl_::pdmax_1ch_(begin, idx, comp);
    if (idx == 0) return;
  }
  if (l != 4) {
    for (u32 lidx_ngch = l / 4;;) {
      int hib = depq_impl_::hib_(idx);
      u32 loplim = max(lidx_ngch, (1_u32 << hib) - 1);
      if (--idx; hib & 1)
        for (;; --idx) {
          if (depq_impl_::pdmax_1lvl_(begin, idx, comp); idx == loplim) break;
        }
      else {
        for (;; --idx) {
          if (depq_impl_::pdmin_1lvl_(begin, idx, comp); idx == loplim) break;
        }
        if (idx == 0) return;
      }
      if (idx == lidx_ngch) break;
    }
  }
  int hib = depq_impl_::hib_(idx);
  switch (u32 loplim = (1_u32 << hib) - 1; hib & 1)
    for (;;) {
      case 0:
        for (;;) {
          --idx;
          depq_impl_::pdmin_(begin, std::move(begin[idx]), idx, l, comp);
          if (idx == loplim) break;
        }
        if (idx == 0) return;
        loplim /= 2;
        [[fallthrough]];
      case 1:
        for (;;) {
          --idx;
          depq_impl_::pdmax_(begin, std::move(begin[idx]), idx, l, comp);
          if (idx == loplim) break;
        }
        loplim /= 2;
    }
}
template <common_range R, class C = std::less<>>
CEXP bool make_minmax_heap(R CR r, C &&comp = C{}) NE { return make_minmax_heap(r.begin(), r.end(), std::forward<C>(comp)); }

}  // namespace tifa_libs::ds

#endif