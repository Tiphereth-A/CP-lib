// competitive-verifier: STANDALONE

#include "../../../src/fast/rsort32/lib.hpp"
#include "../../../src/graph/ds/alist/lib.hpp"
#include "../../../src/graph/euler_trail/lib.hpp"
#include "../../../src/graph/kirchhoff/lib.hpp"
#include "../../../src/lalg/mat/ge/lib.hpp"
#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/ms/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_ms, 1'000'003>;
vec<mint> fact(200'005);

strn single_proceed(std::istream& fin) {
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
  auto f = [&](auto&& f, u32 x) -> void {
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
    auto& tos = g.g[inv_ids[id]];
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
  auto ge = [&](math::matrix<mint>& A, bool clear_u) { return math::ge_mat<mint, decltype(is_0), true>(A, is_0, clear_u); };
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
  for (int i = 1; i <= 11; ++i) {
    timer_(test(std::to_string(i)));
  }
}