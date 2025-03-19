#ifndef TIFALIBS_OPT_ASTAR
#define TIFALIBS_OPT_ASTAR

#include "../util/alias_others.hpp"

namespace tifa_libs::opt {

template <class T>
requires requires(T x, T y) {
  { x.solved() } -> std::same_as<bool>;
  { x.next() } -> range;
  x.cost() < y.cost();
  x < y;
}
std::optional<T> astar(T CR s) NE {
  struct C {
    CEXP bool operator()(cT_(T) a, cT_(T) b) CNE { return b.cost() < a.cost(); }
  };
  std::priority_queue<T, vec<T>, C> pq;
  std::set<T> vis;
  pq.push(s);
  vis.insert(s);
  while (!pq.empty()) {
    T now = pq.top();
    if (pq.pop(); now.solved()) return now;
    for (auto nxt = now.next(); auto i : nxt)
      if (!vis.count(i)) pq.push(i), vis.insert(i);
  }
  return std::nullopt;
}

}  // namespace tifa_libs::opt

#endif