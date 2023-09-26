#ifndef TIFA_LIBS_SPARSE_MAT
#define TIFA_LIBS_SPARSE_MAT

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class T>
struct spmat_node {
  size_t r, c;
  T val;

  explicit spmat_node(size_t r = 0, size_t c = 0, T const &val = T{}):
    r(r), c(c), val(val) {}
};

template <class T>
class spmat {
  vec<spmat_node<T>> d;

public:
  using node = spmat_node<T>;

  explicit spmat() {}

  constexpr vec<node> data() const { return d; }
  constexpr vec<node> &data() { return d; }
  constexpr void insert(size_t r, size_t c, T const &val) { d.emplace_back(r, c, val); }
  constexpr void insert(node const &val) { d.push_back(val); }
  constexpr void shrink() {
    d.erase(std::remove_if(d.begin(), d.end(), [](node const &x) { return x.val == T{}; }), d.end());
  }

  constexpr void sort_by_row() {
    std::sort(d.begin(), d.end(), [](node const &l, node const &r) { return l.r == r.r ? l.c < r.c : l.r < r.r; });
  }
  constexpr void sort_by_col() {
    std::sort(d.begin(), d.end(), [](node const &l, node const &r) { return l.c == r.c ? l.r < r.r : l.c < r.c; });
  }
  template <class F>
  void apply(F f) {
    for (auto &[r, c, v] : d) f(r, c, v);
  }
  template <class F>
  friend void merge(spmat l, spmat r, F f) {
    l.sort_by_row();
    r.sort_by_row();
    spmat ret;
    for (auto itl = l.begin(), itr = r.begin(); itl != l.end() || itr != r.end();) {
      while (itl != l.end() && itr != r.end() && itl->r != itr->r) {
        while (itl != l.end() && itl->r < itr->r) ret.insert(*(itl++));
        while (itr != r.end() && itr->r < itl->r) ret.insert(*(itr++));
      }
      while (itl != l.end() && itr != r.end() && itl->r == itr->r) {
        while (itl != l.end() && itl->c < itr->c) ret.insert(*(itl++));
        while (itr != r.end() && itr->c < itl->c) ret.insert(*(itr++));
        if (itl != l.end() && itr != r.end() && itl->c == itr->c) {
          ret.insert(itl->r, itl->c, f(itl->r, itl->c, itl->val, itr->val));
          ++itl;
          ++itr;
        }
      }
      if (itl == l.end()) {
        while (itr != r.end()) ret.insert(*(itr++));
        break;
      }
      if (itr == r.end()) {
        while (itl != l.end()) ret.insert(*(itl++));
        break;
      }
    }
  }

  constexpr spmat operator-() const {
    spmat ret = *this;
    ret.apply([]([[maybe_unused]] size_t r, [[maybe_unused]] size_t c, T &v) { v = -v; });
    return ret;
  }

  constexpr friend spmat operator+(spmat l, const T &v) { return l += v; }
  constexpr friend spmat operator+(const T &v, spmat l) { return l += v; }
  constexpr spmat &operator+=(const T &v) {
    apply([&v]([[maybe_unused]] size_t i, [[maybe_unused]] size_t j, T &val) { val += v; });
    shrink();
    return *this;
  }
  constexpr friend spmat operator-(spmat l, const T &v) { return l -= v; }
  constexpr friend spmat operator-(const T &v, spmat l) { return l -= v; }
  constexpr spmat &operator-=(const T &v) {
    apply([&v]([[maybe_unused]] size_t i, [[maybe_unused]] size_t j, T &val) { val -= v; });
    shrink();
    return *this;
  }
  constexpr friend spmat operator*(spmat l, const T &v) { return l *= v; }
  constexpr friend spmat operator*(const T &v, spmat l) { return l *= v; }
  constexpr spmat &operator*=(const T &v) {
    apply([&v]([[maybe_unused]] size_t i, [[maybe_unused]] size_t j, T &val) { val *= v; });
    shrink();
    return *this;
  }

  constexpr friend spmat operator+(spmat const &l, spmat const &r) {
    return merge(l, r, []([[maybe_unused]] size_t r, [[maybe_unused]] size_t c, T const &lv, T const &rv) { return lv + rv; });
  }
  constexpr spmat &operator+=(spmat const &r) { return *this = *this + r; }
  constexpr friend spmat operator-(spmat l, const spmat &r) { return l + (-r); }
  constexpr spmat &operator-=(const spmat &r) { return *this = *this - r; }
};

}  // namespace tifa_libs::math

#endif