// competitive-verifier: STANDALONE

#include "../../../src/ds/bst/fhq/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("bzoj", "3224", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 n;
  fin >> n;
  ds::fhq_treap<i32> treap;
  for (u32 i = 0, opt; i < n; ++i) {
    i32 x, got, want;
    fin >> opt >> x;
    switch (opt) {
      case 1:
        treap.insert(x);
        break;
      case 2:
        treap.erase(x);
        break;
      case 3:
        got = (int)treap.rank(x);
        fans >> want;
        break;
      case 4:
        got = treap.kth((u32)x).value();
        fans >> want;
        break;
      case 5:
        got = treap.prev(x).value();
        fans >> want;
        break;
      case 6:
        got = treap.next(x).value();
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