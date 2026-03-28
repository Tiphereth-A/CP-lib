#pragma once

#include "../../../bit/lowbit/lib.hpp"
#include "../../../util/alias/others/lib.hpp"

namespace tifa_libs {

template <class T, class F>
class rmq_linear {
  F cmp;  // std::less<> -> min, std::greater<> -> max
  u32 n;
  vec<T> a;
  vecu in, asc, head;
  CEXP u32 idx(u32 l, u32 r) CNE {
    if (u32 j = in[l] ^ in[r]) {
      if (j = asc[l] & asc[r] & -std::bit_floor(j); auto k = std::bit_floor(asc[l] ^ j)) l = head[(in[l] & -k) | k];
      if (auto k = std::bit_floor(asc[r] ^ j)) r = head[(in[r] & -k) | k];
    }
    retif_((cmp(a[l], a[r])), l, r);
  }

 public:
  CEXP rmq_linear(spn<T> a) NE : cmp{}, n{(u32)a.size()}, a{a.begin(), a.end()}, in(n), asc(n), head(n + 1) {
    vecu st{-1_u32};
    flt_ (u32, i, 0, n + 1) {
      u32 prev = 0;
      while (st.size() > 1 && (i == n || !cmp(a[st.back()], a[i]))) {
        head[prev] = st.back();
        auto j = st[st.size() - 2] + 1, k = std::bit_floor(i ^ j);
        in[st.back()] = prev = i & -k, asc[j] |= k, st.pop_back();
      }
      st.push_back(head[prev] = i);
    }
    flt_ (u32, i, 1, n) asc[i] = (asc[i] | asc[i - 1]) & -lowbit(in[i]);
  }
  //! [l, r]
  CEXP T query(u32 l, u32 r) CNE { return a[idx(l, r)]; }
};

}  // namespace tifa_libs
