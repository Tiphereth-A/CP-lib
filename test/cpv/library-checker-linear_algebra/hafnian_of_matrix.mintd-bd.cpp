#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/hafnian_of_matrix"

#include "../../../src/lalg/ds/mat/lib.hpp"
#include "../../../src/lalg/mat/hafnian/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/math/ds/mint/bd/lib.hpp"

using namespace tifa_libs;
using mint = mint_bd<__LINE__>;
using mat = tifa_libs::matrix<mint>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  mat a(n, n);
  std::cin >> a;
  std::cout << tifa_libs::hafnian(a);
  return 0;
}
