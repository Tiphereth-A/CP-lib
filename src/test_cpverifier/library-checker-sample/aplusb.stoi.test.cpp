#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../code/fast/str2uint_mod.hpp"
#include "../../code/fast/u32tostr.hpp"

constexpr u64 MOD = u64(1e9) + 1;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  strn s, t;
  std::cin >> s >> t;
  char ans[16] = {0};
  tifa_libs::u32tostr(tifa_libs::str2uint_mod(s, MOD) + tifa_libs::str2uint_mod(t, MOD), ans);
  std::cout << ans;
  return 0;
}
