#ifndef TIFA_LIBS_DS_FHQ_TREAP
#define TIFA_LIBS_DS_FHQ_TREAP

#include "../rand/gen.hpp"
#include "../util/util.hpp"

namespace tifa_libs::ds {

// template <class T, T (*op)(T, T), T (*e)(), class F, T (*mapping)(F, T), F (*composition)(F, F), F (*id)()>
template <
    class Ty,
    class T,
    auto op,
    auto e,
    class F,
    auto mapping,
    auto composition,
    auto id,
    bool reverse_ = false,
    bool recovery = false>
// default range add range sum
class fhq_treap_w {
  //!!! initial cnt = 1;
  struct YYZ {
    T w;
    T val;
    F sign;
    size_t sz, ls, rs;
    i32 rad;
    bool rev;
    YYZ(T W = e(), T VAL = e(), size_t SZ = 0, i32 RAD = 0, F SIGN = id()) : w(W), val(VAL), sign(SIGN), sz(SZ), ls(0), rs(0), rad(RAD), rev(0) {}
  };
  rand::Gen<std::uniform_int_distribution<i32>> gen;
  vec<YYZ> t;
  vec<size_t> sta;
  size_t cnt;
  size_t newnode(T val) {
    size_t ret;
    if (sta.size()) ret = *sta.rbegin(), sta.pop_back(), t[ret] = YYZ(val, val, 1, gen());
    else ret = ++cnt, t[ret] = YYZ(val, val, 1, gen());
    return ret;
  }
  constexpr void rm(size_t u) { sta.push_back(u); }
  constexpr void update(size_t u) {
    t[u].w = op(t[t[u].ls].w, op(t[u].val, t[t[u].rs].w));
    t[u].sz = t[t[u].ls].sz + t[t[u].rs].sz + 1;
  }
  constexpr void reverse__(size_t u) {
    assert(reverse_);
    std::swap(t[u].ls, t[u].rs), t[u].rev ^= 1;
  }
  constexpr void all_update(size_t u, F f) {
    if (u) t[u].val = mapping(f, t[u].val), t[u].w = mapping(f, t[u].w), t[u].sign = composition(f, t[u].sign);
  }
  constexpr void pushdown(size_t u) {
    if (u) {
      all_update(t[u].ls, t[u].sign), all_update(t[u].rs, t[u].sign), t[u].sign = id();
      if (reverse_ && t[u].rev) reverse__(t[u].ls), reverse__(t[u].rs), t[u].rev = 0;
    }
  }

 public:
  size_t root;
  explicit constexpr fhq_treap_w(size_t MAX_N) : gen(), t(MAX_N + 1), sta(), cnt(0), root(0) {
    if (recovery) sta.reserve(MAX_N + 1);
  }
  void split(size_t u, size_t k, size_t& x, size_t& y) {
    if (!u) x = y = 0;
    else {
      pushdown(u);
      if (t[t[u].ls].sz < k) x = u, split(t[u].rs, k - t[t[u].ls].sz - 1, t[x].rs, y), update(x);
      else y = u, split(t[u].ls, k, x, t[y].ls), update(y);
    }
  }
  size_t merge(size_t x, size_t y) {
    pushdown(x), pushdown(y);
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
  void insert(T w, size_t id_) {
    size_t x, y;
    split(root, id_, x, y);
    root = merge(merge(x, newnode(w)), y);
  }
  void insert(T w) { insert(w, cnt); }
  void erase(size_t id_) {
    size_t x, y, z;
    split(root, id_, x, y);
    split(y, 1, z, y);
    if (recovery) rm(z);
    root = merge(x, y);
  }
  void update(size_t l, size_t r, F f) {
    size_t x, y, z;
    split(root, r + 1, x, z);
    split(x, l, x, y);
    all_update(y, f);
    root = merge(merge(x, y), z);
  }
  void reverse(size_t l, size_t r) {
    assert(reverse_);
    size_t x, y, z;
    split(root, r + 1, x, z);
    split(x, l, x, y);
    reverse__(y);
    root = merge(merge(x, y), z);
  }
  T query(size_t l, size_t r) {
    size_t x, y, z;
    split(root, r + 1, x, z);
    split(x, l, x, y);
    T ret = t[y].w;
    root = merge(merge(x, y), z);
    return ret;
  }
};

}  // namespace tifa_libs::ds

#endif