#ifndef TIFALIBS_DS_TRIE01
#define TIFALIBS_DS_TRIE01

#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T = i32, bool persistent = false>
struct trie01 {
  struct TIFA {
    u32 nxt[2];
    T val;
    vecu idxs;
    TIFA() : nxt{0, 0}, val(0), idxs() {}
  };

  const i32 MAX_DEP;
  vec<TIFA> data;
  u32 root;

  CEXPE trie01(i32 max_depth = 32) : MAX_DEP(max_depth), data(2), root(1) {
    assert(max_depth > 0);
    data.reserve(1_u64 << (max_depth / 2));
  }

  CEXP void add(u64 bit, T val = 1, int idx = -1, u64 xv = 0) { root = add_(root, bit, idx, MAX_DEP, val, xv); }
  CEXP u32 find(u64 bit, u64 xv = 0) const { return find_(root, bit, MAX_DEP, xv); }
  CEXP auto kth_element(T k, u64 xv = 0) const {
    assert(0 <= k && k < data[root].val);
    return kth_(root, k, MAX_DEP, xv);
  }
  CEXP T count_less(u64 bit, u64 xv = 0) const { return cntle_(root, bit, MAX_DEP, xv); }

 private:
  CEXP u32 add_(u32 t, u64 bit, int idx, int dep, T x, u64 xv, bool need = true) {
    if CEXP (persistent)
      if (need) t = (u32)data.size(), data.emplace_back();
    if (!~dep) {
      if (data[t].val += x; idx >= 0) data[t].idxs.push_back((u32)idx);
    } else {
      if (auto &_ = data[t].nxt[(xv ^ bit) >> dep & 1]; !_) _ = (u32)data.size(), data.emplace_back(), need = false;
      data[t].nxt[(xv ^ bit) >> dep & 1] = add_(data[t].nxt[(xv ^ bit) >> dep & 1], bit, idx, dep - 1, x, xv, need), data[t].val += x;
    }
    return t;
  }
  CEXP u32 find_(u32 t, u64 bit, int dep, u64 xv) const {
    if (!~dep) return t;
    const auto to = data[t].nxt[(xv ^ bit) >> dep & 1];
    return to ? find_(to, bit, dep - 1, xv) : 0;
  }
  CEXP std::pair<u64, u32> kth_(u32 t, T k, int idx, u64 xv) const {
    if (!~idx) return {0, t};
    const bool f = xv >> idx & 1;
    if (auto _ = data[t].nxt[f]; (_ ? data[_].val : 0) <= k) {
      auto ret = kth_(data[t].nxt[f ^ 1], k - (_ ? data[_].val : 0), idx - 1, xv);
      ret.first |= 1_u64 << idx;
      return ret;
    } else return kth_(_, k, idx - 1, xv);
  }
  CEXP T cntle_(u32 t, u64 bit, int idx, u64 xv) const {
    if (!~idx) return 0;
    T ret = 0;
    if (const bool f = xv >> idx & 1; (bit >> idx & 1) && data[t].nxt[f]) ret += data[data[t].nxt[f]].val;
    if (auto _ = data[t].nxt[(xv ^ bit) >> idx & 1]; _) ret += cntle_(_, bit, idx - 1, xv);
    return ret;
  }
};

}  // namespace tifa_libs::ds

#endif