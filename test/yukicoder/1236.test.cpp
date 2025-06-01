#define PROBLEM "https://yukicoder.me/problems/no/1236"

#include "../../include/math/rational.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  int a, b;
  std::cin >> a >> b;
  math::rational<int> c(a * 60 + b), d(720, 11), x(0);
  while (x < c) x += d;
  x -= c;
  std::cout << x.num * 60 / x.den << "\n";
  return 0;
}
