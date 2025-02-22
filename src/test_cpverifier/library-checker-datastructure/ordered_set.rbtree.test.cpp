#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"

#include "../../code/ds/rbtree.hpp"
#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"

int main() {
  u32 n, q;
  tifa_libs::fin >> n >> q;
  tifa_libs::ds::rbtree<u32> tr;
  flt_ (u32, i, 0, n, x) {
    tifa_libs::fin >> x;
    tr.insert(x);
  }
  flt_ (u32, i, 0, q, t, x) {
    tifa_libs::fin >> t >> x;
    auto lb = tr.lower_bound(x);
    switch (t) {
      case 0:
        if (!lb || lb->data != x) tr.insert(x);
        break;
      case 1:
        if (lb && lb->data == x) tr.erase(lb);
        break;
      case 2:
        if (tr.size() < x) tifa_libs::fout << "-1\n";
        else tifa_libs::fout << tr.find_by_order(x - 1)->data << '\n';
        break;
      case 3: tifa_libs::fout << tr.order_of_key(x) + (lb ? lb->data == x : false) << '\n'; break;
      case 4:
        if (!lb) lb = tifa_libs::ds::rightmost(tr.root);
        if (!lb) tifa_libs::fout << "-1\n";
        else if (lb->data <= x) tifa_libs::fout << lb->data << '\n';
        else if (auto pre = tr.prev(lb); !pre) tifa_libs::fout << "-1\n";
        else tifa_libs::fout << pre->data << '\n';
        break;
      case 5:
        if (!lb) tifa_libs::fout << "-1\n";
        else tifa_libs::fout << lb->data << '\n';
        break;
    }
  }
  return 0;
}
