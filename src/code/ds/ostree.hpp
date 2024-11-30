#ifndef TIFALIBS_DS_OSTREE
#define TIFALIBS_DS_OSTREE

#include "../util/util.hpp"

namespace tifa_libs::ds {

struct bst_tag {
  template <class pointer>
  CEXP u32 size(pointer p) const { return p ? p->sz : 0; }
  template <class pointer>
  CEXP void insert_leaf(pointer &root, pointer p, pointer n, bool dir) {
    if (!p) return void(root = n);
    p->ch[dir] = n, n->fa = p;
    auto now = p;
    while (now) now->sz++, now = now->fa;
  }
  template <class pointer>
  CEXP void erase_branch_leaf(pointer &root, pointer n) {
    auto p = n->fa, s = n->ch[0] ? n->ch[0] : n->ch[1];
    if (s) s->fa = p;
    if (!p) return void(root = s);
    p->ch[n->child_dir()] = s;
    auto now = p;
    while (now) now->sz--, now = now->fa;
  }
  template <class pointer>
  CEXP pointer rotate(pointer &root, pointer p, bool dir) {
    auto g = p->fa, s = p->ch[!dir];
    assert(s);
    s->sz = p->sz, p->sz = size(p->ch[dir]) + size(s->ch[dir]) + 1;
    auto c = s->ch[dir];
    if (c) c->fa = p;
    p->ch[!dir] = c, s->ch[dir] = p, p->fa = s, s->fa = g;
    return (g ? g->ch[p == g->ch[1]] : root) = s;
  }
};

template <class T, class K>
struct ostree_node_t {};
template <class K>
struct ostree_node_t<bst_tag, K> {
  ostree_node_t *fa, *ch[2];
  K data;
  u32 sz;
  // @return child direction of this non-root point
  CEXP bool child_dir() const { return this == fa->ch[1]; }
};

template <class K, class tree_tag_t, class Comp = std::less<K>, template <class> class Alloc = std::pmr::polymorphic_allocator>
requires requires(ostree_node_t<tree_tag_t, K> *&root, ostree_node_t<tree_tag_t, K> n, tree_tag_t tag, bool dir) {
  n.fa->ch[0]->ch[1]->data;
  n.sz;
  { n.child_dir() } -> std::same_as<bool>;
  { tag.size(&n) } -> std::same_as<u32>;
  tag.insert_leaf(root, &n, &n, dir);
  tag.erase_branch_leaf(root, &n);
}
struct ostree : protected tree_tag_t {
  using node_t = ostree_node_t<tree_tag_t, K>;
  using pointer = node_t *;
  using const_pointer = const node_t *;
  using pointer_const = node_t *const;

  static constexpr Comp compare{};
  pointer root;

  CEXP ostree() : tree_tag_t(), root{nullptr} {}
  CEXP ~ostree() {
    post_order([this](auto it) { alloc.deallocate(it, 1); });
  }
  CEXP u32 size() const { return tree_tag_t::size(root); }
  template <class F>
  requires requires(pointer p, F f) { f(p); }
  CEXP void pre_order(F callback) {
    auto f = [&](auto &&f, pointer p) {
      if (!p) return;
      callback(p), f(f, p->ch[0]), f(f, p->ch[1]);
    };
    f(f, root);
  }
  template <class F>
  requires requires(pointer p, F f) { f(p); }
  CEXP void in_order(F callback) {
    auto f = [&](auto &&f, pointer p) {
      if (!p) return;
      f(f, p->ch[0]), callback(p), f(f, p->ch[1]);
    };
    f(f, root);
  }
  template <class F>
  requires requires(pointer p, F f) { f(p); }
  CEXP void post_order(F callback) {
    auto f = [&](auto &&f, pointer p) {
      if (!p) return;
      f(f, p->ch[0]), f(f, p->ch[1]), callback(p);
    };
    f(f, root);
  }
  CEXP auto leftmost(const_pointer p) const { return most(p, 0); }
  CEXP auto rightmost(const_pointer p) const { return most(p, 1); }
  CEXP auto prev(const_pointer p) const { return neighbour(p, 0); }
  CEXP auto next(const_pointer p) const { return neighbour(p, 1); }
  CEXP pointer lower_bound(const K &key) const {
    const_pointer now = root, ans = nullptr;
    while (now) {
      if (!compare(now->data, key)) ans = now, now = now->ch[0];
      else now = now->ch[1];
    }
    return (pointer)ans;
  }
  CEXP pointer upper_bound(const K &key) const {
    const_pointer now = root, ans = nullptr;
    while (now) {
      if (compare(key, now->data)) ans = now, now = now->ch[0];
      else now = now->ch[1];
    }
    return (pointer)ans;
  }
  CEXP pointer find(const K &key) const {
    auto p = lower_bound(key);
    return (!p || p->data != key) ? nullptr : p;
  }
  // Order start from 0
  CEXP u32 order_of_key(const K &key) const {
    u32 ans = 0;
    auto now = root;
    while (now) {
      if (!compare(now->data, key)) now = now->ch[0];
      else ans += tree_tag_t::size(now->ch[0]) + 1, now = now->ch[1];
    }
    return ans;
  }
  // Order start from 0
  CEXP const_pointer find_by_order(u32 order) const {
    const_pointer now = root, ans = nullptr;
    while (now && now->sz >= order)
      if (auto lsize = tree_tag_t::size(now->ch[0]); order < lsize) now = now->ch[0];
      else {
        if (ans = now; order == lsize) break;
        now = now->ch[1], order -= lsize + 1;
      }
    return ans;
  }
  CEXP const_pointer insert(const K &data) {
    pointer n = alloc.allocate(1);
    n->fa = n->ch[0] = n->ch[1] = nullptr, n->data = data, n->sz = 1;
    pointer now = root, p = nullptr;
    bool dir = 0;
    while (now) p = now, dir = compare(now->data, data), now = now->ch[dir];
    return tree_tag_t::insert_leaf(root, p, n, dir), n;
  }
  CEXP bool erase(const K &key) {
    if (auto p = find(key); !p) return false;
    else return erase(p), true;
  }
  CEXP const_pointer erase(pointer p) {
    if (!p) return nullptr;
    pointer result;
    if (p->ch[0] && p->ch[1]) {
      auto s = leftmost(p->ch[1]);
      std::swap(s->data, p->data), result = p, p = s;
    } else result = next(p);
    return tree_tag_t::erase_branch_leaf(root, p), alloc.deallocate(p, 1), result;
  }

 private:
  Alloc<node_t> alloc;
  CEXP pointer most(const_pointer p, bool dir) const {
    if (!p) return nullptr;
    while (p->ch[dir]) p = p->ch[dir];
    return (pointer)p;
  }
  CEXP pointer neighbour(const_pointer p, bool dir) const {
    if (!p) return nullptr;
    if (p->ch[dir]) return most(p->ch[dir], !dir);
    if (p == root) return nullptr;
    while (p && p->fa && !p->child_dir()) p = p->fa;
    return p ? p->fa : nullptr;
  }
};

template <class K, class Comp = std::less<K>>
using bstree = ostree<K, bst_tag, Comp>;

}  // namespace tifa_libs::ds

#endif