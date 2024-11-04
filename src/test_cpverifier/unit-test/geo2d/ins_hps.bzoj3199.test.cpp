#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/geo2d/ins_hps.hpp"

#include "../../../code/geo2d/proj.hpp"
#include "../../../code/graph/alist.hpp"
#include "../../../code/graph/dijkstra.hpp"
#include "../base.hpp"

using data_t = f128;
using Point2 = tifa_libs::geo::point<data_t>;
using Line2 = tifa_libs::geo::line<data_t>;

strn single_proceed(std::istream &fin) {
  std::stringstream ss;

  u32 n;
  fin >> n;
  Point2 s, t;
  fin >> t >> s;
  vec<Point2> vp(n);
  for (auto &p : vp) fin >> p;
  if (!n) return "0\n";
  map<Point2, u32> ids;
  flt_ (u32, i, 0, n) ids[vp[i]] = i + 1;
  u32 pos = 0;
  vecb skip(n);
  {
    data_t len = std::numeric_limits<data_t>::max();
    flt_ (u32, i, 0, n) {
      if (vp[i].x > t.x || vp[i].y > t.y) skip[i] = 1;
      if (data_t now = tifa_libs::geo::dist_PP(vp[i], s); len > now) len = now, pos = i;
    }
  }
  vec<Line2> vl;
  vl.emplace_back(Point2(0, 0), Point2(t.x, 0));
  vl.emplace_back(Point2(t.x, 0), Point2(t.x, t.y));
  vl.emplace_back(Point2(t.x, t.y), Point2(0, t.y));
  vl.emplace_back(Point2(0, t.y), Point2(0, 0));
  tifa_libs::graph::alistw<u32> g(n + 1);
  flt_ (u32, i, 0, n) {
    if (skip[i]) continue;
    vl.resize(4);
    flt_ (u32, j, 0, n) {
      if (j == i || skip[j]) continue;
      Point2 mid = mid_point(vp[i], vp[j]), v = rot90(vp[j] - vp[i]);
      vl.emplace_back(mid, mid + v);
    }
    auto res = tifa_libs::geo::ins_hPs(vl);
    flt_ (u32, j, 0, res.size()) {
      Line2 l{res.vs[j], res.vs[res.next(j)]};
      u32 id = ids[reflect(l, vp[i])];
      if (id) --id;
      else id = n;
      g.add_arc(i, id, 1);
      g.add_arc(id, i, 1);
    }
  }
  ss << tifa_libs::graph::dijkstra(g, pos, fn_0)[n] << '\n';

  return ss.str();
}

void test(strn CR data) {
  auto [fn_in, fn_ans] = tifa_libs::unittest::get_fname_in_ans("bzoj", "3199", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 t = 1;
  u32 testcase = 0;
  fin >> t;
  flt_ (u32, i, 0, t) {
    ++testcase;
    strn got = single_proceed(fin);
    strn want;
    std::getline(fans, want);
    while (isspace(got.back())) got.pop_back();
    while (isspace(want.back())) want.pop_back();
    check(got, want, check_param(testcase));
  }
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test("1"); break;
    case tifa_libs::unittest::ts_example_01: test("2"); break;
    case tifa_libs::unittest::ts_random_00: test("3"); break;
    case tifa_libs::unittest::ts_random_01: test("4"); break;
    case tifa_libs::unittest::ts_random_02: test("5"); break;
    case tifa_libs::unittest::ts_random_03: test("6"); break;
    case tifa_libs::unittest::ts_random_04: test("7"); break;
    case tifa_libs::unittest::ts_random_05: test("8"); break;
    case tifa_libs::unittest::ts_random_06: test("9"); break;
    case tifa_libs::unittest::ts_random_07: test("10"); break;
    case tifa_libs::unittest::ts_random_08: break;
    case tifa_libs::unittest::ts_random_09: break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}