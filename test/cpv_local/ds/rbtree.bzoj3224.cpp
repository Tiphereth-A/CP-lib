// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/3224

#include "../../../src/ds/bst/rbt/lib.hpp"
#include "../../../src/ds/bt_trv/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
int main() {
  u32 m;
  cin >> m;
  rbtree<int> bt;

  for (u32 i = 0, opt; i < m; ++i) {
    int x;
    cin >> opt >> x;
    switch (opt) {
      case 1:
        bt.insert(x);
        break;
      case 2:
        bt.erase(x);
        break;
      case 3:
        cout << int(bt.order_of_key(x) + 1) << '\n';
        break;
      case 4:
        cout << bt.find_by_order((u32)x - 1)->data << '\n';
        break;
      case 5: {
        auto it = bt.lower_bound(x);
        cout << (it ? bt.prev(it) : rightmost(bt.root))->data << '\n';
      } break;
      case 6:
        cout << bt.upper_bound(x)->data << '\n';
        break;
    }
  }
}