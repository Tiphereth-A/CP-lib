#define PROBLEM "https://judge.yosupo.jp/problem/stern_brocot_tree"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/nt/sbt.hpp"

using namespace tifa_libs;
using sbt = math::sbt<u64>;

int main() {
  int n;
  fin_uint >> n;
  while (n--) {
    strn s;
    fin >> s;
    u64 k;
    u64 a, b, c, d;
    switch (s.front()) {
      case 'E': {
        fin_uint >> a >> b;
        vec<std::pair<char, u64>> path;
        sbt::walk_to(a, b, [&path](bool dir, u64 step) { path.emplace_back(dir ? 'R' : 'L', step); });
        fout << path.size();
        for (auto [dir, step] : path) fout << ' ' << dir << ' ' << step;
        fout << '\n';
      } break;
      case 'D': {
        fin_uint >> k;
        sbt s;
        char ch;
        flt_ (u64, i, 0, k, _) {
          fin >> ch >> _;
          ch == 'R' ? s.movr(_) : s.movl(_);
        }
        fout << s.x << ' ' << s.y << '\n';
      } break;
      case 'L': {
        fin_uint >> a >> b >> c >> d;
        auto s = sbt::walk_to_lca(a, b, c, d);
        fout << s.x << ' ' << s.y << '\n';
      } break;
      case 'A': {
        fin_uint >> d >> a >> b;
        vec<std::pair<char, u64>> path;
        sbt::walk_to(a, b, [&path](bool dir, u64 step) { path.emplace_back(dir ? 'R' : 'L', step); });
        for (auto it = path.begin(); it != path.end(); ++it) {
          if (it->second <= d) d -= it->second;
          else {
            it->second = d, d = 0;
            path.erase(++it, path.end());
            break;
          }
        }
        if (d) fout << "-1\n";
        else {
          sbt s;
          for (auto [dir, step] : path)
            if (dir == 'R') s.movr(step);
            else s.movl(step);
          fout << s.x << ' ' << s.y << '\n';
        }
      } break;
      case 'R': {
        fin_uint >> a >> b;
        auto _ = sbt::walk_to(a, b);
        fout << _.lx << ' ' << _.ly << ' ' << _.rx << ' ' << _.ry << '\n';
      } break;
    }
  }
  return 0;
}
