#ifndef TIFALIBS_STR_AHO_CORASICK_AUTOMATON
#define TIFALIBS_STR_AHO_CORASICK_AUTOMATON

#include "../util/alias_others.hpp"

namespace tifa_libs::str {

template <u32 SZ = 26, u32 BASE = u32('a')>
class aho_corasick {
  // super root is 0
  struct TIFA {
    arr<u32, SZ> nex{};
    u32 fail, tot;
    vecu end;
  };

 public:
  vec<TIFA> t;
  u32 sz;

  CEXPE aho_corasick() NE : t(1), sz(1) {}

  CEXP void insert(strnv s, u32 id = -1u) NE {
    u32 u = 0;
    for (++t[u].tot; auto c : s) {
      u32 a = u32(c) - BASE;
      if (!t[u].nex[a]) t[u].nex[a] = sz++, t.push_back(TIFA());
      u = t[u].nex[a], ++t[u].tot;
    }
    if (~id) t[u].end.push_back(id);
  }
  void getfail() NE {
    std::queue<u32> q;
    flt_ (u32, i, 0, SZ)
      if (t[0].nex[i]) q.push(t[0].nex[i]);
    while (!q.empty()) {
      const u32 u = q.front();
      q.pop();
      flt_ (u32, i, 0, SZ)
        if (t[u].nex[i]) t[t[u].nex[i]].fail = t[t[u].fail].nex[i], q.push(t[u].nex[i]);
        else t[u].nex[i] = t[t[u].fail].nex[i];
    }
  }
  CEXP void build(spn<strn> s_) NE {
    flt_ (u32, i, 0, (u32)s_.size()) insert(s_[i], i);
    getfail();
  }
};
}  // namespace tifa_libs::str

#endif