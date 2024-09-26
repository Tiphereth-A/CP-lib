#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/math/simpson.hpp"

#include "../../../code/edh/discretization.hpp"
#include "../base.hpp"

using data_t = f128;
struct Node {
  int x, y, m;
  Node(int x = 0, int y = 0, int m = 0) : x(x), y(y), m(m) {}
};

vec<Node> v;
vecpt<data_t> seg;
template <class T>
T f(T pos) {
  seg.clear();
  for (auto [x, y, m] : v)
    if (x < pos && pos < x + m) seg.emplace_back(y, x + y + m - pos);
  if (seg.empty()) return 0;
  std::ranges::sort(seg);
  data_t ans = 0, lst = seg.front().first;
  for (auto &&[l, r] : seg)
    if (r - lst > 0) {
      ans += r - std::max(l, lst);
      lst = r;
    }
  return (T)ans;
}

CEXP data_t EPS = 1e-10l;

strn single_proceed(std::istream &fin) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(1);

  u32 n;
  fin >> n;
  v.clear();
  vec<Node> v_(n);
  for (auto &[x, y, m] : v_) fin >> y >> x >> m;
  std::ranges::sort(v_, [](Node CR l, Node CR r) { return l.m > r.m; });
  v.push_back(v_.front());
  fle_ (u32, i, 1, n - 1) {
    auto &&now = v_[i];
    if (now.m == 0) break;
    if (std::ranges::none_of(v, [&now](Node CR x) { return now.x >= x.x && now.x + now.m <= x.x + x.m && now.y >= x.y && now.y + now.m <= x.y + x.m && now.x + now.y + now.m <= x.x + x.y + x.m; })) v.push_back(now);
  }
  seg.reserve(n);

  vec<int> pos;
  pos.reserve(n * 2);
  for (auto &&[x, _, m] : v) {
    pos.push_back(x);
    pos.push_back(x + m);
  }
  pos = tifa_libs::uniq(pos);
  data_t ans = 0;
  tifa_libs::math::simpson_impl<f64, f<f64>> integral;

  fle_ (u32, i, 1, (u32)pos.size() - 1) ans += integral(pos[i - 1] + EPS, pos[i] - 2 * EPS, EPS);
  ss << ans;

  return ss.str();
}

void test(strn CR data) {
  auto [fn_in, fn_ans] = tifa_libs::unittest::get_fname_in_ans("bzoj", "2731", data);
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