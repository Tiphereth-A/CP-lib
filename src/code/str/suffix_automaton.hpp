#ifndef TIFA_LIBS_STR_SUFFIX_AUTOMATON
#define TIFA_LIBS_STR_SUFFIX_AUTOMATON

#include "../util/util.hpp"

namespace tifa_libs::str {

class suffix_automaton {
  // super root is 0
  size_t last;
  struct YYZ {
    tifa_libs::i32 len, link;
    std::map<char, tifa_libs::i32> nex;
    tifa_libs::i64 sz;
    tifa_libs::i32 times;
  };

 public:
  size_t sz;
  vec<YYZ> st;
  suffix_automaton(size_t n) : last(0), sz(1), st(n * 2) {
    assert(n);
    st[0].len = 0, st[0].link = -1;
  }
  void extend(char c) {
    i32 cur = sz++;
    st[cur].len = st[last].len + 1;
    st[cur].times = 1;
    i32 p = last;

    while (p != -1 && !st[p].nex[c]) {
      st[p].nex[c] = cur;
      p = st[p].link;
    }
    if (p == -1) st[cur].link = 0;
    else {
      i32 q = st[p].nex[c];
      if (st[p].len + 1 == st[q].len) st[cur].link = q;
      else {
        i32 clone = sz++;
        st[clone].nex = st[q].nex;
        
        st[clone].len = st[p].len + 1;
        st[clone].link = st[q].link;

        while (p != -1 && st[p].nex[c] == q) {
          st[p].nex[c] = clone;
          p = st[p].link;
        }
        st[q].link = st[cur].link = clone;
      }
    }
    last = cur;
  }
  vvec<size_t> e;
  void buildparenttree() {
    e = vvec<size_t>(sz);
    auto add = [&](size_t u, size_t v) { e[u].push_back(v); };
    for (size_t i = 1; i < sz; ++i) add(size_t(st[i].link), i);
  }
  void gettimes(size_t u = 0) {
    for (auto v : e[u]) gettimes(v), st[u].times += st[v].times;
  }
  void getsz(size_t u = 0) {
    st[u].sz = 1;
    for (auto [c, v] : st[u].nex) {
      if (!st[v].sz) getsz(v);
      st[u].sz += st[v].sz;
    }
  }
};

}  // namespace tifa_libs::str

#endif