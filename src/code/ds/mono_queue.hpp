#ifndef TIFALIBS_DS_MONO_QUEUE
#define TIFALIBS_DS_MONO_QUEUE

#include "../util/alias_num.hpp"

namespace tifa_libs::ds {

template <class T, class Comp = std::less<T>>
class mono_queue {
  static CEXP Comp compare{};

  const u32 k;
  u32 i;
  std::deque<std::pair<T, u32>> q;

 public:
  CEXPE mono_queue(u32 k) NE : k{k}, i{0} { assert(k > 0); }
  // @return minimum of last k (at most) pushed elements
  CEXP T CR push(cT_(T) x) NE {
    if (!q.empty() && q.front().second + k == i) q.pop_front();
    while (!q.empty() && compare(x, q.back().first)) q.pop_back();
    q.emplace_back(x, i++);
    return q.front().first;
  }
};

}  // namespace tifa_libs::ds

#endif