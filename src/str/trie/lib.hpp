#pragma once

#include "../../util/alias/others/lib.hpp"

namespace tifa_libs {

template <chr BGNCH = 'a', chr ENDCH = 'z' + 1>
class trie {
  struct TIFA {
    arr<u32, ENDCH - BGNCH> nxt{};
    bool end{false};
  };

  vec<TIFA> data;
  u32 sz{0};

 public:
  CEXP trie() NE : data(1) {}

  CEXP void insert(strnv str) NE {
    u32 p = 0;
    for (u32 i = 0, c; i < str.size(); ++i) {
      if (!data[p].nxt[c = str[i] - BGNCH]) data[p].nxt[c] = data.size(), data.emplace_back();
      p = data[p].nxt[c];
    }
    sz += !data[p].end, data[p].end = true;
  }
  ND CEXP u32 size() CNE { return sz; }
  ND CEXP u32 node_size() CNE { return (u32)data.size(); }
  ND CEXP bool query(strnv str) CNE {
    u32 p = 0;
    for (u32 i = 0, c; i < str.size(); ++i) {
      if (!data[p].nxt[c = str[i] - BGNCH]) return false;
      p = data[p].nxt[c];
    }
    return data[p].end;
  }
};

}  // namespace tifa_libs
