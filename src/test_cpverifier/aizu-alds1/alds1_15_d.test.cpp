#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_15_D"

#include "../../code/edh/huffman_tree.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  strn s;
  std::cin >> s;
  std::map<char, u32> mp;
  for (char c : s) ++mp[c];
  vec<char> dict;
  vecu w;
  for (auto [k, v] : mp) {
    dict.push_back(k);
    w.push_back(v);
  }
  if (w.size() < 3) {
    if (w.size() == 1)
      std::cout << w[0] << "\n";
    else
      std::cout << w[0] + w[1] << "\n";
    return 0;
  }
  tifa_libs::huffman<u32> hf(w);
  auto x = hf.encode();
  u64 ans = 0;
  flt_ (u32, i, 0, (u32)w.size()) ans += w[i] * x[i].size();
  std::cout << ans << '\n';
  return 0;
}
