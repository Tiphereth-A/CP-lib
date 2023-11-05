#ifndef TIFA_LIBS_DS_CARTESIAN_TREE
#define TIFA_LIBS_DS_CARTESIAN_TREE

#include "../util/util.hpp"

namespace tifa_libs::ds {

template <typename T>
class cartesian_tree {
  struct YYZ {
    u32 fa;
    std::array<u32, 2> son{-1u, -1u};
  };
  void build(const vec<T>& y) {
    vec<u32> s(y.size() + 1);
    u32 top = 0;
    for (u32 i = 0; i < y.size(); i++) {
      u32 k = top;
      while (k && y[s[k]] > y[i]) --k;
      if (k) t[s[k]].son[1] = i, t[i].fa = s[k];
      if (k < top) t[i].son[0] = s[k + 1], t[s[k + 1]].fa = i;
      s[top = ++k] = i;
    }
    t[root = s[1]].fa = s[1];
  }

 public:
  u32 root;
  vec<YYZ> t;
  cartesian_tree(const vec<T>& y) : root(), t(y.size()) { build(y); }
};

}  // namespace tifa_libs::ds

#endif