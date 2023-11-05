#ifndef TIFA_LIBS_DS_DEQUE_WITH_W
#define TIFA_LIBS_DS_DEQUE_WITH_W

#include "../util/util.hpp"

namespace tifa_libs::ds {

// T e() {}
// T op(T a, T b) {}
template <typename T, auto e, auto op>
class deque_with_w {
  // front [q[0].back        q[0].front][q[1].front       q[1].back] back
  vec<vec<T>> q;
  vec<vec<T>> s;
  void bf() {
    s[0].resize(q[0].size() + 1);
    s[0][0] = e();
    for (usz i = 0; i < q[0].size(); ++i) s[0][i + 1] = op(q[0][i], s[0][i]);
    s[1].resize(q[1].size() + 1);
    s[1][0] = e();
    for (usz i = 0; i < q[1].size(); ++i) s[1][i + 1] = op(s[1][i], q[1][i]);
  }

 public:
  deque_with_w() : q(2), s(2) { bf(); }
  void push_front(T x) {
    q[0].push_back(x);
    if (s[0].size()) s[0].push_back(op(x, s[0].back()));
    else s[0].push_back(x);
  }
  void push_back(T x) {
    q[1].push_back(x);
    if (s[1].size()) s[1].push_back(op(s[1].back(), x));
    else s[1].push_back(x);
  }
  T pop_front() {
    if (q[0].empty()) {
      u32 lessHalf = u32(q[1].size()) / 2;
      q[0] = std::vector<T>(q[1].rbegin() + lessHalf, q[1].rend());
      q[1] = std::vector<T>(q[1].end() - lessHalf, q[1].end());
      bf();
    }
    T ret = q[0].back();
    q[0].pop_back(), s[0].pop_back();
    return ret;
  }
  T pop_back() {
    if (q[1].empty()) {
      u32 lessHalf = u32(q[0].size()) / 2;
      q[1] = std::vector<T>(q[0].rbegin() + lessHalf, q[0].rend());
      q[0] = std::vector<T>(q[0].end() - lessHalf, q[0].end());
      bf();
    }
    T ret = q[1].back();
    q[1].pop_back(), s[1].pop_back();
    return ret;
  }
  T w() {
    return op(s[0].back(), s[1].back());
  }
};

}  // namespace tifa_libs::ds

#endif