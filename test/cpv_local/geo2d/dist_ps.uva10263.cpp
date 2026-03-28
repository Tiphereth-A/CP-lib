// competitive-verifier: LOCALCASE test/cpv_local/_data/uva/10263

#include "../../../src/geo2d/dis/ps/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f64;
using Point2 = point<data_t>;
using Line2 = line<data_t>;

int main() {
  cout << std::fixed << std::setprecision(4);

  data_t x, y;
  while (cin >> x >> y) {
    Point2 m{x, y};
    u32 n;
    cin >> n;
    vec<Line2> l;
    l.reserve(n + 1);
    Point2 prev, now;
    cin >> prev;
    flt_ (u32, i, 1, n + 1) {
      cin >> now;
      l.emplace_back(prev, now);
      prev = now;
    }
    if (!n) {
      cout << prev.x << '\n'
           << prev.y << '\n';
      continue;
    }
    data_t ans = std::numeric_limits<data_t>::max();
    Point2 ansP;
    for (auto CR i : l) {
      auto pp = dist_PS_P(m, i);
      data_t d = dist_PP(pp, m);
      if (is_lt(d, ans)) {
        ans = d;
        ansP = pp;
      }
    }
    cout << ansP.x << '\n'
         << ansP.y << '\n';
  }
}