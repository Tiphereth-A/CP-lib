#ifndef TIFALIBS_UTIL_TUPLE_OP
#define TIFALIBS_UTIL_TUPLE_OP

#include "tuple_push_pop.hpp"

namespace tifa_libs {
namespace tuple_op_impl_ {
template <class Tpl, class Op2, usz... Is>
CEXP auto apply2_impl_(Op2 f, Tpl &&l, Tpl &&r, std::index_sequence<Is...>) NE { return std::make_tuple(f(std::get<Is>(l), std::get<Is>(r))...); }
}  // namespace tuple_op_impl_

template <class Tpl, class Op2>
CEXP auto tuple_apply2(Op2 &&f, Tpl &&l, Tpl &&r) NE { return tuple_op_impl_::apply2_impl_(std::forward<Op2>(f), l, r, std::make_index_sequence<tifa_libs::tuple_size<Tpl>>()); }

#define OO_PTEQ_(op)                                                         \
  template <class... Ts>                                                     \
  CEXP auto operator op(std::tuple<Ts...> CR l, std::tuple<Ts...> CR r) NE { \
    return tuple_apply2([](auto &&l, auto &&r) NE { return l op r; }, l, r); \
  }                                                                          \
  template <class... Ts>                                                     \
  CEXP auto operator op##=(std::tuple<Ts...> &l, std::tuple<Ts...> CR r) NE { return l = l op r; }

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

}  // namespace tifa_libs

#endif