// competitive-verifier: LOCALCASE test/cpv_local/_data/uva/675

#include "../../../src/geo2d/ds/cvh/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f64;
using Point2 = point<data_t>;
using ConvexHull2 = cvh<data_t>;

int main() {
  cout << std::fixed << std::setprecision(0);

  strn s;
  vec<Point2> vp;

  while (std::getline(cin, s)) {
    if (s.find(',') == strn::npos) {
      if (vp.empty()) continue;

      map<Point2, int> id;
      int cnt = 0;
      for (auto CR p : vp)
        if (!id[p]) id[p] = ++cnt;
      ConvexHull2 poly{vp};
      auto&& now = poly.vs;
      usz start = 0;
      int start_id = id[now[0]];
      flt_ (usz, i, 1, now.size())
        if (id[now[i]] < start_id) {
          start = i;
          start_id = id[now[i]];
        }
      flt_ (usz, i, start, now.size()) cout << now[i].x << ", " << now[i].y << '\n';
      flt_ (usz, i, 0, start + 1) cout << now[i].x << ", " << now[i].y << '\n';
      cout << '\n';

      vp.clear();
    } else {
      data_t x, y;
      char ch;
      std::stringstream{s} >> x >> ch >> y;
      vp.emplace_back(x, y);
    }
  }

  if (!vp.empty()) {
    map<Point2, int> id;
    int cnt = 0;
    for (auto CR p : vp)
      if (!id[p]) id[p] = ++cnt;
    ConvexHull2 poly{vp};
    auto&& now = poly.vs;
    usz start = 0;
    int start_id = id[now[0]];
    flt_ (usz, i, 1, now.size())
      if (id[now[i]] < start_id) {
        start = i;
        start_id = id[now[i]];
      }
    flt_ (usz, i, start, now.size()) cout << now[i].x << ", " << now[i].y << '\n';
    flt_ (usz, i, 0, start + 1) cout << now[i].x << ", " << now[i].y << '\n';
  }
}