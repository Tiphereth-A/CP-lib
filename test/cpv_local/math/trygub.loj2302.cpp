// competitive-verifier: LOCALCASE test/cpv_local/_data/loj/2302

#include "../../../src/math/ds/trygub/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;

int main() {
  u32 n, t1, t2, t3;
  cin >> n >> t1 >> t2 >> t3;
  trygub_num<2> num;
  flt_ (u32, i, 0, n) {
    int op;
    cin >> op;
    if (op == 1) {
      int a, b;
      cin >> a >> b;
      num.add(a, b);
    } else {
      int k;
      cin >> k;
      cout << num.get(k) << '\n';
    }
  }
}