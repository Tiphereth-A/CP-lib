#define PROBLEM "https://vjudge.net/problem/UVA-11525"

#include "../../code/math/cantor_inv.hpp"

void solve() {
  u32 n;
  std::cin >> n;
  vec<u32> a(n);
  for (auto& i : a) std::cin >> i;
  auto p = tifa_libs::math::cantor_inv_seq(a);
  for (usz i = 0; i < n; ++i) std::cout << p[i] << " \n"[i == n - 1];
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 t;
  std::cin >> t;
  while (t--) solve();
  return 0;
}

/*
Given N and K find the N -th permutation of the integers from 1 to K when those permutations are
lexicographically ordered. N starts from 0. Since N is very large N will be represented by a sequence
of K non-negative integers S1, S2, . . . , Sk. From this sequence of integers N can be calculated with
the following expression.

\sum_{i=1}^K S_i*(K-i)!

**Input**

First line of the input contains T (<= 10) the number of test cases. Each of these test cases consists of
2 lines. First line contains a integer K (1 <= K <= 50000). Next line contains K integers S1, S2, . . . , Sk.
(0 <= Si <= K - i).

**Output**

For each test case output contains N -th permutation of the integers from 1 to K. These K integers
should be separated by a single space
*/

/*
4
3
2 1 0
3
1 0 0
4
2 1 1 0
4
1 2 1 0
==========
3 2 1
2 1 3
3 2 4 1
2 4 3 1
*/