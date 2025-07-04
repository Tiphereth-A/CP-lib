#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/fast/rsort32.hpp"
#include "../../../include/graph/alist.hpp"
#include "../../../include/graph/euler_trail.hpp"
#include "../../../include/graph/kirchhoff.hpp"
#include "../../../include/lalg/ge_mat.hpp"
#include "../../../include/math/mint.hpp"
#include "../../../include/math/mint_s30.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_s30, 1'000'003>;
vec<mint> fact(200'005);

strn single_proceed(std::istream &fin) {
  std::stringstream ss;

  u32 n;
  fin >> n;
  graph::alist<true> g(n);
  for (u32 i = 0, s; i < n; ++i) {
    fin >> s;
    for (u32 j = 0, x; j < s; ++j) (fin >> x), g.add_arc(i, x - 1);
  }
  if (!g.cnt_arc) return "1\n";
  if (!graph::is_eulerian(g) || !g.deg_out[0]) return "0\n";
  vecb vis(n);
  auto f = [&](auto &&f, u32 x) -> void {
    for (auto v : g.g[x])
      if (!vis[v]) vis[v] = 1, f(f, v);
  };
  vis[0] = 1, f(f, 0);
  vecu ids(n, -1_u32), inv_ids;
  u32 cnt_ids = 0;
  flt_ (u32, i, 0, n)
    if (vis[i]) ids[i] = cnt_ids++, inv_ids.push_back(i);
  graph::amat<mint> mat(cnt_ids);
  flt_ (u32, id, 0, cnt_ids) {
    auto &tos = g.g[inv_ids[id]];
    if (tos.empty()) continue;
    ::sort(tos);
    u32 cnt = 1, pre = tos[0];
    flt_ (u32, j, 1, (u32)tos.size())
      if (tos[j] != pre) {
        mat.set_arc(id, ids[pre], cnt), pre = tos[j], cnt = 1;
      } else ++cnt;
    mat.set_arc(id, ids[pre], cnt);
  }
  auto is_0 = [](cT_(mint) x) { return x.val() == 0; };
  auto ge = [&](math::matrix<mint> &A, bool clear_u) { return math::ge_mat<mint, decltype(is_0), true>(A, is_0, clear_u); };
  mint ans = graph::kirchhoff<true>(mat, ids[0], ge) * fact[g.deg_out[inv_ids[0]]];
  flt_ (u32, i, 1, cnt_ids) ans *= fact[g.deg_out[inv_ids[i]] - 1];
  ss << ans << '\n';

  return ss.str();
}

void test(strn data) {
  // modified data, for easier test
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("bzoj", "3659m", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  fact[0] = 1;
  flt_ (u32, i, 1, (u32)fact.size()) fact[i] = fact[i - 1] * i;
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
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::ts_example_00: test("1"); break;
    case unittest::ts_example_01: test("2"); break;
    case unittest::ts_random_00: test("3"); break;
    case unittest::ts_random_01: test("4"); break;
    case unittest::ts_random_02: test("5"); break;
    case unittest::ts_random_03: test("6"); break;
    case unittest::ts_random_04: test("7"); break;
    case unittest::ts_random_05: test("8"); break;
    case unittest::ts_random_06: test("9"); break;
    case unittest::ts_random_07: test("10"); break;
    case unittest::ts_random_08: test("11"); break;  // from Luogu P5807
    case unittest::ts_random_09: break;
    default: break;
  }

  unittest::post_test();
}