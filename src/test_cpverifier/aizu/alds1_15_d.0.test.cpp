#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_15_D"

#include "../../code/util/huffman_tree.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::string s;
  std::cin >> s;
  std::map<char, tifa_libs::u32> mp;
  for (char c : s) ++mp[c];
  tifa_libs::vec<char> dict;
  tifa_libs::vec<tifa_libs::u32> w;
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
  tifa_libs::util::huffman<tifa_libs::u32> hf(w);
  auto x = hf.encode();
  tifa_libs::u64 ans = 0;
  for (size_t i = 0; i < w.size(); ++i) ans += w[i] * x[i].size();
  std::cout << ans << '\n';
  return 0;
}
