#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/lalg/basis_r.hpp"

#include "../base.hpp"

struct Node {
  vec<double> v;
  int w;

  friend bool operator<(const Node &lhs, const Node &rhs) { return lhs.w == rhs.w ? lhs.v < rhs.v : lhs.w < rhs.w; }
};

strn single_proceed(std::istream &fin) {
  std::stringstream ss;

  set_eps(1e-4);
  vec<Node> a;
  u32 n, m;
  fin >> n >> m;
  tifa_libs::math::basisR<double> rbs(m);
  a.resize(n);
  for (auto &[v, w] : a) {
    v.resize(m);
    for (auto &j : v) fin >> j;
  }
  for (auto &[v, w] : a) fin >> w;
  std::sort(a.begin(), a.end());
  int cnt = 0, ans = 0;
  for (auto &&[v, w] : a) {
    if (rbs.insert(v)) {
      ++cnt;
      ans += w;
    }
  }
  ss << cnt << ' ' << ans << '\n';

  return ss.str();
}

void test(strn CR data) {
  auto [fn_in, fn_ans] = tifa_libs::unittest::get_fname_in_ans("bzoj", "4004", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 t = 1;
  u32 testcase = 0;
  // fin >> t;
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