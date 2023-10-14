#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"

#include "../../code/str/suffix_automaton.hpp"


int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::string s;
  std::cin >> s;
  tifa_libs::str::suffix_automaton sam(s.size());
  for (size_t i = 0; i < s.size(); ++i) sam.extend(s[i]);
  sam.buildparenttree(), sam.getsz();
  std::cout << sam.st[0].sz - 1;
  return 0;
}
