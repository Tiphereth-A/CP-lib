#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_7_G"
#define ERROR 0.00001

#include "../../code/geo2d/circle.hpp"
#include "../../code/geo2d/extan_cc.hpp"
#include "../../code/geo2d/intan_cc.hpp"
#include "../../code/geo2d/line.hpp"

using line = tifa_libs::geo2d::line<double>;
using circ = tifa_libs::geo2d::circle<double>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(12);
  circ c1, c2;
  std::cin >> c1 >> c2;
  auto exl = extan_CC(c1, c2), inl = intan_CC(c1, c2);
  tifa_libs::vec<line> ans;
  if (exl.has_value()) {
    ans.push_back(exl.value().first);
    ans.push_back(exl.value().second);
  }
  if (inl.has_value()) {
    ans.push_back(inl.value().first);
    ans.push_back(inl.value().second);
  }
  std::sort(ans.begin(), ans.end());
  ans.erase(std::unique(ans.begin(), ans.end()), ans.end());
  for (auto &i : ans) std::cout << i << '\n';
  return 0;
}
