#define PROBLEM "https://www.luogu.com.cn/problem/P5657"

#include "../../code/util/gray_code.hpp"

void solve() {
  tifa_libs::u32 n;
  tifa_libs::u64 k;
  std::cin >> n >> k;
  auto x = tifa_libs::util::gray_code(n, k).to_string().substr(64 - n);
  std::cout << x;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve();
  return 0;
}