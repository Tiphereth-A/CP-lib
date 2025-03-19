#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/graph/gomory_hu.hpp"

#include "../../../include/graph/alist.hpp"
#include "../base.hpp"

u32 q;
strn single_proceed(std::istream &fin) {
  std::stringstream ss;

  u32 n, m;
  fin >> n >> m;
  vec<edge_t<u64>> edges(m);
  for (auto &[w, u, v] : edges) {
    fin >> u >> v >> w;
    --u;
    --v;
  }
  tifa_libs::graph::alistw<u64> mct(n);
  vvecuu mat(n, vecuu(n, std::numeric_limits<u64>::max()));
  for (auto mct_edges = tifa_libs::graph::gomory_hu(n, edges); auto &&[w, u, v] : mct_edges) {
    mct.add_arc(u, v, w);
    mct.add_arc(v, u, w);
    mat[u][v] = mat[v][u] = w;
  }
  auto dfs = [&](auto &&dfs, u32 r, u32 u, u32 fa) -> void {
    for (auto [v, w] : mct.g[u])
      if (v != fa) mat[r][v] = std::min({mat[r][v], mat[r][u], w}), dfs(dfs, r, v, u);
    ;
  };
  flt_ (u32, r, 0, n) {
    dfs(dfs, r, r, -1_u32);
    mat[r][r] = 0;
  }
  map<u64, u32> cnts;
  flt_ (u32, i, 0, n)
    flt_ (u32, j, i + 1, n) ++cnts[mat[i][j]];
  fin >> q;
  for (u32 i = 0, x; i < q; ++i) {
    fin >> x;
    u32 ans = 0;
    for (auto &&[k, v] : cnts) {
      if (k > x) break;
      ans += v;
    }
    ss << ans << ' ';
  }

  return ss.str();
}

void test(strn data) {
  auto [fn_in, fn_ans] = tifa_libs::unittest::get_fname_in_ans("bzoj", "2229", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 t = 1;
  u32 testcase = 0;
  fin >> t;
  flt_ (u32, i, 0, t) {
    ++testcase;
    strn got = single_proceed(fin);
    while (isspace(got.back())) got.pop_back();
    strn want;
    flt_ (u32, j, 0, q + (i < t - 1)) {
      strn _;
      std::getline(fans, _);
      while (isspace(_.back())) _.pop_back();
      if (j) want += ' ';
      want += _;
    }
    while (isspace(want.back())) want.pop_back();
    check(got, want, check_param(testcase));
  }
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test("1"), test("13"); break;
    case tifa_libs::unittest::ts_example_01: test("2"), test("14"); break;
    case tifa_libs::unittest::ts_random_00: test("3"), test("15"); break;
    case tifa_libs::unittest::ts_random_01: test("4"); break;
    case tifa_libs::unittest::ts_random_02: test("5"); break;
    case tifa_libs::unittest::ts_random_03: test("6"); break;
    case tifa_libs::unittest::ts_random_04: test("7"); break;
    case tifa_libs::unittest::ts_random_05: test("8"); break;
    case tifa_libs::unittest::ts_random_06: test("9"); break;
    case tifa_libs::unittest::ts_random_07: test("10"); break;
    case tifa_libs::unittest::ts_random_08: test("11"); break;
    case tifa_libs::unittest::ts_random_09: test("12"); break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}