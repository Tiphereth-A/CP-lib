#ifndef TIFALIBS_UTIL_TUPLE_PUSH_POP
#define TIFALIBS_UTIL_TUPLE_PUSH_POP

#include "traits.hpp"

namespace tifa_libs {

namespace tuple_push_pop_impl_ {

template <usz bgn, class Tpl, usz... Is>
constexpr auto subtuple_impl_(Tpl &&t, std::index_sequence<Is...>) { return std::make_tuple(std::get<Is + bgn>(t)...); }

}  // namespace tuple_push_pop_impl_

template <class Tpl>
constexpr usz tuple_size = std::tuple_size_v<std::remove_cvref_t<Tpl>>;

template <usz bgn, usz len, class Tpl>
constexpr auto subtuple(Tpl &&t) {
  static_assert(bgn <= tuple_size<Tpl> && len <= tuple_size<Tpl> && bgn + len <= tuple_size<Tpl>, "Out of range");
  return tuple_push_pop_impl_::subtuple_impl_<bgn>(t, std::make_index_sequence<len>());
}
template <usz pos, class T, class Tpl>
constexpr auto tuple_push(T &&v, Tpl &&t) {
  static_assert(tuple_size<Tpl> > 0, "Pop from empty tuple");
  return std::tuple_cat(subtuple<0, pos>(t), std::make_tuple(v), subtuple<pos, tuple_size<Tpl> - pos>(t));
}
template <class T, class Tpl>
constexpr auto tuple_push_front(T &&v, Tpl &&t) { return tuple_push<0>(v, t); }
template <class T, class Tpl>
constexpr auto tuple_push_back(T &&v, Tpl &&t) { return tuple_push<tuple_size<Tpl>>(v, t); }

template <usz pos, class Tpl>
constexpr auto tuple_pop(Tpl &&t) {
  static_assert(tuple_size<Tpl> > 0, "Pop from empty tuple");
  return std::tuple_cat(subtuple<0, pos>(t), subtuple<pos + 1, tuple_size<Tpl> - pos - 1>(t));
}
template <class Tpl>
constexpr auto tuple_pop_front(Tpl &&t) { return tuple_pop<0>(t); }
template <class Tpl>
constexpr auto tuple_pop_back(Tpl &&t) { return tuple_pop<tuple_size<Tpl> - 1>(t); }

}  // namespace tifa_libs

#endif