#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/geo2d/cvh.hpp"

#include "../base.hpp"

using data_t = f64;
using Point2 = tifa_libs::geo::point<data_t>;
using ConvexHull2 = tifa_libs::geo::cvh<data_t>;

strn single_proceed(vec<Point2> CR vp) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(0);

  std::map<Point2, int> id;
  int cnt = 0;
  for (auto CR p : vp)
    if (!id[p]) id[p] = ++cnt;
  ConvexHull2 poly{vp};
  auto&& now = poly.vs;
  usz start = 0;
  int start_id = id[now[0]];
  fle_ (usz, i, 1, now.size() - 1)
    if (id[now[i]] < start_id) {
      start = i;
      start_id = id[now[i]];
    }
  fle_ (usz, i, start, now.size() - 1) ss << now[i].x << ", " << now[i].y << '\n';
  fle_ (usz, i, 0, start) ss << now[i].x << ", " << now[i].y << '\n';

  return ss.str();
}

void test(strn CR data) {
  strn path = "src/data/uva/675/" + data;
  std::ifstream fin(path + ".in"), fans(path + ".out");

  strn s;
  u32 testcase = 0;
  vec<Point2> vp;
  while (std::getline(fin, s))
    if (s.find(',') == strn::npos) {
    l1:;
      ++testcase;
      strn got = single_proceed(vp);
      isz cnt = std::ranges::count(got, ',');
      strn want;
      fle_ (isz, i, 1, cnt) {
        strn _;
        std::getline(fans, _);
        while (isspace(_.back())) _.pop_back();
        (want += _) += '\n';
      }
      while (isspace(got.back())) got.pop_back();
      while (isspace(want.back())) want.pop_back();
      check(got, want, check_param(testcase));
      vp.clear();
      std::getline(fans, want);
    } else {
      data_t x, y;
      char ch;
      std::stringstream{s} >> x >> ch >> y;
      vp.emplace_back(x, y);
    }
  if (!vp.empty()) goto l1;
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test("1"); break;
    case tifa_libs::unittest::ts_example_01: test("2"); break;
    case tifa_libs::unittest::ts_random_00: test("3"); break;
    case tifa_libs::unittest::ts_random_01: break;
    case tifa_libs::unittest::ts_random_02: break;
    case tifa_libs::unittest::ts_random_03: break;
    case tifa_libs::unittest::ts_random_04: break;
    case tifa_libs::unittest::ts_random_05: break;
    case tifa_libs::unittest::ts_random_06: break;
    case tifa_libs::unittest::ts_random_07: break;
    case tifa_libs::unittest::ts_random_08: break;
    case tifa_libs::unittest::ts_random_09: break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}