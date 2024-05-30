#ifndef TIFALIBS_OPT_ASTAR
#define TIFALIBS_OPT_ASTAR

#include "../util/traits.hpp"

namespace tifa_libs::opt {

template <class T>
requires requires(T x, T y) {
  { x.solved() } -> std::same_as<bool>;
  { x.next() } -> iterable_c;
  x.cost() < y.cost();
  x < y;
}
std::optional<T> astar(T CR s) {
  struct C {
    CEXP bool operator()(cT_(T) a, cT_(T) b) const { return b.cost() < a.cost(); }
  };
  pq<T, C> pq;
  std::set<T> vis;

  pq.push(s);
  vis.insert(s);
  while (!pq.empty()) {
    T now = pq.top();
    pq.pop();
    if (now.solved()) return now;
    auto nxt = now.next();
    for (auto i : nxt)
      if (!vis.count(i)) pq.push(i), vis.insert(i);
  }
  return std::nullopt;
}

}  // namespace tifa_libs::opt

#endif