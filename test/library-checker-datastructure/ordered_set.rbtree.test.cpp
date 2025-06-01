#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"

#include "../../include/ds/rbtree.hpp"
#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"

using namespace tifa_libs;
int main() {
  u32 n, q;
  fin >> n >> q;
  ds::rbtree<u32> tr;
  flt_ (u32, i, 0, n, x) {
    fin >> x;
    tr.insert(x);
  }
  flt_ (u32, i, 0, q, t, x) {
    fin >> t >> x;
    auto lb = tr.lower_bound(x);
    switch (t) {
      case 0:
        if (!lb || lb->data != x) tr.insert(x);
        break;
      case 1:
        if (lb && lb->data == x) tr.erase(lb);
        break;
      case 2:
        if (tr.size() < x) fout << "-1\n";
        else fout << tr.find_by_order(x - 1)->data << '\n';
        break;
      case 3: fout << tr.order_of_key(x) + (lb ? lb->data == x : false) << '\n'; break;
      case 4:
        if (!lb) lb = ds::rightmost(tr.root);
        if (!lb) fout << "-1\n";
        else if (lb->data <= x) fout << lb->data << '\n';
        else if (auto pre = tr.prev(lb); !pre) fout << "-1\n";
        else fout << pre->data << '\n';
        break;
      case 5:
        if (!lb) fout << "-1\n";
        else fout << lb->data << '\n';
        break;
    }
  }
  return 0;
}
