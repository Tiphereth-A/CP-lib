#ifndef TIFALIBS_STR_TRIE
#define TIFALIBS_STR_TRIE

#include "../util/util.hpp"

namespace tifa_libs::str {

template <char BGNCH = 'a', char ENDCH = 'z' + 1>
class Trie {
  struct YYZ {
    u32 nxt[ENDCH - BGNCH];
    bool end;
    YYZ() : nxt{}, end(false) {}
  };

  vec<YYZ> data;
  u32 sz;

 public:
  constexpr Trie() : data(1), sz(0) {}

  constexpr void insert(strnv str) {
    u32 p = 0;
    for (u32 i = 0, c; i < str.size(); ++i) {
      if (!data[p].nxt[c = str[i] - BGNCH]) data[p].nxt[c] = data.size(), data.emplace_back();
      p = data[p].nxt[c];
    }
    sz += !data[p].end, data[p].end = true;
  }
  constexpr u32 size() const { return sz; }
  constexpr u32 node_size() const { return (u32)data.size(); }
  constexpr bool query(strnv str) const {
    u32 p = 0;
    for (u32 i = 0, c; i < str.size(); ++i) {
      if (!data[p].nxt[c = str[i] - BGNCH]) return false;
      p = data[p].nxt[c];
    }
    return data[p].end;
  }
};

}  // namespace tifa_libs::str

#endif