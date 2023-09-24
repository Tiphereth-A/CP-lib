#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations"

#include "../../code/math/leqs_solver.hpp"
#include "../../code/math/mat_ge_basic.hpp"
#include "../../code/math/mat_trans.hpp"
#include "../../code/math/mint_s30.hpp"

using mint = tifa_libs::math::mint_s30<998244353>;
using mat = tifa_libs::math::matrix<mint>;
using leqssolver = tifa_libs::math::LeqsSolver<mint>;

int main() {
  tifa_libs::u64 n, m;
  std::cin >> n >> m;
  mat a(n, m), b(n, 1);
  std::cin >> a >> b;

  auto is_0 = [](mint const &x) { return x == 0; };
  auto ge = [&is_0](mat &m, bool f) { return tifa_libs::math::ge_basic(m, is_0, f); };

  leqssolver leqs(a, b, ge);
  if (leqs.fe_cnt() < 0)
    std::cout << "-1\n";
  else {
    std::cout << leqs.fe_cnt() << '\n';
    std::cout << tifa_libs::math::transpose(leqs.solution()) << '\n';
    if (size_t fec = (size_t)leqs.fe_cnt(); fec > 0) {
      mat fe(fec, 1);
      for (size_t i = 0; i < fec; ++i) {
        fe(i, 0) = 1;
        std::cout << tifa_libs::math::transpose(leqs.solution(fe, ge)) << '\n';
        fe(i, 0) = 0;
      }
    }
  }
  return 0;
}
