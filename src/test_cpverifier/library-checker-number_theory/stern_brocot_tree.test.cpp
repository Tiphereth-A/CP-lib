#define PROBLEM "https://judge.yosupo.jp/problem/stern_brocot_tree"

#include "../../code/io/ios_pair.hpp"
#include "../../code/nt/sbt.hpp"

using sbt = tifa_libs::math::SBT<i64>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  int n;
  std::cin >> n;
  while (n--) {
    strn s;
    std::cin >> s;
    u64 k;
    i64 a, b, c, d;
    switch (s.front()) {
      case 'E':
        std::cin >> a >> b;
        {
          auto res = sbt(a, b).path();
          std::cout << res.size();
          for (i64 i : res) std::cout << ' ' << (i < 0 ? 'L' : 'R') << ' ' << (i < 0 ? -i : i);
          std::cout << '\n';
        }
        break;
      case 'D':
        std::cin >> k;
        {
          sbt s;
          char ch;
          for (i64 i = 0, _; i < (i64)k; ++i) {
            std::cin >> ch >> _;
            ch == 'R' ? s.movr(_) : s.movl(_);
          }
          std::cout << s.current() << '\n';
        }
        break;
      case 'L':
        std::cin >> a >> b >> c >> d;
        std::cout << sbt::lca(sbt(a, b), sbt(c, d)).current() << '\n';
        break;
      case 'A':
        std::cin >> d >> a >> b;
        {
          auto _ = sbt(a, b);
          if (_.dep() - d < 0) {
            std::cout << "-1\n";
            break;
          }
          _.movf(_.dep() - d);
          std::cout << _.current() << '\n';
        }
        break;
      case 'R':
        std::cin >> a >> b;
        {
          auto _ = sbt(a, b);
          std::cout << _.lbound() << ' ' << _.rbound() << '\n';
        }
        break;
    }
  }
  return 0;
}
