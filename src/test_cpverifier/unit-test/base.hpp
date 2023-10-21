#ifndef TIFA_LIBS_UNITTEST_BASE
#define TIFA_LIBS_UNITTEST_BASE

#include "../../code/util/util.hpp"

namespace tifa_libs::unittest {
template <class T, class... Ts>
void check(T const& got, T const& want, Ts... param) {
  if (got != want) throw std::runtime_error("WA: " + ((param + std::string(", ")) + ...) + ", got " + got.to_str() + ", want " + want.to_str());
}

}  // namespace tifa_libs::unittest

#endif