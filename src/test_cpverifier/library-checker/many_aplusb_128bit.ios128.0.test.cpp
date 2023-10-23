#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb_128bit"

#include "../../code/util/ios128.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 t;
  std::cin >> t;
  while (t--) {
    i128 a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
  }
  return 0;
}
