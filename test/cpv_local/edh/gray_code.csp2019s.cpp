// competitive-verifier: STANDALONE
// competitive-verifier: LOCALCASE test/cpv_local/_data/csp/2019s

#include "../../../src/edh/gray_code/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;

int main() {
  u32 n;
  u64 k;
  cin >> n >> k;
  auto x = gray_code(n, k).to_string().substr(64 - n);
  cout << x << '\n';
}