// competitive-verifier: STANDALONE

#include "../../../src/lalg/basis/r/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
struct Node {
  vec<double> v;
  int w;

  friend bool operator<(const Node& lhs, const Node& rhs) { retif_((lhs.w == rhs.w), lhs.v < rhs.v, lhs.w < rhs.w); }
};

strn single_proceed(std::istream& fin) {
  std::stringstream ss;

  set_eps(1e-4);
  vec<Node> a;
  u32 n, m;
  fin >> n >> m;
  math::basis_r<double> rbs(m);
  a.resize(n);
  for (auto& [v, w] : a) {
    v.resize(m);
    for (auto& j : v) fin >> j;
  }
  for (auto& [v, w] : a) fin >> w;
  std::sort(begin(a), end(a));
  int cnt = 0, ans = 0;
  for (auto&& [v, w] : a) {
    if (rbs.insert(v)) {
      ++cnt;
      ans += w;
    }
  }
  ss << cnt << ' ' << ans << '\n';

  return ss.str();
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("bzoj", "4004", data);
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
  for (int i = 1; i <= 10; ++i) {
    timer_(test(std::to_string(i)));
  }
}