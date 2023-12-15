#ifndef TIFALIBS_GEO2D_INS_HP
#define TIFALIBS_GEO2D_INS_HP

#include "cvh.hpp"

namespace tifa_libs::geo {

template <class FP>
constexpr cvh<FP> ins_hP(vec<line<FP>> vl) {
  auto check = [](line<FP> const &u, line<FP> const &v, line<FP> const &w) -> bool { return w.is_include_strict(ins_LL(u, v)); };
  std::sort(vl.begin(), vl.end());
  vl.erase(std::unique(vl.begin(), vl.end()), vl.end());
  if (vl.size() < 3) return {};
  std::deque<line<FP>> q;
  for (auto it = vl.begin(); it != vl.end(); ++it) {
    if (it != vl.begin() && is_same_dir(*it, *(it - 1))) continue;
    while (q.size() > 1 && !check(*(q.rbegin() + 1), q.back(), *it)) q.pop_back();
    while (q.size() > 1 && !check(*(q.begin() + 1), q.front(), *it)) q.pop_front();
    q.push_back(*it);
  }
  while (q.size() > 2 && !check(*(q.rbegin() + 1), q.back(), q.front())) q.pop_back();
  while (q.size() > 2 && !check(*(q.begin() + 1), q.front(), q.back())) q.pop_front();
  vec<point<FP>> ret;
  for (u32 i = 0; i < q.size(); ++i) ret.push_back(ins_LL(q[i], q[(i + 1) % q.size()]));
  return cvh{ret, true};
}

}  // namespace tifa_libs::geo

#endif