#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_totient_function"

#include "../../code/math/du_seive.hpp"
#include "../../code/math/isqrt.hpp"
#include "../../code/math/linear_phi_seive.hpp"
#include "../../code/math/mint_s63.hpp"

using mint = tifa_libs::math::mint_s63<998244353>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u64 n;
  std::cin >> n;
  tifa_libs::vec<mint> sphi;
  {
    auto _ = tifa_libs::math::linear_phi_seive(tifa_libs::math::isqrt(n));
    sphi.reserve(_.size());
    for (auto i : _) sphi.push_back(i);
    std::partial_sum(sphi.begin(), sphi.end(), sphi.begin());
  }
  auto sf = [sphi](tifa_libs::u64 x) -> mint { return sphi[x]; };
  auto sg = [](tifa_libs::u64 x) -> mint { return x; };
  auto sh = [](tifa_libs::u64 x) -> mint { return mint{x} * (x + 1) * ((mint::mod() + 1) / 2); };
  std::cout << tifa_libs::math::du_seive<mint, decltype(sf), decltype(sg), decltype(sh)>(sphi.size() - 1, sf, sg, sh)(n) << '\n';
  return 0;
}
