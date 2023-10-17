#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../code/util/str2uint_mod.hpp"

constexpr tifa_libs::u64 MOD = tifa_libs::u64(1e9) + 1;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::string s, t;
  std::cin >> s >> t;
  std::cout << tifa_libs::str2uint_mod(s, MOD) + tifa_libs::str2uint_mod(t, MOD);
  return 0;
}
