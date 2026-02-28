// competitive-verifier: STANDALONE

#include "../../../src/ds/st/basic/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
i64 f(i64 x, i64 y) { return std::max(x, y); }

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("bzoj", "1012", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 m, d;
  fin >> m >> d;
  ds::st_array<i64, f> st;
  char op;
  i64 t = 0, u;
  for (u32 i = 1; i <= m; ++i) {
    fin >> op >> u;
    if (op == 'A') st.push_back((u % d + t + d) % d);
    else {
      t = st.query(u32(st.size() - u));
      i64 ans_t;
      fans >> ans_t;
      check(t, ans_t, check_param(i));
    }
  }
}

int main() {
  for (int i = 1; i <= 8; ++i) {
    timer_(test(std::to_string(i)));
  }
}