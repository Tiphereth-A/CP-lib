#ifndef TIFA_LIBS_UTIL_STR2UINT_1E8
#define TIFA_LIBS_UTIL_STR2UINT_1E8

#include "../util/util.hpp"

namespace tifa_libs {

constexpr u32 str2uint_1e8(const char* const s) {
  static_assert(__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__);
  u64 _ = *((u64*)(s));
  _ = (_ & 0x0F0F0F0F0F0F0F0F) * 2561 >> 8;
  _ = (_ & 0x00FF00FF00FF00FF) * 6553601 >> 16;
  _ = (_ & 0x0000FFFF0000FFFF) * 42949672960001 >> 32;
  return (u32)_;
}

}  // namespace tifa_libs

#endif