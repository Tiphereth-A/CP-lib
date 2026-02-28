// competitive-verifier: STANDALONE

#include "../../../src/graph/ds/alist/lib.hpp"
#include "../../../src/graph/sp/bm/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
u32 q;
strn single_proceed(std::istream& fin) {
  std::stringstream ss;

  u32 n, m;
  fin >> n >> m;
  graph::alistw<f64> g(n + 1);
  flt_ (u32, i, 0, m, u, v) {
    f64 w;
    fin >> u >> v >> w;
    g.add_arc(u, v, w);
  }
  f64 l = -1e7, r = 1e7, mid;
  auto chk = [&g](f64 x) {
    vec<f64> dis(g.size());
    flt_ (u32, i, 1, g.size())
      for (auto& [v, w] : g[i]) w -= x;
    bool flag = false;
    flt_ (u32, i, 1, g.size())
      if (!graph::bellman_ford(g, i, fn_0, dis)) {
        flag = true;
        break;
      }
    flt_ (u32, i, 1, g.size())
      for (auto& [v, w] : g[i]) w += x;
    return flag;
  };
  while (r - l > 1e-10) {
    mid = std::midpoint(l, r);
    (chk(mid) ? r : l) = mid;
  }
  ss << std::fixed << std::setprecision(8) << l;

  return ss.str();
}

void test(strn data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("bzoj", "1486", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  strn got = single_proceed(fin);
  while (isspace(got.back())) got.pop_back();
  strn want;
  std::getline(fans, want);
  while (isspace(want.back())) want.pop_back();
  check(got, want);
}

int main() {
  for (int i = 1; i <= 10; ++i) {
    timer_(test(std::to_string(i)));
  }
}