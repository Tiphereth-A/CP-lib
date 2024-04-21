#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/runenumerate/"

#include "../../code/io/fastio.hpp"
#include "../../code/str/run_hash.hpp"

constexpr u32 MOD0 = 998244353;
constexpr u32 MOD1 = 1000000007;

#include "../../code/math/mint_d63.hpp"
#include "../../code/str/hash_substr2.hpp"

using mint0 = tifa_libs::math::mint_d63<-1>;
using mint1 = tifa_libs::math::mint_d63<-2>;
using hashstr = tifa_libs::str::hash_substr2<mint0, mint1>;

int main() {
  mint0::set_mod(MOD0);
  mint1::set_mod(MOD1);
  strn s;
  tifa_libs::fin >> s;
  auto res = tifa_libs::str::run_hash<hashstr>(s);
  tifa_libs::fout << res.size() << '\n';
  for (auto& i : res) tifa_libs::fout << i << '\n';
  return 0;
}