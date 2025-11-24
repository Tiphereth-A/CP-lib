#ifndef TIFALIBS_DS_OSTREE
#define TIFALIBS_DS_OSTREE

#include "../util/alias_others.hpp"
#include "bt_trv.hpp"

namespace tifa_libs::ds {

struct ostree_tag_base {
  template <tp2_ds_c pointer>
  static CEXP u32 size(pointer p) NE { retif_((p), p->sz, 0); }
  template <tp2_ds_c pointer>
  static CEXP u32 count(pointer p) NE { retif_((p), p->sz - size(p->ch[0]) - size(p->ch[1]), 0); }
  // [size(begin), size(begin->fa), ..., size(end)) += v
  template <tp2_ds_c pointer>
  static CEXP void modify_size(pointer begin, i32 v, pointer end = nullptr) NE {
    while (begin != end) begin->sz += (u32)v, begin = begin->fa;
  }

  template <tp2_ds_c pointer>
  static CEXP pointer neighbour(pointer p, bool dir) NE {
    if (!p) return nullptr;
    if (p->ch[dir]) return most(p->ch[dir], !dir);
    while (p && p->fa && p->child_dir() == dir) p = p->fa;
    retif_((p), p->fa, nullptr);
  }
  template <tp2_ds_c pointer>
  static CEXP auto prev(pointer p) NE { return neighbour(p, 0); }
  template <tp2_ds_c pointer>
  static CEXP auto next(pointer p) NE { return neighbour(p, 1); }

  template <tp2_ds_c pointer>
  static CEXP pointer rotate(pointer& root, pointer p, bool dir) NE {
    auto g = p->fa, s = p->ch[!dir];
    u32 psz = p->sz, ssz = s->sz;
    s->sz = psz, p->sz += size(s->ch[dir]) - ssz;
    auto c = s->ch[dir];
    if (c) c->fa = p;
    p->ch[!dir] = c, s->ch[dir] = p, p->fa = s, s->fa = g;
    (g ? g->ch[p == g->ch[1]] : root) = s;
    return s;
  }
};
//! will NOT change sz
struct bst_op_leaf : ostree_tag_base {
  template <tp2_ds_c pointer>
  static CEXP void insert_leaf(pointer& root, pointer p, pointer n, bool dir) NE {
    if (!p) return void(root = n);
    p->ch[dir] = n, n->fa = p;
  }
  template <tp2_ds_c pointer>
  static CEXP void erase_branch_leaf(pointer& root, pointer n) NE {
    auto p = n->fa, s = n->ch[0] ? n->ch[0] : n->ch[1];
    if (s) s->fa = p;
    if (!p) return void(root = s);
    p->ch[n->child_dir()] = s;
  }
};
template <class leaf>
struct bst_op : leaf {
  using tag_t = ostree_tag_base;
  template <tp2_ds_c pointer, class K, class Alloc, class Comp>
  CEXP pointer insert(pointer& root, const K& data, Alloc& alloc, Comp compare) NE {
    pointer now = root, p = nullptr;
    bool dir = 0;
    while (now)
      if (dir = compare((p = now)->data, data), now = now->ch[dir]; !dir && !compare(data, p->data)) {
        tag_t::modify_size(p, 1);
        return p;
      }
    pointer n = alloc.allocate(1);
    n->fa = n->ch[0] = n->ch[1] = nullptr, n->data = data, n->sz = 1;
    tag_t::modify_size(p, 1), leaf::insert_leaf(root, p, n, dir);
    return n;
  }
  template <tp2_ds_c pointer, class Alloc>
  CEXP pointer erase(pointer& root, pointer p, Alloc& alloc) NE {
    if (!p) return nullptr;
    pointer result;
    if (p->ch[0] && p->ch[1]) {
      auto s = leftmost(p->ch[1]);
      std::swap(s->data, p->data);
      tag_t::modify_size(s, (i32)tag_t::count(p) - (i32)tag_t::count(s), p);
      result = p, p = s;
    } else result = tag_t::next(p);
    tag_t::modify_size(p, -(i32)tag_t::count(p));
    leaf::erase_branch_leaf(root, p), alloc.deallocate(p, 1);
    return result;
  }
};
using bst_tag = bst_op<bst_op_leaf>;

template <class T, class K>
struct ostree_node_t {};
template <class K>
struct ostree_node_t<bst_tag, K> {
  ostree_node_t *fa, *ch[2];
  K data;
  u32 sz;
  // @return child direction of this non-root point
  CEXP bool child_dir() CNE { return this == fa->ch[1]; }
};

template <class K, std::derived_from<ostree_tag_base> tag_t, class Comp = std::less<K>>
requires requires(ostree_node_t<tag_t, K>*& root, ostree_node_t<tag_t, K> n, tag_t tag, bool dir, K key, alc<ostree_node_t<tag_t, K>> alloc, Comp comp) {
  n.fa->ch[0]->ch[1]->data;
  n.sz;
  { comp(key, key) } -> std::same_as<bool>;
  { n.child_dir() } -> std::same_as<bool>;
  { tag.size(&n) } -> std::same_as<u32>;
  tag.insert(root, key, alloc, comp);
  tag.erase(root, &n, alloc);
}
struct ostree : tag_t {
  using node_t = ostree_node_t<tag_t, K>;
  using pointer = node_t*;
  using const_pointer = const node_t*;
  using pointer_const = node_t* const;

  static CEXP Comp compare{};
  pointer root{nullptr};

  CEXP ostree() NE = default;
  ostree(ostree CR) = delete;
  ostree& operator=(ostree CR) = delete;
  CEXP ~ostree() NE { dealloc_subtree(root, alloc); }
  CEXP u32 size() CNE { return tag_t::size(root); }

  CEXP pointer lower_bound(const K& key) CNE {
    const_pointer now = root, ans = nullptr;
    while (now) {
      if (!compare(now->data, key)) ans = now, now = now->ch[0];
      else now = now->ch[1];
    }
    return (pointer)ans;
  }
  CEXP pointer upper_bound(const K& key) CNE {
    const_pointer now = root, ans = nullptr;
    while (now) {
      if (compare(key, now->data)) ans = now, now = now->ch[0];
      else now = now->ch[1];
    }
    return (pointer)ans;
  }
  CEXP pointer find(const K& key) CNE {
    auto p = lower_bound(key);
    retif_(((!p || compare(p->data, key) || compare(key, p->data))), nullptr, p);
  }
  // Order start from 0
  CEXP u32 order_of_key(const K& key) CNE {
    u32 ans = 0;
    auto now = root;
    while (now) {
      if (!compare(now->data, key)) now = now->ch[0];
      else ans += tag_t::size(now->ch[0]) + tag_t::count(now), now = now->ch[1];
    }
    return ans;
  }
  // Order start from 0
  CEXP const_pointer find_by_order(u32 order) CNE {
    const_pointer now = root, ans = nullptr;
    while (now && now->sz >= order)
      if (auto lsz = tag_t::size(now->ch[0]), cnt = tag_t::count(now); order < lsz) now = now->ch[0];
      else {
        if (ans = now; order < lsz + cnt) break;
        now = now->ch[1], order -= lsz + cnt;
      }
    return ans;
  }
  CEXP const_pointer insert(const K& data) NE { return tag_t::insert(root, data, alloc, compare); }
  //! count -= 1
  CEXP bool erase(const K& key) NE {
    if (auto p = find(key); !p) return false;
    else if (tag_t::count(p) > 1) {
      tag_t::modify_size(p, -1);
      return true;
    } else {
      erase(p);
      return true;
    }
  }
  CEXP const_pointer erase(pointer p) NE { return tag_t::erase(root, p, alloc); }

 private:
  alc<node_t> alloc;
};

template <class K, class Comp = std::less<K>>
using bstree = ostree<K, bst_tag, Comp>;

}  // namespace tifa_libs::ds

#endif