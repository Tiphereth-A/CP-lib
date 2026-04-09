// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_10_A
#include "../../../src/util/alias/num/lib.hpp"
#include "../../../src/util/bitset_getdata/lib.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  std::bitset<32> bs;
  bitset_getdata<32>::getword(bs, 0) = n;
  std::cout << bs << '\n';
  std::cout << ~bs << '\n';
  std::cout << (bs << 1) << '\n';
  std::cout << (bs >> 1) << '\n';
  return 0;
}