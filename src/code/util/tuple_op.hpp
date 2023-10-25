#ifndef TIFA_LIBS_UTIL_TUPLE_OP
#define TIFA_LIBS_UTIL_TUPLE_OP

#include "tuple_push_pop.hpp"

namespace tuple_op_impl_ {

template <class Tpl, class Op2, usz... Is>
constexpr auto apply2_impl_(Op2 f, Tpl &&lhs, Tpl &&rhs, std::index_sequence<Is...>) { return std::make_tuple(f(std::get<Is>(lhs), std::get<Is>(rhs))...); }

}  // namespace tuple_op_impl_

template <class Tpl, class Op2>
constexpr auto tuple_apply2(Op2 f, Tpl &&lhs, Tpl &&rhs) { return tuple_op_impl_::apply2_impl_(f, lhs, rhs, std::make_index_sequence<tifa_libs::tuple_size<Tpl>>()); }

#define OO_PTEQ_(op)                                                                       \
  template <class... Ts>                                                                   \
  constexpr auto operator op(std::tuple<Ts...> const &lhs, std::tuple<Ts...> const &rhs) { \
    return apply2([](auto &&l, auto &&r) { return l op r; }, lhs, rhs);                    \
  }                                                                                        \
  template <class... Ts>                                                                   \
  constexpr auto operator op##=(std::tuple<Ts...> &lhs, const std::tuple<Ts...> &rhs) { return lhs = lhs op rhs; }

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