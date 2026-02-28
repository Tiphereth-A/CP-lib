// competitive-verifier: STANDALONE

#include "../../../src/fast/rsort32/lib.hpp"
#include "../../../src/graph/chordal/lib.hpp"
#include "../../../src/graph/ds/alist/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
void test(strn data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("bzoj", "1006", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 n, m;
  fin >> n >> m;
  graph::alist g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    fin >> u >> v;
    --u;
    --v;
    g.add_arc(u, v);
    g.add_arc(v, u);
  }
  for (auto& i : g.g) ::sort(i);
  graph::chordal chd(g);
  u32 got = chd.chromatic_number();
  u32 want;
  fans >> want;
  check(got, want, check_param(data));
}

int main() {
  for (int i = 1; i <= 10; ++i) {
    timer_(test(std::to_string(i)));
  }
}