#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"

using namespace tifa_libs;
int main() {
  u32 n, q;
  fin >> n >> q;
  __gnu_pbds::tree<u32, __gnu_pbds::null_type, std::less<u32>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> tr;
  flt_ (u32, i, 0, n, x) {
    fin >> x;
    tr.insert(x);
  }
  flt_ (u32, i, 0, q, t, x) {
    fin >> t >> x;
    auto lb = tr.lower_bound(x);
    switch (t) {
      case 0:
        if (lb == tr.end() || *lb != x) tr.insert(x);
        break;
      case 1:
        if (lb != tr.end() && *lb == x) tr.erase(lb);
        break;
      case 2:
        if (tr.size() < x) fout << "-1\n";
        else fout << *tr.find_by_order(x - 1) << '\n';
        break;
      case 3: fout << tr.order_of_key(x) + (lb != tr.end() ? *lb == x : false) << '\n'; break;
      case 4:
        if (lb == tr.end()) lb = tr.rbegin();
        if (lb == tr.end()) fout << "-1\n";
        else if (*lb <= x) fout << *lb << '\n';
        else if (lb == tr.begin()) fout << "-1\n";
        else fout << *std::prev(lb) << '\n';
        break;
      case 5:
        if (lb == tr.end()) fout << "-1\n";
        else fout << *lb << '\n';
        break;
    }
  }
  return 0;
}
