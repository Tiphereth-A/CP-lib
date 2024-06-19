#ifndef TIFALIBS_DS_CARTESIAN_TREE
#define TIFALIBS_DS_CARTESIAN_TREE

#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T>
class cartesian_tree {
  struct TIFA {
    u32 fa;
    arr<u32, 2> son{-1u, -1u};
  };

 public:
  u32 root;
  vec<TIFA> t;

  CEXPE cartesian_tree(vec<T> CR y) : root(), t(y.size()) {
    vecu s(y.size() + 1);
    u32 top = 0;
    flt_ (u32, i, 0, (u32)y.size()) {
      u32 k = top;
      while (k && y[s[k]] > y[i]) --k;
      if (k) t[s[k]].son[1] = i, t[i].fa = s[k];
      if (k < top) t[i].son[0] = s[k + 1], t[s[k + 1]].fa = i;
      s[top = ++k] = i;
    }
    t[root = s[1]].fa = s[1];
  }
};

}  // namespace tifa_libs::ds

#endif