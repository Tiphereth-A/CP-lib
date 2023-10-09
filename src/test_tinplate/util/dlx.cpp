#define PROBLEM "https://www.luogu.com.cn/problem/P4929"

#include "../../code/util/dlx.hpp"

void solve() {
  tifa_libs::u32 n, m;
  std::cin >> n >> m;
  tifa_libs::vvec<bool> maps(n, tifa_libs::vec<bool>(m));
  for (size_t i = 0, x; i < n; ++i)
    for (size_t j = 0; j < m; ++j) {
      std::cin >> x;
      maps[i][j] = x;
    }
  auto res = tifa_libs::util::DLX(maps).dance([]([[maybe_unused]] auto const &x) {});
  if (res.has_value())
    for (auto i : res.value()) std::cout << i << ' ';
  else
    std::cout << "No Solution!";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve();
  return 0;
}