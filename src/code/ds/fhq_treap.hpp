#ifndef TIFALIBS_DS_FHQ_TREAP
#define TIFALIBS_DS_FHQ_TREAP

#include "../rand/gen.hpp"

namespace tifa_libs::ds {

template <class KEY, class VAL, bool recovery = false>
class fhq_treap {
  //! initial cnt = 1
  struct TIFA {
    std::pair<KEY, VAL> w;
    u32 sz;
    arr<u32, 2> son{};
    i32 rad;
    CEXP TIFA(std::pair<KEY, VAL> W = {0, 0}, u32 SZ = 0, i32 RAD = 0) : w(W), sz(SZ), rad(RAD) {}
  };
  rand::Gen<std::uniform_int_distribution<i32>> gen;
  vec<TIFA> t;
  vecu sta;
  u32 cnt;

  CEXP u32 newnode(std::pair<KEY, VAL> CR w) {
    u32 ret;
    if (recovery && sta.size()) ret = *sta.rbegin(), sta.pop_back(), t[ret] = TIFA(w, 1, gen());
    else ret = ++cnt, t.push_back(TIFA(w, 1, gen()));
    return ret;
  }
  CEXP void preorder(u32 u, vecp<KEY, VAL>& ret) {
    if (!u) return;
    ret.push_back(t[u].w);
    preorder(t[u].son[0], ret);
    preorder(t[u].son[1], ret);
  }
  CEXP void inorder(u32 u, vecp<KEY, VAL>& ret) {
    if (!u) return;
    inorder(t[u].son[0], ret);
    ret.push_back(t[u].w);
    inorder(t[u].son[1], ret);
  }
  CEXP void postorder(u32 u, vecp<KEY, VAL>& ret) {
    if (!u) return;
    preorder(t[u].son[0], ret);
    preorder(t[u].son[1], ret);
    ret.push_back(t[u].w);
  }
  CEXP void rm(u32 u) { sta.push_back(u); }
  CEXP void update(u32 u) { t[u].sz = t[t[u].son[0]].sz + t[t[u].son[1]].sz + 1; }

 public:
  u32 root;

  explicit CEXP fhq_treap() : gen(), t(1), sta(), cnt(0), root(0) {}

  CEXP void split(u32 u, KEY k, u32& x, u32& y) {
    if (!u) x = y = 0;
    else {
      if (t[u].w.first <= k) x = u, split(t[u].son[1], k, t[u].son[1], y), update(x);
      else y = u, split(t[u].son[0], k, x, t[y].son[0]), update(y);
    }
  }
  CEXP void split_not_include(u32 u, KEY k, u32& x, u32& y) {
    if (!u) x = y = 0;
    else {
      if (t[u].w.first < k) x = u, split_not_include(t[u].son[1], k, t[u].son[1], y), update(x);
      else y = u, split_not_include(t[u].son[0], k, x, t[y].son[0]), update(y);
    }
  }
  CEXP u32 merge(u32 x, u32 y) {
    if (x && y) {
      if (t[x].rad <= t[y].rad) {
        t[x].son[1] = merge(t[x].son[1], y), update(x);
        return x;
      }
      t[y].son[0] = merge(x, t[y].son[0]), update(y);
      return y;
    }
    return x + y;
  }
  CEXP void insert(std::pair<KEY, VAL> w) {
    u32 x, y;
    split(root, w.first, x, y);
    root = merge(merge(x, newnode(w)), y);
  }
  CEXP void erase(KEY key) {
    u32 x, y, z;
    split(root, key, x, y);
    split_not_include(x, key, x, z);
    if (recovery) rm(z);
    z = merge(t[z].son[0], t[z].son[1]);
    root = merge(merge(x, z), y);
  }
  CEXP u32 key_req_rk(KEY key) {
    u32 x, y, ret;
    split_not_include(root, key, x, y);
    ret = t[x].sz + 1;
    root = merge(x, y);
    return ret;
  }
  CEXP std::pair<KEY, VAL> rk_req_w(u32 u, u32 k) {
    while (1) {
      if (t[t[u].son[0]].sz >= k) u = t[u].son[0];
      else {
        if (t[t[u].son[0]].sz + 1 >= k) return t[u].w;
        k -= t[t[u].son[0]].sz + 1, u = t[u].son[1];
      }
    }
  }
  CEXP std::pair<KEY, VAL> pre_w(KEY key) {
    u32 x, y;
    split(root, key - 1, x, y);
    std::pair<KEY, VAL> ret = rk_req_w(x, t[x].sz);
    root = merge(x, y);
    return ret;
  }
  CEXP std::pair<KEY, VAL> suf_w(KEY key) {
    u32 x, y;
    split(root, key, x, y);
    std::pair<KEY, VAL> ret = rk_req_w(y, 1);
    root = merge(x, y);
    return ret;
  }
  CEXP bool find(KEY key) {
    u32 x, y, z;
    split(root, key, x, y);
    split_not_include(x, key, x, z);
    bool ret = t[z].sz;
    root = merge(merge(x, z), y);
    return ret;
  }
  CEXP vecp<KEY, VAL> preorder() {
    vecp<KEY, VAL> ret;
    preorder(root, ret);
    return ret;
  }
  CEXP vecp<KEY, VAL> inorder() {
    vecp<KEY, VAL> ret;
    inorder(root, ret);
    return ret;
  }
  CEXP vecp<KEY, VAL> postorder() {
    vecp<KEY, VAL> ret;
    postorder(root, ret);
    return ret;
  }
  CEXP vecp<KEY, VAL> inorder(KEY key) {
    u32 x, y, z;
    split(root, key, x, y);
    split_not_include(x, key, x, z);
    vecp<KEY, VAL> ret;
    inorder(z, ret);
    root = merge(merge(x, z), y);
    return ret;
  }
};

}  // namespace tifa_libs::ds

#endif