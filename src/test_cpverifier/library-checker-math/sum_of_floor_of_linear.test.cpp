#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_floor_of_linear"

#include "../../code/math/exeuclid.hpp"

template <class T>
struct exeuclid_node {
  T u, r;
  T f;
  exeuclid_node(T u = 0, T r = 0, T f = 0) : u(u), r(r), f(f) {}
  friend exeuclid_node operator*(exeuclid_node CR l, exeuclid_node CR r) { return {l.u + r.u, l.r + r.r, l.f + r.f + l.u * r.r}; }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 t;
  std::cin >> t;
  exeuclid_node<u64> u(1, 0, 0), r(0, 1, 0);
  while (t--) {
    u32 n, m, a, b;
    std::cin >> n >> m >> a >> b;
    std::cout << tifa_libs::math::exeuclid<exeuclid_node<u64>>(a, m, b, n - 1, u, r).f + b / m << '\n';
  }
  return 0;
}
