#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_3_D"

#include "../../include/ds/mono_queue.hpp"
#include "../../include/util/alias_others.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, k;
  std::cin >> n >> k;
  ds::mono_queue<i32> qmin(k);
  veci ans;
  ans.reserve(n);
  flt_ (u32, i, 0, n) {
    i32 x;
    std::cin >> x;
    ans.push_back(qmin.push(x));
  }
  flt_ (u32, i, k - 1, n) std::cout << ans[i] << " \n"[i + 1 == n];
}
