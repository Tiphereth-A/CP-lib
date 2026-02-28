// competitive-verifier: STANDALONE

#include "../../../src/edh/gray_code/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
strn single_proceed(std::istream& fin) {
  std::stringstream ss;

  u32 n;
  u64 k;
  fin >> n >> k;
  auto x = gray_code(n, k).to_string().substr(64 - n);
  ss << x;

  return ss.str();
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("csp", "2019s", "code"s + data.data());
  std::ifstream fin(fn_in), fans(fn_ans);

  strn got = single_proceed(fin);
  strn want;
  std::getline(fans, want);
  while (isspace(got.back())) got.pop_back();
  while (isspace(want.back())) want.pop_back();
  check(got, want);
}

int main() {
  for (int i = 1; i <= 20; ++i) {
    timer_(test(std::to_string(i)));
  }
}