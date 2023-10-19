#ifndef TIFA_LIBS_STR_ORTHODOX_EX_SUFFIX_AUTOMATON
#define TIFA_LIBS_STR_ORTHODOX_EX_SUFFIX_AUTOMATON

#include "../util/util.hpp"

namespace tifa_libs::str {

template <u32 SZ = 26>
class orthodox_ex_suffix_automaton {
  // super root is 0
  struct YYZ {
    tifa_libs::u32 len, link;
    std::array<u32, SZ> nex{};
  };

 public:
  u32 sz;
  vec<YYZ> st;
  orthodox_ex_suffix_automaton() : sz(1) {
    st.push_back(YYZ()), st[0].len = 0, st[0].link = -1;
  }
  u32 extend(u32 last, char c) {
    u32 cur = st[last].nex[c];
    if (st[cur].len) return cur;
    st[cur].len = st[last].len + 1;
    u32 p = st[last].link;

    while (p != -1 && !st[p].nex[c]) {
      st[p].nex[c] = cur;
      p = st[p].link;
    }
    if (p == -1) st[cur].link = 0;
    else {
      u32 q = st[p].nex[c];
      if (st[p].len + 1 == st[q].len) st[cur].link = q;
      else {
        u32 clone = sz++;
        st.push_back(YYZ());
        for (auto [x, y] : st[q].nex)
          if (st[y].len) st[clone].nex[x] = y;

        st[clone].len = st[p].len + 1;
        st[clone].link = st[q].link;

        while (p != -1 && st[p].nex[c] == q) {
          st[p].nex[c] = clone;
          p = st[p].link;
        }
        st[q].link = st[cur].link = clone;
      }
    }
    return cur;
  }
  void insert(std::string s) {
    u32 u = 0;
    for (auto c : s) {
      if (!st[u].nex[c]) st[u].nex[c] = sz++, st.push_back(YYZ());
      u = st[u].nex[c];
    }
  }
  void build() {
    std::queue<std::pair<u32, char>> q;
    for (auto [x, y] : st[0].nex) q.push({0, x});
    while (q.size()) {
      auto [last, c] = q.front();
      q.pop();
      last = extend(last, c);
      for (auto [x, y] : st[last].nex) q.push({last, x});
    }
  }
};

}  // namespace tifa_libs::str

#endif