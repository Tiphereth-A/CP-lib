#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/runenumerate/"

#include "../../code/io/fastio.hpp"
#include "../../code/str/run_zfunc.hpp"

int main() {
  strn s;
  tifa_libs::fin >> s;
  auto res = tifa_libs::str::run_zfunc(s);
  tifa_libs::fout << res.size() << '\n';
  for (auto& i : res) tifa_libs::fout << i << '\n';
  return 0;
}