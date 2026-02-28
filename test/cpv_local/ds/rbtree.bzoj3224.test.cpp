// competitive-verifier: STANDALONE

#include "../../../src/ds/bst/rbt/lib.hpp"
#include "../../../src/ds/bt_trv/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("bzoj", "3224", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 n, m;
  fin >> n >> m;
  ds::rbtree<int> bt;

  for (u32 i = 0, opt; i < m; ++i) {
    int x, got, want;
    fin >> opt >> x;
    switch (opt) {
      case 1:
        bt.insert(x);
        break;
      case 2:
        bt.erase(x);
        break;
      case 3:
        got = int(bt.order_of_key(x) + 1);
        fans >> want;
        break;
      case 4:
        got = bt.find_by_order((u32)x - 1)->data;
        fans >> want;
        break;
      case 5: {
        auto it = bt.lower_bound(x);
        got = (it ? bt.prev(it) : rightmost(bt.root))->data;
        fans >> want;
      } break;
      case 6:
        got = bt.upper_bound(x)->data;
        fans >> want;
        break;
    }
    check(got, want, check_param(i), check_param(opt), check_param(x));
  }
}

int main() {
  for (int i = 1; i <= 10; ++i) {
    timer_(test(std::to_string(i)));
  }
}