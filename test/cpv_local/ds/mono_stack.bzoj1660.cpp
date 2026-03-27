// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/1660

#include "../../../src/ds/mono_stack/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
int main() {
  u32 n;
  cin >> n;
  ds::mono_stack<u32, std::greater_equal<u32>> stk;
  u64 ans = 0;
  flt_ (u32, i, 0, n, x) {
    cin >> x;
    stk.pop_greater(x);
    ans += stk.size();
    stk.push_nocheck(x);
  }
  cout << ans << '\n';
}