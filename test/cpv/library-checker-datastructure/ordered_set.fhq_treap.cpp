// competitive-verifier: PROBLEM "https://judge.yosupo.jp/problem/ordered_set"

#include "../../../src/ds/bst/fhq/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
int main() {
  u32 n, q;
  fin_uint >> n >> q;
  fhq_treap<u32> treap;
  flt_ (u32, i, 0, n, x) {
    fin_uint >> x;
    treap.insert(x);
  }
  flt_ (u32, i, 0, q, t, x) {
    fin_uint >> t >> x;
    auto it = treap.find(x);
    switch (t) {
      case 0:
        if (it == end(treap.data)) treap.insert(x);
        break;
      case 1:
        if (it != end(treap.data)) treap.erase(x);
        break;
      case 2:
        if (auto _ = treap.kth(x); !_) fout << "-1\n";
        else fout << _.value() << '\n';
        break;
      case 3:
        fout << treap.rank(x) - (it == end(treap.data)) << '\n';
        break;
      case 4:
        if (it != end(treap.data)) fout << it->val << '\n';
        else if (auto _ = treap.prev(x); !_) fout << "-1\n";
        else fout << _.value() << '\n';
        break;
      case 5:
        if (it != end(treap.data)) fout << it->val << '\n';
        else if (auto _ = treap.next(x); !_) fout << "-1\n";
        else fout << _.value() << '\n';
        break;
    }
  }
  return 0;
}
