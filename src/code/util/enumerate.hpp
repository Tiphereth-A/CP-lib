#ifndef TIFALIBS_UTIL_ENUMERATE
#define TIFALIBS_UTIL_ENUMERATE

#include "traits.hpp"

namespace tifa_libs::util {

namespace enumerate_impl_ {
template <iterable_c T>
class iter_ {
 public:
  using iter_t = typename std::remove_cvref_t<T>::iterator;

 private:
  T const &container_;
  usz sz_;
  iter_t now_;

 public:
  constexpr iter_(T x) : container_(x), sz_(0), now_(x.begin()) {}
  constexpr iter_ const &begin() const { return *this; }
  constexpr iter_ const &end() const { return *this; }
  constexpr bool operator!=(iter_ const &) const { return now_ != container_.end(); }
  constexpr void operator++() {
    ++now_;
    ++sz_;
  }
  constexpr std::pair<usz, iter_t> operator*() const { return {sz_, now_}; }
};

}  // namespace enumerate_impl_
//! Usage: for(auto [index, iter] : enumerate(container)) {...}
template <typename T>
constexpr enumerate_impl_::iter_<T> enumerate(T &&container) { return {std::forward<T>(container)}; }

}  // namespace tifa_libs::util

#endif