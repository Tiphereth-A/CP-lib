#ifndef TIFALIBS_DS_CARTESIAN_TREE
#define TIFALIBS_DS_CARTESIAN_TREE

#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T>
class cartesian_tree {
  struct YYZ {
    u32 fa;
    std::array<u32, 2> son{-1u, -1u};
  };

  constexpr void build(vec<T> const& y) {
    vecu s(y.size() + 1);
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

  explicit constexpr cartesian_tree(vec<T> const& y) : root(), t(y.size()) { build(y); }
};

}  // namespace tifa_libs::ds

#endif