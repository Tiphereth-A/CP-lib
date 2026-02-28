// competitive-verifier: STANDALONE

#include "../../../src/graph/min_cycle_mean/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
u32 q;
strn single_proceed(std::istream& fin) {
  std::stringstream ss;

  u32 n, m;
  fin >> n >> m;
  vec<edge_t<f64>> e(m);
  for (auto& [w, u, v] : e) fin >> u >> v >> w;
  ss << std::fixed << std::setprecision(8) << graph::min_cycle_mean(e, n + 1);

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