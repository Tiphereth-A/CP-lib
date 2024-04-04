#define PROBLEM "https://judge.yosupo.jp/problem/division_of_polynomials"

#include "../../code/poly/divmod_fps.hpp"

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
  u32 n, m;
  std::cin >> n >> m;
  poly f(n), g(m);
  std::cin >> f >> g;
  auto [q, r] = tifa_libs::math::divmod_fps(f, g);
  if (q.size() == 1 && q[0].val() == 0) q.resize(0);
  if (r.size() == 1 && r[0].val() == 0) r.resize(0);
  std::cout << q.size() << ' ' << r.size() << '\n';
  std::cout << q << '\n';
  std::cout << r << '\n';
  return 0;
}
