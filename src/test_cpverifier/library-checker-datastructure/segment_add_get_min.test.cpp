#define PROBLEM "https://judge.yosupo.jp/problem/segment_add_get_min"

#include "../../code/ds/lichao_segtree.hpp"
#include "../../code/edh/discretization.hpp"
#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"

i64 op(i64 x, i64 y) { return tifa_libs::min(x, y); }

int main() {
  u32 n, q;
  tifa_libs::fin >> n >> q;
  vecii lsh;
  struct seg {
    i64 a, b, l, r;
  };
  vec<seg> se(n);
  struct que {
    usz opt;
    i64 pos;
    seg k;
  };
  vec<que> qu(q);
  flt_ (u32, i, 0, n)
    tifa_libs::fin >> se[i].l >> se[i].r >> se[i].a >> se[i].b, se[i].r -= 1, lsh.push_back(se[i].l), lsh.push_back(se[i].r);
  flt_ (u32, i, 0, q) {
    tifa_libs::fin >> qu[i].opt;
    if (qu[i].opt)
      tifa_libs::fin >> qu[i].pos, lsh.push_back(qu[i].pos);
    else
      tifa_libs::fin >> qu[i].k.l >> qu[i].k.r >> qu[i].k.a >> qu[i].k.b, qu[i].k.r -= 1, lsh.push_back(qu[i].k.l), lsh.push_back(qu[i].k.r);
  }
  lsh = tifa_libs::uniq<vecii>(lsh);
  tifa_libs::ds::lichao_segtree<i64, op> tr(lsh);
  flt_ (u32, i, 0, n)
    tr.add(se[i].a, se[i].b, se[i].l, se[i].r);
  flt_ (u32, i, 0, q)
    if (qu[i].opt) {
      i64 ret = tr.query(qu[i].pos);
      if (ret == INT64_MAX) tifa_libs::fout << "INFINITY\n";
      else tifa_libs::fout << ret << '\n';
    } else
      tr.add(qu[i].k.a, qu[i].k.b, qu[i].k.l, qu[i].k.r);
  return 0;
}
