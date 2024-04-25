#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/runenumerate/"

#include "../../code/io/fastio.hpp"
#include "../../code/str/run_hash.hpp"
//
#include "../../code/math/mint_2e61n1.hpp"
#include "../../code/str/hash_substr.hpp"

using mint = tifa_libs::math::mint_2e61n1;
using hashstr = tifa_libs::str::hash_substr<mint>;

int main() {
  strn s;
  tifa_libs::fin >> s;
  auto res = tifa_libs::str::run_hash<hashstr>(s);
  tifa_libs::fout << res.size() << '\n';
  for (auto& i : res) tifa_libs::fout << i << '\n';
  return 0;
}