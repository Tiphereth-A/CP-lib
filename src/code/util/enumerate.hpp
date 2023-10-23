#ifndef TIFA_LIBS_UTIL_ENUMERATE
#define TIFA_LIBS_UTIL_ENUMERATE

#include "traits.hpp"

namespace tifa_libs::util {

namespace enumerate_impl_ {
template <typename T, std::enable_if_t<is_iterable<T>::value> * = nullptr>
class iter_ {
 public:
  using iter_t = typename remove_cvref_t<T>::iterator;

 private:
  const T &container_;
  usz sz_;
  iter_t now_;

 public:
  iter_(T x) : container_(x), sz_(0), now_(x.begin()) {}
  const iter_ &begin() const { return *this; }
  const iter_ &end() const { return *this; }
  bool operator!=(const iter_ &) const { return now_ != container_.end(); }
  void operator++() {
    ++now_;
    ++sz_;
  }
  std::pair<usz, iter_t> operator*() const { return {sz_, now_}; }
};

//! Usage: for(auto [index, iter] : enumerate(container)) {...}
template <typename T>
iter_<T> enumerate(T &&container) { return {std::forward<T>(container)}; }
}  // namespace enumerate_impl_
using enumerate_impl_::enumerate;

}  // namespace tifa_libs::util

#endif