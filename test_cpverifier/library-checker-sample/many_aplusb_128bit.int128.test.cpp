#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb_128bit"

#include "../../include/io/ios128.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 t;
  std::cin >> t;
  while (t--) {
    i128 a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
  }
  return 0;
}
