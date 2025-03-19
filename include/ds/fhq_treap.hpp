#ifndef TIFALIBS_DS_FHQ_TREAP
#define TIFALIBS_DS_FHQ_TREAP

#include "../rand/gen.hpp"
#include "../util/alias_others.hpp"

namespace tifa_libs::ds {

template <class T, bool recovery = false, class Comp = std::less<T>>
struct fhq_treap {
  static CEXP Comp compare{};
  struct TIFA {
    T val;
    u32 r, sz, son[2];
  };
  rand::Gen<u32> rnd;
  vec<TIFA> data;
  vecu stk;
  u32 root;

 private:
  u32 new_node(cT_(T) val) NE {
    u32 ret;
    if CEXP (recovery && stk.size()) data[ret = stk.back()] = {val, rnd(), 1, {0, 0}}, stk.pop_back();
    else ret = (u32)data.size(), data.push_back(TIFA{val, rnd(), 1, {0, 0}});
    return ret;
  }
  void pushup(u32 pos) NE { data[pos].sz = data[data[pos].son[0]].sz + 1 + data[data[pos].son[1]].sz; }
  template <bool strict = false>
  pttu split_root(u32 pos, cT_(T) key) NE {
    if (!pos) return {};
    bool f;
    if CEXP (strict) f = compare(data[pos].val, key);
    else f = !compare(key, data[pos].val);
    if (f) {
      auto [l, r] = split_root<strict>(data[pos].son[1], key);
      data[pos].son[1] = l, pushup(pos);
      return {pos, r};
    }
    auto [l, r] = split_root<strict>(data[pos].son[0], key);
    data[pos].son[0] = r, pushup(pos);
    return {l, pos};
  }
  u32 merge_root(u32 l, u32 r) NE {
    if (!l | !r) return l | r;
    if (data[l].r < data[r].r) {
      data[l].son[1] = merge_root(data[l].son[1], r), pushup(l);
      return l;
    }
    data[r].son[0] = merge_root(l, data[r].son[0]), pushup(r);
    return r;
  }

 public:
  CEXPE fhq_treap() : rnd{}, data{1}, stk{}, root{} { data[0].sz = {}; }
  void insert(cT_(T) val) NE {
    u32 tar = new_node(val);
    auto dfs = [&](auto &&f, u32 &pos) NE -> void {
      if (!pos) return void(pos = tar);
      if (data[tar].r < data[pos].r) {
        auto [l, r] = split_root<true>(pos, val);
        data[tar].son[0] = l, data[tar].son[1] = r;
        pos = tar;
      } else f(f, compare(data[pos].val, val) ? data[pos].son[1] : data[pos].son[0]);
      pushup(pos);
    };
    dfs(dfs, root);
  }
  bool erase(cT_(T) val) NE {
    auto dfs = [&](auto &&f, u32 &pos) NE -> bool {
      if (!pos) return false;
      if (data[pos].val == val) {
        if CEXP (recovery) stk.push_back(pos);
        pos = merge_root(data[pos].son[0], data[pos].son[1]);
        return true;
      }
      if (!f(f, compare(data[pos].val, val) ? data[pos].son[1] : data[pos].son[0])) return false;
      pushup(pos);
      return true;
    };
    return dfs(dfs, root);
  }
  auto find(cT_(T) val) CNE {
    u32 pos = root;
    while (pos)
      if (val == data[pos].val) return data.cbegin() + pos;
      else pos = data[pos].son[!compare(val, data[pos].val)];
    return data.cend();
  }
  u32 rank(cT_(T) val) CNE {
    u32 pos = root, res = 0;
    while (pos)
      if (compare(data[pos].val, val)) res += data[data[pos].son[0]].sz + 1, pos = data[pos].son[1];
      else pos = data[pos].son[0];
    return res + 1;
  }
  u32 count(cT_(T) val) CNE {
    u32 rk = rank(val);
    if (auto res = next(val); !res) return data[root].sz - rk + 1;
    else return rank(res.value()) - rk;
  }
  std::optional<T> kth(u32 k) CNE {
    if (k < 1 || k > data[root].sz) return {};
    u32 pos = root;
    while (true)
      if (auto _ = data[pos].sz - data[data[pos].son[1]].sz; _ == k) return data[pos].val;
      else if (_ < k) k -= _, pos = data[pos].son[1];
      else pos = data[pos].son[0];
  }
  auto prev(cT_(T) val) CNE {
    u32 pos = root;
    std::pair<bool, T> res{false, {}};
    while (pos)
      if (!compare(data[pos].val, val)) pos = data[pos].son[0];
      else res = {true, data[pos].val}, pos = data[pos].son[1];
    return res.first ? std::optional<T>{res.second} : std::nullopt;
  }
  auto next(cT_(T) val) CNE {
    u32 pos = root;
    std::pair<bool, T> res{false, {}};
    while (pos)
      if (!compare(val, data[pos].val)) pos = data[pos].son[1];
      else res = {true, data[pos].val}, pos = data[pos].son[0];
    return res.first ? std::optional<T>{res.second} : std::nullopt;
  }
};

}  // namespace tifa_libs::ds

#endif