#ifndef TIFALIBS_UTIL_ENUMERATE
#define TIFALIBS_UTIL_ENUMERATE

#include "traits.hpp"

namespace tifa_libs::util {

namespace enumerate_impl_ {
template <typename T, std::enable_if_t<is_iterable<T>::value> * = nullptr>
class iter_ {
 public:
  using iter_t = typename remove_cvref_t<T>::iterator;

 private:
  T const &container_;
  usz sz_;
  iter_t now_;

 public:
  iter_(T x) : container_(x), sz_(0), now_(x.begin()) {}
  iter_ const &begin() const { return *this; }
  iter_ const &end() const { return *this; }
  bool operator!=(iter_ const &) const { return now_ != container_.end(); }
  void operator++() {
    ++now_;
    ++sz_;
  }
  std::pair<usz, iter_t> operator*() const { return {sz_, now_}; }
};

}  // namespace enumerate_impl_
//! Usage: for(auto [index, iter] : enumerate(container)) {...}
template <typename T>
enumerate_impl_::iter_<T> enumerate(T &&container) { return {std::forward<T>(container)}; }

}  // namespace tifa_libs::util

#endif