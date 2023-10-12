#ifndef TIFA_LIBS_DS_FHQ_TREAP
#define TIFA_LIBS_DS_FHQ_TREAP

#include "../rand/gen.hpp"
#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class Ty, bool recovery = false>
class fhq_treap {
  //!!! initial cnt = 1;
  struct YYZ {
    // rand::Gen<std::mt19937(), std::uniform_int_distribution<int>> gen(std::mt19937(), std::uniform_int_distribution<int>());
    Ty val;
    size_t sz, ls, rs;
    i32 rad;
    YYZ(Ty VAL = 0, size_t SZ = 0, size_t LS = 0, size_t RS = 0) : val(VAL), sz(SZ), ls(LS), rs(RS), rad() { rad = std::rand(); }
  };
  vec<YYZ> t;
  vec<size_t> sta;
  size_t cnt;
  size_t newnode(Ty val) {
    size_t ret;
    if (recovery && sta.size()) ret = *sta.rbegin(), sta.pop_back(), t[ret] = YYZ(val, 1);
    else ret = ++cnt, t[ret] = YYZ(val, 1);
    return ret;
  }
  constexpr void rm(size_t u) { sta.push_back(u); }
  constexpr void update(size_t u) { t[u].sz = t[t[u].ls].sz + t[t[u].rs].sz + 1; }

 public:
  size_t root;
  explicit constexpr fhq_treap(size_t MAX_N) : t(MAX_N + 1), sta(), cnt(0), root(0) {
    if (recovery) sta.reserve(MAX_N + 1);
  }
  void split_w(size_t u, Ty k, size_t& x, size_t& y) {
    if (!u) x = y = 0;
    else {
      if (t[u].val <= k) x = u, split_w(t[u].rs, k, t[u].rs, y), update(x);
      else y = u, split_w(t[u].ls, k, x, t[y].ls), update(y);
    }
  }
  void split_id(size_t u, size_t k, size_t& x, size_t& y) {
    if (!u) x = y = 0;
    else {
      if (t[t[u].ls].sz < k) x = u, split_id(t[u].rs, k - t[t[u].ls].sz - 1, t[x].rs, y), update(x);
      else y = u, split_id(t[u].ls, k, x, t[y].ls), update(y);
    }
  }
  size_t merge(size_t x, size_t y) {
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
  void insert(Ty w) {
    size_t x, y;
    split_w(root, w, x, y);
    root = merge(merge(x, newnode(w)), y);
  }
  void erase(Ty w) {
    size_t x, y, z;
    split_w(root, w, x, y);
    split_w(x, w - 1, x, z);
    z = merge(t[z].ls, t[z].rs);
    if (recovery) rm(z);
    root = merge(merge(x, z), y);
  }
  size_t w_que_rk(Ty w) {
    size_t x, y, ret;
    split_w(root, w - 1, x, y);
    ret = t[x].sz + 1;
    root = merge(x, y);
    return ret;
  }
  Ty rk_que_w(size_t u, size_t k) {
    while (1) {
      if (t[t[u].ls].sz >= k) u = t[u].ls;
      else {
        if (t[t[u].ls].sz + 1 >= k) return t[u].val;
        k -= t[t[u].ls].sz + 1, u = t[u].rs;
      }
    }
  }
  Ty pre_w(Ty w) {
    size_t x, y;
    Ty ret;
    split_w(root, w - 1, x, y);
    ret = rk_que_w(x, t[x].sz);
    root = merge(x, y);
    return ret;
  }
  Ty suf_w(Ty w) {
    size_t x, y;
    Ty ret;
    split_w(root, w, x, y);
    ret = rk_que_w(y, 1);
    root = merge(x, y);
    return ret;
  }
};

// template <class Ty
//           // ,
//           // class T = std::pair<Ty, size_t>,
//           // auto op = [](T a, T b) { return T{a.first + b.first, a.second + b.second}; },
//           // auto e = []() { return T{0, 0}; },
//           // class F = T,
//           // auto mapping = [](F f, T a) { return f * a.second + a.first; },
//           // auto composition = [](F f, F g) { return f + g; },
//           // auto id = []() { return 0; },
//           // auto poset = [](T a, T b) { return a <= b; }
//           >
// class fhq_treap_w {
//   //!!! initial cnt = 1;
//   struct YYZ {
//     rand::Gen<std::mt19937, std::uniform_int_distribution<int>> gen(std::mt19937(), std::uniform_int_distribution<tifa_libs::u32>());
//     Ty val;
//     // T w;
//     // F sign;
//     size_t sz, ls, rs;
//     tifa_libs::u32 rad;
//     YYZ(Ty VAL = 0, size_t SZ = 1, size_t LS = 0, size_t RS = 0) : val(VAL), sz(SZ), ls(LS), rs(RS), rad(gen()) {}
//   };
//   vec<YYZ> t;
//   vec<size_t> sta;
//   size_t cnt;
//   size_t newnode(Ty val) {
//     size_t ret;
//     if (sta.size()) ret = *sta.rbegin(), sta.pop_back(), t[ret] = YYZ(val, 1);
//     else ret = ++cnt, t.push_back(YYZ(val, 1));
//     return ret;
//   }
//   constexpr void update(size_t u) {
//     // t[u].w = op(t[t[u].ls].w, t[t[u].rs].w);
//     t[u].sz = t[t[u].ls].sz + t[t[u].rs].sz + 1;
//   }
//   // constexpr void all_update(size_t u, F f) { t[u].w = mapping(f, t[u].w), t[u].sign = composition(f, t[u].sign); }
//   // constexpr void pushdown(size_t u) {
//   //   if (u) all_update(t[u].ls, t[u].sign), all_update(t[u].rs, t[u].sign), t[u].sign = id();
//   // }

// public:
//  explicit constexpr fhq_treap_w<>() : t(1), sta(), cnt(0) {}
//  void split_w(size_t u, Ty k, size_t& x, size_t& y) {
//    if (!u) x = y = 0;
//    else {
//      // pushdown(u);
//      if (t[u].w <= k) x = u, split(t[u].rs, k, t[u].ls, y), update(x);
//      else y = u, split(t[u].rs, k, x, t[y].rs), update(y);
//    }
//  }
//  void split_id(size_t u, size_t k, size_t& x, size_t& y) {
//    if (!u) x = y = 0;
//    else {
//      // pushdown(u);
//      if (t[t[u].ls].sz < k) x = u, split(t[u].rs, k - t[t[u].ls].sz - 1, t[x].ls, y), update(x);
//      else y = u, split(t[u].rs, k, x, t[y].rs), update(y);
//    }
//  }
//  size_t merge(size_t x, size_t y) {
//    // pushdown(x), pushdown(y);
//    if (x && y) {
//      if (t[x].rad <= t[y].rad) {
//        t[x].rs = merge(t[x].rs, y), update(x);
//        return x;
//      } else {
//        t[y].ls = merge(x, t[y].ls), update(y);
//        return y;
//      }
//    } else return x + y;
//  }
// };

}  // namespace tifa_libs::ds

#endif