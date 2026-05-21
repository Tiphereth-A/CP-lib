#pragma once

#include "../../util/alias/num/lib.hpp"

namespace tifa_libs {

template <class T, class Comp = std::less<T>>
class mono_queue {
  static CEXP Comp compare{};

  cu32 k;
  u32 i{0};
  std::deque<std::pair<T, u32>> q;

 public:
  CEXPE mono_queue(u32 k) NE : k{k} { assert(k > 0); }
  // @return minimum of last k (at most) pushed elements
  CEXP T CR push(cT_(T) x) NE {
    if (!q.empty() && q.front().second + k == i) q.pop_front();
    while (!q.empty() && compare(x, q.back().first)) q.pop_back();
    q.emplace_back(x, i++);
    return q.front().first;
  }
};

}  // namespace tifa_libs
