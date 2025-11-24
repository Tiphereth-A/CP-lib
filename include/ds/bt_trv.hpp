#ifndef TIFALIBS_DS_BT_TRV
#define TIFALIBS_DS_BT_TRV

#include "../util/traits_ds.hpp"

namespace tifa_libs::ds {

template <tp2_ds_c pointer, class F>
requires requires(pointer p, F&& f) { f(p); }
CEXP void pre_order(pointer p, F&& f) NE {
  if (p) f(p), pre_order(p->ch[0], std::forward<F>(f)), pre_order(p->ch[1], std::forward<F>(f));
}
template <tp2_ds_c pointer, class F>
requires requires(pointer p, F f) { f(p); }
CEXP void in_order(pointer p, F&& f) NE {
  if (p) in_order(p->ch[0], std::forward<F>(f)), f(p), in_order(p->ch[1], std::forward<F>(f));
}
template <tp2_ds_c pointer, class F>
requires requires(pointer p, F f) { f(p); }
CEXP void post_order(pointer p, F&& f) NE {
  if (p) post_order(p->ch[0], std::forward<F>(f)), post_order(p->ch[1], std::forward<F>(f)), f(p);
}
template <tp_ds_c pointer, class F>
requires requires(pointer p, u32 level, F f) { f(p, level); }
CEXP void level_order(pointer p, F&& f) NE {
  if (!p) return;
  u32 level = 0;
  std::queue<pointer> q({p});
  while (!q.empty()) {
    flt_ (u32, i, 0, (u32)q.size()) {
      auto now = q.front();
      q.pop(), f(now, level);
      for (auto&& s : now->ch) q.push(s);
    }
    ++level;
  }
}
template <tp_ds_c pointer, class Alloc>
CEXP void dealloc_subtree(pointer p, Alloc& alloc) NE {
  if (!p) return;
  for (auto&& s : p->ch) dealloc_subtree(s, alloc);
  alloc.deallocate(p, 1);
}

template <tp_ds_c pointer>
CEXP pointer most(pointer p, bool dir) NE {
  if (!p) return nullptr;
  while (p->ch[dir]) p = p->ch[dir];
  return p;
}
template <tp2_ds_c pointer>
CEXP auto leftmost(pointer p) NE { return most(p, 0); }
template <tp2_ds_c pointer>
CEXP auto rightmost(pointer p) NE { return most(p, 1); }

}  // namespace tifa_libs::ds

#endif