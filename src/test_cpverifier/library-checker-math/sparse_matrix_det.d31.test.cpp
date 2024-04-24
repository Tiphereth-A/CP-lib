#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/sparse_matrix_det"

#include "../../code/lalg/det_rd_mat.hpp"
#include "../../code/lalg/matsp.hpp"
#include "../../code/rand/gen.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_d31.hpp"

using mint = tifa_libs::math::mint_d31<-1>;
using mat = tifa_libs::math::matsp<mint>;

int main() {
  mint::set_mod(MOD);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u64 n, k;
  std::cin >> n >> k;
  mat a(n, n);
  for (u64 i = 0, x, y, z; i < k; ++i) {
    std::cin >> x >> y >> z;
    a(x, y) = z;
  }
  auto is0 = [](mint const &x) { return x.val() == 0; };
  tifa_libs::rand::Gen<std::uniform_int_distribution<u32>> gen(1, mint::mod() - 1);
  std::cout << tifa_libs::math::det_rd(a, gen, is0) << '\n';
  return 0;
}
