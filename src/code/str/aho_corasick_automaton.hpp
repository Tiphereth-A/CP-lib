#ifndef TIFA_LIBS_STR_AHO_CORASICK_AUTOMATON
#define TIFA_LIBS_STR_AHO_CORASICK_AUTOMATON

#include "../util/util.hpp"

namespace tifa_libs::str {

template <u32 SZ = 26, u32 BASE = u32('a')>
class aho_corasick_automaton {
  // super root is 0
  struct YYZ {
    std::array<u32, SZ> nex{};
    u32 fail, tot;
    vec<u32> end;
  };

 public:
  vec<YYZ> t;
  u32 sz;
  aho_corasick_automaton() : t(1), sz(1) {}
  void insert(std::string s, u32 id = -1u) {
    u32 u = 0;
    ++t[u].tot;
    for (auto c : s) {
      u32 a = u32(c) - BASE;
      if (!t[u].nex[a]) t[u].nex[a] = sz++, t.push_back(YYZ());
      u = t[u].nex[a], ++t[u].tot;
    }
    if (id != -1u) t[u].end.push_back(id);
  }
  void getfail() {
    std::queue<u32> q;
    for (u32 i = 0; i < SZ; ++i)
      if (t[0].nex[i]) q.push(t[0].nex[i]);
    while (!q.empty()) {
      u32 u = q.front();
      q.pop();
      for (u32 i = 0; i < SZ; ++i) {
        if (t[u].nex[i]) t[t[u].nex[i]].fail = t[t[u].fail].nex[i], q.push(t[u].nex[i]);
        else t[u].nex[i] = t[t[u].fail].nex[i];
      }
    }
  }
  void build(vec<std::string> s_) {
    for (u32 i = 0; i < s_.size(); ++i) insert(s_[i], i);
    getfail();
  }
};
}  // namespace tifa_libs::str

#endif