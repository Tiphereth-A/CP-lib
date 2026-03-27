// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/3659m

#include "../../../src/fast/rsort32/lib.hpp"
#include "../../../src/graph/ds/alist/lib.hpp"
#include "../../../src/graph/euler_trail/lib.hpp"
#include "../../../src/graph/kirchhoff/lib.hpp"
#include "../../../src/lalg/mat/ge/lib.hpp"
#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/ms/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using mint = math::mint<math::mint_ms, 1'000'003>;
vec<mint> fact(200'005);

int main() {
  fact[0] = 1;
  flt_ (u32, i, 1, (u32)fact.size()) fact[i] = fact[i - 1] * i;

  u32 t;
  cin >> t;
  while (t--) {
    u32 n;
    cin >> n;
    graph::alist<true> g(n);
    for (u32 i = 0, s; i < n; ++i) {
      cin >> s;
      for (u32 j = 0, x; j < s; ++j) (cin >> x), g.add_arc(i, x - 1);
    }
    if (!g.cnt_arc) {
      cout << "1\n";
      continue;
    }
    if (!graph::is_eulerian(g) || !g.deg_out[0]) {
      cout << "0\n";
      continue;
    }
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
    cout << ans << '\n';
  }
}