#define PROBLEM "https://www.luogu.com.cn/problem/P3804"

#include "../../code/str/suffix_automaton.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::string s, t;
  std::cin >> s >> t;
  tifa_libs::str::suffix_automaton sam;
  for (auto c : s) sam.extend(tifa_libs::u32(c - 'a'));
  std::cout << sam.lcs(t).second;
  return 0;
}
