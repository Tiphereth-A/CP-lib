#define PROBLEM "https://judge.yosupo.jp/problem/assignment/"

#include "../../code/graph/ssp.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  u32 s = n + n, t = n + n + 1;
  tifa_libs::graph::ssp mcmf(n + n + 2, s, t);
  flt_ (u32, i, 0, n) mcmf.add(s, i, 1, 0);
  flt_ (u32, i, 0, n) mcmf.add(i + n, t, 1, 0);
  i32 x;
  flt_ (u32, i, 0, n)
    flt_ (u32, j, 0, n)
      std::cin >> x, mcmf.add(i, j + n, 1, x);
  auto [flow, cost] = mcmf();
  std::cout << cost << '\n';
  vecu ans(n);
  flt_ (u32, i, 0, n)
    for (auto v : mcmf.e[i])
      if (v.to < n + n && v.to >= n && v.w == 0) {
        ans[i] = v.to - n;
        break;
      }
  for (auto x : ans) std::cout << x << ' ';
  return 0;
}