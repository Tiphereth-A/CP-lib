#ifndef TIFALIBS_DS_FHQ_TREAP_W
#define TIFALIBS_DS_FHQ_TREAP_W

#include "../rand/gen.hpp"
#include "../util/util.hpp"

namespace tifa_libs::ds {

// template <class T, T (*op)(T, T), T (*e)(), class F, T (*mapping)(F, T), F (*composition)(F, F), F (*id)()>
template <
    class T,
    auto op,
    auto e,
    class F,
    auto mapping,
    auto composition,
    auto id,
    bool reverse_ = false,
    bool recovery = false>
class fhq_treap_w {
  //!!! initial cnt = 1;
  struct YYZ {
    T w;
    T val;
    F sign;
    usz sz;
    std::array<usz, 2> son{};
    i32 rad;
    bool rev;
    YYZ(T W = e(), T VAL = e(), usz SZ = 0, i32 RAD = 0, F SIGN = id()) : w(W), val(VAL), sign(SIGN), sz(SZ), rad(RAD), rev(0) {}
  };
  rand::Gen<std::uniform_int_distribution<i32>> gen;
  vec<YYZ> t;
  vec<usz> sta;
  usz cnt;

  usz newnode(T val) {
    usz ret;
    if (sta.size()) ret = *sta.rbegin(), sta.pop_back(), t[ret] = YYZ(val, val, 1, gen());
    else ret = ++cnt, t[ret] = YYZ(val, val, 1, gen());
    return ret;
  }
  constexpr void rm(usz u) { sta.push_back(u); }
  constexpr void update(usz u) {
    t[u].w = op(t[t[u].son[0]].w, op(t[u].val, t[t[u].son[1]].w));
    t[u].sz = t[t[u].son[0]].sz + t[t[u].son[1]].sz + 1;
  }
  constexpr void reverse__(usz u) {
    static_assert(reverse_);
    std::swap(t[u].son[0], t[u].son[1]), t[u].rev ^= 1;
  }
  constexpr void all_update(usz u, F f) {
    if (u) t[u].val = mapping(f, t[u].val), t[u].w = mapping(f, t[u].w), t[u].sign = composition(f, t[u].sign);
  }
  constexpr void pushdown(usz u) {
    if (u) {
      all_update(t[u].son[0], t[u].sign), all_update(t[u].son[1], t[u].sign), t[u].sign = id();
      if constexpr (reverse_)
        if (t[u].rev) reverse__(t[u].son[0]), reverse__(t[u].son[1]), t[u].rev = 0;
    }
  }

 public:
  usz root;

  explicit constexpr fhq_treap_w(usz MAX_N) : gen(), t(MAX_N + 1), sta(), cnt(0), root(0) {
    if constexpr (recovery) sta.reserve(MAX_N + 1);
  }

  void split(usz u, usz k, usz& x, usz& y) {
    if (!u) x = y = 0;
    else {
      pushdown(u);
      if (t[t[u].son[0]].sz < k) x = u, split(t[u].son[1], k - t[t[u].son[0]].sz - 1, t[x].son[1], y), update(x);
      else y = u, split(t[u].son[0], k, x, t[y].son[0]), update(y);
    }
  }
  usz merge(usz x, usz y) {
    pushdown(x), pushdown(y);
    if (x && y) {
      if (t[x].rad <= t[y].rad) {
        t[x].son[1] = merge(t[x].son[1], y), update(x);
        return x;
      } else {
        t[y].son[0] = merge(x, t[y].son[0]), update(y);
        return y;
      }
    } else return x + y;
  }
  void insert(T w, usz id_) {
    usz x, y;
    split(root, id_, x, y);
    root = merge(merge(x, newnode(w)), y);
  }
  void insert(T w) { insert(w, cnt); }
  void erase(usz id_) {
    usz x, y, z;
    split(root, id_, x, y);
    split(y, 1, z, y);
    if (recovery) rm(z);
    root = merge(x, y);
  }
  void update(usz l, usz r, F f) {
    usz x, y, z;
    split(root, r + 1, x, z);
    split(x, l, x, y);
    all_update(y, f);
    root = merge(merge(x, y), z);
  }
  void reverse(usz l, usz r) {
    assert(reverse_);
    usz x, y, z;
    split(root, r + 1, x, z);
    split(x, l, x, y);
    reverse__(y);
    root = merge(merge(x, y), z);
  }
  T query(usz l, usz r) {
    usz x, y, z;
    split(root, r + 1, x, z);
    split(x, l, x, y);
    T ret = t[y].w;
    root = merge(merge(x, y), z);
    return ret;
  }
};

}  // namespace tifa_libs::ds

#endif