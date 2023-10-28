#ifndef TIFA_LIBS_DS_FHQ_TREAP
#define TIFA_LIBS_DS_FHQ_TREAP

#include "../rand/gen.hpp"
#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T, bool recovery = false>
class fhq_treap {
  //!!! initial cnt = 1;
  struct YYZ {
    T val;
    usz sz, ls, rs;
    i32 rad;
    YYZ(T VAL = 0, usz SZ = 0, i32 RAD = 0, usz LS = 0, usz RS = 0) : val(VAL), sz(SZ), ls(LS), rs(RS), rad(RAD) {}
  };
  rand::Gen<std::uniform_int_distribution<i32>> gen;
  vec<YYZ> t;
  vec<usz> sta;
  usz cnt;
  usz newnode(T val) {
    usz ret;
    if (recovery && sta.size()) ret = *sta.rbegin(), sta.pop_back(), t[ret] = YYZ(val, 1, gen());
    else ret = ++cnt, t[ret] = YYZ(val, 1, gen());
    return ret;
  }
  constexpr void rm(usz u) { sta.push_back(u); }
  constexpr void update(usz u) { t[u].sz = t[t[u].ls].sz + t[t[u].rs].sz + 1; }

 public:
  usz root;
  explicit constexpr fhq_treap(usz MAX_N) : gen(), t(MAX_N + 1), sta(), cnt(0), root(0) {
    if (recovery) sta.reserve(MAX_N + 1);
  }
  void split(usz u, T k, usz& x, usz& y) {
    if (!u) x = y = 0;
    else {
      if (t[u].val <= k) x = u, split(t[u].rs, k, t[u].rs, y), update(x);
      else y = u, split(t[u].ls, k, x, t[y].ls), update(y);
    }
  }
  usz merge(usz x, usz y) {
    if (x && y) {
      if (t[x].rad <= t[y].rad) {
        t[x].rs = merge(t[x].rs, y), update(x);
        return x;
      } else {
        t[y].ls = merge(x, t[y].ls), update(y);
        return y;
      }
    } else return x + y;
  }
  void insert(T w) {
    usz x, y;
    split(root, w, x, y);
    root = merge(merge(x, newnode(w)), y);
  }
  void erase(T w) {
    usz x, y, z;
    split(root, w, x, y);
    split(x, w - 1, x, z);
    if (recovery) rm(z);
    z = merge(t[z].ls, t[z].rs);
    root = merge(merge(x, z), y);
  }
  usz w_que_rk(T w) {
    usz x, y, ret;
    split(root, w - 1, x, y);
    ret = t[x].sz + 1;
    root = merge(x, y);
    return ret;
  }
  T rk_que_w(usz u, usz k) {
    while (1) {
      if (t[t[u].ls].sz >= k) u = t[u].ls;
      else {
        if (t[t[u].ls].sz + 1 >= k) return t[u].val;
        k -= t[t[u].ls].sz + 1, u = t[u].rs;
      }
    }
  }
  T pre_w(T w) {
    usz x, y;
    T ret;
    split(root, w - 1, x, y);
    ret = rk_que_w(x, t[x].sz);
    root = merge(x, y);
    return ret;
  }
  T suf_w(T w) {
    usz x, y;
    T ret;
    split(root, w, x, y);
    ret = rk_que_w(y, 1);
    root = merge(x, y);
    return ret;
  }
};

}  // namespace tifa_libs::ds

#endif