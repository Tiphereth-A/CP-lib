// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/3224

#include "../../../src/ds/bst/fhq/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
int main() {
  u32 n;
  cin >> n;
  fhq_treap<i32> treap;
  for (u32 i = 0, opt; i < n; ++i) {
    i32 x;
    cin >> opt >> x;
    switch (opt) {
      case 1:
        treap.insert(x);
        break;
      case 2:
        treap.erase(x);
        break;
      case 3:
        cout << (int)treap.rank(x) << '\n';
        break;
      case 4:
        cout << treap.kth((u32)x).value() << '\n';
        break;
      case 5:
        cout << treap.prev(x).value() << '\n';
        break;
      case 6:
        cout << treap.next(x).value() << '\n';
        break;
    }
  }
}