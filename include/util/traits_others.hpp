#ifndef TIFALIBS_UTIL_TRAITS_OTHERS
#define TIFALIBS_UTIL_TRAITS_OTHERS
// clang-format off
#include "alias_others.hpp"

namespace tifa_libs {

//! only for template without non-type argument
template <class, template <class...> class> CEXP bool specialized_from_v = false;
template <template <class...> class T, class... Args> CEXP bool specialized_from_v<T<Args...>, T> = true;
static_assert(specialized_from_v<vecu, std::vector>);
template <class T> concept container_c = common_range<T> && !std::is_array_v<std::remove_cvref_t<T>> && !std::same_as<std::remove_cvref_t<T>, strn> && !std::same_as<std::remove_cvref_t<T>, strnv>;
template <class T> concept istream_c = std::derived_from<T, std::istream> || std::derived_from<T, std::wistream> || requires(T is) { {is.flags()} -> std::same_as<std::ios_base::fmtflags>; is.peek(); };
template <class T> concept ostream_c = std::derived_from<T, std::ostream> || std::derived_from<T, std::wostream> || requires(T os) { {os.flags()} -> std::same_as<std::ios_base::fmtflags>; os.flush(); };

}  // namespace tifa_libs
// clang-format on
#endif