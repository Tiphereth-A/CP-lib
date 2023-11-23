#ifndef TIFA_LIBS_UTIL_TUPLE_OP
#define TIFA_LIBS_UTIL_TUPLE_OP

#include "tuple_push_pop.hpp"

namespace tuple_op_impl_ {

template <class Tpl, class Op2, usz... Is>
constexpr auto apply2_impl_(Op2 f, Tpl &&l, Tpl &&r, std::index_sequence<Is...>) { return std::make_tuple(f(std::get<Is>(l), std::get<Is>(r))...); }

}  // namespace tuple_op_impl_

template <class Tpl, class Op2>
constexpr auto tuple_apply2(Op2 &&f, Tpl &&l, Tpl &&r) { return tuple_op_impl_::apply2_impl_(std::forward<Op2>(f), l, r, std::make_index_sequence<tifa_libs::tuple_size<Tpl>>()); }

#define OO_PTEQ_(op)                                                                   \
  template <class... Ts>                                                               \
  constexpr auto operator op(std::tuple<Ts...> const &l, std::tuple<Ts...> const &r) { \
    return tuple_apply2([](auto &&l, auto &&r) { return l op r; }, l, r);              \
  }                                                                                    \
  template <class... Ts>                                                               \
  constexpr auto operator op##=(std::tuple<Ts...> &l, const std::tuple<Ts...> &r) { return l = l op r; }

OO_PTEQ_(+)
OO_PTEQ_(-)
OO_PTEQ_(*)
OO_PTEQ_(/)
OO_PTEQ_(%)
OO_PTEQ_(&)
OO_PTEQ_(|)
OO_PTEQ_(^)
OO_PTEQ_(<<)
OO_PTEQ_(>>)

#undef OO_PTEQ_

#endif