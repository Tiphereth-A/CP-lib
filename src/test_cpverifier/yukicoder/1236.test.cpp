#define PROBLEM "https://yukicoder.me/problems/no/1236"

#include "../../code/math/rational.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int a, b;
  std::cin >> a >> b;
  tifa_libs::math::rational<int> c(a * 60 + b), d(720, 11), x(0);
  while (x < c) x += d;
  x -= c;
  std::cout << x.num * 60 / x.den << "\n";
  return 0;
}
