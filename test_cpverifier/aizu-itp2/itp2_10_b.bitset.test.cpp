#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_10_B"

#include "../../include/util/alias_num.hpp"
#include "../../include/util/bitset_getdata.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 a, b;
  std::cin >> a >> b;
  std::bitset<32> ba, bb;
  tifa_libs::bitset_getdata<32>::getword(ba, 0) = a;
  tifa_libs::bitset_getdata<32>::getword(bb, 0) = b;
  std::cout << (ba & bb) << '\n';
  std::cout << (ba | bb) << '\n';
  std::cout << (ba ^ bb) << '\n';
  return 0;
}