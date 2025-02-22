#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"

#include "../../code/ds/fhq_treap.hpp"
#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"

int main() {
  u32 n, q;
  tifa_libs::fin >> n >> q;
  tifa_libs::ds::fhq_treap<u32> treap;
  flt_ (u32, i, 0, n, x) {
    tifa_libs::fin >> x;
    treap.insert(x);
  }
  flt_ (u32, i, 0, q, t, x) {
    tifa_libs::fin >> t >> x;
    auto it = treap.find(x);
    switch (t) {
      case 0:
        if (it == treap.data.end()) treap.insert(x);
        break;
      case 1:
        if (it != treap.data.end()) treap.erase(x);
        break;
      case 2:
        if (auto _ = treap.kth(x); !_) tifa_libs::fout << "-1\n";
        else tifa_libs::fout << _.value() << '\n';
        break;
      case 3:
        tifa_libs::fout << treap.rank(x) - (it == treap.data.end()) << '\n';
        break;
      case 4:
        if (it != treap.data.end()) tifa_libs::fout << it->val << '\n';
        else if (auto _ = treap.prev(x); !_) tifa_libs::fout << "-1\n";
        else tifa_libs::fout << _.value() << '\n';
        break;
      case 5:
        if (it != treap.data.end()) tifa_libs::fout << it->val << '\n';
        else if (auto _ = treap.next(x); !_) tifa_libs::fout << "-1\n";
        else tifa_libs::fout << _.value() << '\n';
        break;
    }
  }
  return 0;
}
