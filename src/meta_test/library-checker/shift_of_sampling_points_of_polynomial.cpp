#define PROBLEM "https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial"

#include "../../code/poly/ctsh_fps.hpp"

constexpr u32 MOD = 998244353;

#define GENTCs_p3ntts
#define GENTCs_p3nttd0
#define GENTCs_pcntts
#define GENTCs_pmtts
#define GENTCs_pmttd0
#define GENTCs_pntt

int main() {
#define GENTCs_p3nttd1
#define GENTCs_pmttd1
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m, c;
  std::cin >> n >> m >> c;
  poly a(n);
  std::cin >> a;
  std::cout << tifa_libs::math::ctsh_fps(a, mint(c), m) << '\n';
  return 0;
}
