#define PROBLEM "https://judge.yosupo.jp/problem/stern_brocot_tree"

#include "../../include/io/ios_pair.hpp"
#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/nt/sbt.hpp"

using namespace tifa_libs;
using sbt = math::sbt<i64>;

int main() {
  int n;
  fin >> n;
  while (n--) {
    strn s;
    fin >> s;
    u64 k;
    i64 a, b, c, d;
    switch (s.front()) {
      case 'E':
        fin >> a >> b;
        {
          auto res = sbt(a, b).path();
          fout << res.size();
          for (i64 i : res) fout << ' ' << (i < 0 ? 'L' : 'R') << ' ' << (i < 0 ? -i : i);
          fout << '\n';
        }
        break;
      case 'D':
        fin >> k;
        {
          sbt s;
          char ch;
          for (i64 i = 0, _; i < (i64)k; ++i) {
            fin >> ch >> _;
            ch == 'R' ? s.movr(_) : s.movl(_);
          }
          fout << s.current() << '\n';
        }
        break;
      case 'L':
        fin >> a >> b >> c >> d;
        fout << sbt::lca(sbt(a, b), sbt(c, d)).current() << '\n';
        break;
      case 'A':
        fin >> d >> a >> b;
        {
          auto _ = sbt(a, b);
          if (_.dep() - d < 0) {
            fout << "-1\n";
            break;
          }
          _.movf(_.dep() - d);
          fout << _.current() << '\n';
        }
        break;
      case 'R':
        fin >> a >> b;
        {
          auto _ = sbt(a, b);
          fout << _.lbound() << ' ' << _.rbound() << '\n';
        }
        break;
    }
  }
  return 0;
}
