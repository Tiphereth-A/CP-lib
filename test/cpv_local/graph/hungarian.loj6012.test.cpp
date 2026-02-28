// competitive-verifier: STANDALONE

#include "../../../src/graph/nf/hungarian/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
strn single_proceed(std::istream& fin) {
  std::stringstream ss;

  u32 n;
  fin >> n;
  vveci c1(n, veci(n));
  for (auto& i : c1) fin >> i;
  auto c2 = c1;
  for (auto& i : c2)
    for (auto& j : i) j = -j;
  ss << graph::hungarian(c1).back() << '\n';
  ss << -graph::hungarian(c2).back() << '\n';

  return ss.str();
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("loj", "6012", "job"s + data.data());
  std::ifstream fin(fn_in), fans(fn_ans);

  {
    strn got = single_proceed(fin);
    strn want, want2;
    std::getline(fans, want);
    std::getline(fans, want2);
    while (isspace(got.back())) got.pop_back();
    while (isspace(want.back())) want.pop_back();
    while (isspace(want2.back())) want2.pop_back();
    want = want + '\n' + want2;
    check(got, want);
  }
}

int main() {
  for (int i = 0; i <= 8; ++i) {
    timer_(test(std::to_string(i)));
  }
}