// competitive-verifier: LOCALCASE test/cpv_local/_data/loj/6012

#include "../../../src/graph/nf/hungarian/lib.hpp"
#include "../../../src/io/container/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;

int main() {
  u32 n;
  cin >> n;
  vveci c1(n, veci(n));
  for (auto& i : c1) cin >> i;
  auto c2 = c1;
  for (auto& i : c2)
    for (auto& j : i) j = -j;
  cout << graph::hungarian(c1).back() << '\n';
  cout << -graph::hungarian(c2).back() << '\n';
}