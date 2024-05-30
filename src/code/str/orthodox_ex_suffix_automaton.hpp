#ifndef TIFALIBS_STR_ORTHODOX_EX_SUFFIX_AUTOMATON
#define TIFALIBS_STR_ORTHODOX_EX_SUFFIX_AUTOMATON

#include "../util/util.hpp"

namespace tifa_libs::str {

template <u32 SZ = 26, u32 BASE = u32('a')>
class orthodox_ex_suffix_automaton {
  // super root is 0
  struct TIFA {
    u32 len, link;
    arr<u32, SZ> nex{};
  };

 public:
  u32 sz;
  vec<TIFA> st;

  explicit CEXP orthodox_ex_suffix_automaton() : sz(1) { st.push_back(TIFA()), st[0].len = 0, st[0].link = -1u; }

  CEXP u32 extend(u32 last, u32 c) {
    u32 cur = st[last].nex[c];
    if (st[cur].len) return cur;
    st[cur].len = st[last].len + 1;
    u32 p = st[last].link;

    while (~p && !st[p].nex[c]) st[p].nex[c] = cur, p = st[p].link;
    if (!~p) st[cur].link = 0;
    else {
      u32 q = st[p].nex[c];
      if (st[p].len + 1 == st[q].len) st[cur].link = q;
      else {
        u32 clone = sz++;
        st.push_back(TIFA());
        flt_ (u32, i, 0, SZ)
          if (st[q].nex[i] && st[st[q].nex[i]].len) st[clone].nex[i] = st[q].nex[i];
        st[clone].len = st[p].len + 1, st[clone].link = st[q].link;
        while (~p && st[p].nex[c] == q) st[p].nex[c] = clone, p = st[p].link;
        st[q].link = st[cur].link = clone;
      }
    }
    return cur;
  }
  CEXP void insert(strnv s) {
    u32 u = 0;
    for (auto cc : s) {
      const u32 c = cc - BASE;
      if (!st[u].nex[c]) st[u].nex[c] = sz++, st.push_back(TIFA());
      u = st[u].nex[c];
    }
  }
  void build() {
    std::queue<std::pair<u32, char>> q;
    flt_ (u32, i, 0, SZ)
      if (st[0].nex[i]) q.push({0, i});
    while (q.size()) {
      auto [last, c] = q.front();
      q.pop(), last = extend(last, c);
      flt_ (u32, i, 0, SZ)
        if (st[last].nex[i]) q.push({last, i});
    }
  }
};

}  // namespace tifa_libs::str

#endif