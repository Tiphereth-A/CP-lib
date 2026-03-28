// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/1012

#include "../../../src/ds/rmq/st/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
i64 f(i64 x, i64 y) { return std::max(x, y); }
int main() {
  u32 m, d;
  cin >> m >> d;
  st_array<i64, f> st;
  char op;
  i64 t = 0, u;
  for (u32 i = 1; i <= m; ++i) {
    cin >> op >> u;
    if (op == 'A') st.push_back((u % d + t + d) % d);
    else cout << (t = st.query(u32(st.size() - u))) << '\n';
  }
}