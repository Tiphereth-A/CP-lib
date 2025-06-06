#ifndef TIFALIBS_STR_EX_SUFFIX_AUTOMATON
#define TIFALIBS_STR_EX_SUFFIX_AUTOMATON

#include "../util/alias_others.hpp"

namespace tifa_libs::str {

template <u32 SZ = 26>
class ex_suffix_automaton {
  // super root is 0
  struct TIFA {
    u32 len, link;
    arr<u32, SZ> nex{};
  };

 public:
  u32 sz;
  vec<TIFA> st;

  CEXPE ex_suffix_automaton() NE : sz(1), st(1) { st[0].len = 0, st[0].link = -1_u32; }

  CEXP u32 extend(u32 last, u32 c) NE {
    if (st[last].nex[c]) {
      u32 p = last, q = st[p].nex[c];
      if (st[p].len + 1 == st[q].len) return q;
      else {
        u32 clone = sz++;
        st.push_back(TIFA()), st[clone].len = st[p].len + 1, st[clone].link = st[q].link, st[clone].nex = st[q].nex;
        while (~p && st[p].nex[c] == q) st[p].nex[c] = clone, p = st[p].link;
        return st[q].link = clone;
      }
    }
    u32 cur = sz++, p = last;
    st.push_back(TIFA()), st[cur].len = st[last].len + 1;
    while (~p && !st[p].nex[c]) st[p].nex[c] = cur, p = st[p].link;
    if (!~p) st[cur].link = 0;
    else {
      u32 q = st[p].nex[c];
      if (st[p].len + 1 == st[q].len) st[cur].link = q;
      else {
        u32 clone = sz++;
        st.push_back(TIFA()), st[clone].len = st[p].len + 1, st[clone].link = st[q].link, st[clone].nex = st[q].nex;
        while (~p && st[p].nex[c] == q) st[p].nex[c] = clone, p = st[p].link;
        st[q].link = st[cur].link = clone;
      }
    }
    return cur;
  }
};

}  // namespace tifa_libs::str

#endif