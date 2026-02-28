#include <utility>
// 返回 F(n) 和 F(n + 1)
std::pair<int, int> fib(int n) {
  if (n == 0) return {0, 1};
  auto [a, b] = fib(n / 2);
  int c = a * (2 * b - a), d = a * a + b * b;
  if (n & 1)
    return {d, c + d};
  else
    return {c, d};
}