#ifndef TIFALIBS_DS_FHQ_TREAP
#define TIFALIBS_DS_FHQ_TREAP

#include "../rand/gen.hpp"

namespace tifa_libs::ds {

template <class K, class V, bool recovery = false>
class fhq_treap {
  //! initial cnt = 1
  struct TIFA {
    std::pair<K, V> w;
    u32 sz;
    arr<u32, 2> son{};
    i32 rad;
    CEXP TIFA(cT_(std::pair<K, V>) W = {0, 0}, u32 SZ = 0, i32 RAD = 0) : w(W), sz(SZ), rad(RAD) {}
  };
  rand::Gen<i32> gen;
  vec<TIFA> t;
  vecu sta;
  u32 cnt;

  CEXP u32 newnode(cT_(std::pair<K, V>) w) {
    u32 ret;
    if (recovery && sta.size()) ret = *sta.rbegin(), sta.pop_back(), t[ret] = TIFA(w, 1, gen());
    else ret = ++cnt, t.push_back(TIFA(w, 1, gen()));
    return ret;
  }
  CEXP void preorder(u32 u, vecp<K, V>& ret) const {
    if (!u) return;
    ret.push_back(t[u].w), preorder(t[u].son[0], ret), preorder(t[u].son[1], ret);
  }
  CEXP void inorder(u32 u, vecp<K, V>& ret) const {
    if (!u) return;
    inorder(t[u].son[0], ret), ret.push_back(t[u].w), inorder(t[u].son[1], ret);
  }
  CEXP void postorder(u32 u, vecp<K, V>& ret) const {
    if (!u) return;
    postorder(t[u].son[0], ret), postorder(t[u].son[1], ret), ret.push_back(t[u].w);
  }
  CEXP void rm(u32 u) { sta.push_back(u); }
  CEXP void update(u32 u) { t[u].sz = t[t[u].son[0]].sz + t[t[u].son[1]].sz + 1; }

 public:
  u32 root;

  CEXPE fhq_treap() : gen(), t(1), sta(), cnt(0), root(0) {}

  CEXP u32 CR size() const { return cnt; }
  CEXP void split(u32 u, cT_(K) k, u32& x, u32& y) {
    if (!u) x = y = 0;
    else if (t[u].w.first <= k) x = u, split(t[u].son[1], k, t[u].son[1], y), update(x);
    else y = u, split(t[u].son[0], k, x, t[y].son[0]), update(y);
  }
  CEXP void split_not_include(u32 u, cT_(K) k, u32& x, u32& y) {
    if (!u) x = y = 0;
    else if (t[u].w.first < k) x = u, split_not_include(t[u].son[1], k, t[u].son[1], y), update(x);
    else y = u, split_not_include(t[u].son[0], k, x, t[y].son[0]), update(y);
  }
  CEXP u32 merge(u32 x, u32 y) {
    if (x && y) {
      if (t[x].rad <= t[y].rad) return t[x].son[1] = merge(t[x].son[1], y), update(x), x;
      return t[y].son[0] = merge(x, t[y].son[0]), update(y), y;
    } else return x + y;
  }
  CEXP void insert(cT_(std::pair<K, V>) w) {
    u32 x, y;
    split(root, w.first, x, y), root = merge(merge(x, newnode(w)), y);
  }
  CEXP void erase(cT_(K) key) {
    u32 x, y, z;
    split(root, key, x, y), split_not_include(x, key, x, z);
    if CEXP (recovery) rm(z);
    root = merge(merge(x, z = merge(t[z].son[0], t[z].son[1])), y);
  }
  CEXP u32 key_req_rk(cT_(K) key) {
    u32 x, y, ret;
    return split_not_include(root, key, x, y), ret = t[x].sz + 1, root = merge(x, y), ret;
  }
  CEXP auto rk_req_w(u32 u, u32 k) {
    while (1)
      if (t[t[u].son[0]].sz >= k) u = t[u].son[0];
      else {
        if (t[t[u].son[0]].sz + 1 >= k) return t[u].w;
        k -= t[t[u].son[0]].sz + 1, u = t[u].son[1];
      }
  }
  CEXP auto pre_w(cT_(K) key) {
    u32 x, y;
    split(root, key - 1, x, y);
    auto ret = rk_req_w(x, t[x].sz);
    return root = merge(x, y), ret;
  }
  CEXP auto suf_w(cT_(K) key) {
    u32 x, y;
    split(root, key, x, y);
    auto ret = rk_req_w(y, 1);
    return root = merge(x, y), ret;
  }
  CEXP bool find(cT_(K) key) {
    u32 x, y, z;
    split(root, key, x, y), split_not_include(x, key, x, z);
    bool ret = t[z].sz;
    return root = merge(merge(x, z), y), ret;
  }
  CEXP auto preorder() const {
    vecp<K, V> ret;
    return preorder(root, ret), ret;
  }
  CEXP auto inorder() const {
    vecp<K, V> ret;
    return inorder(root, ret), ret;
  }
  CEXP auto postorder() const {
    vecp<K, V> ret;
    return postorder(root, ret), ret;
  }
  CEXP auto inorder(cT_(K) key) {
    u32 x, y, z;
    split(root, key, x, y), split_not_include(x, key, x, z);
    vecp<K, V> ret;
    return inorder(z, ret), root = merge(merge(x, z), y), ret;
  }
};

}  // namespace tifa_libs::ds

#endif