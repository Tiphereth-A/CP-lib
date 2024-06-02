#ifndef TIFALIBS_FAST_STR2UINT_SI64
#define TIFALIBS_FAST_STR2UINT_SI64

#include "../bit/bswap.hpp"
#include "../util/util.hpp"

namespace tifa_libs {

CEXP u32 str2uint_si64(const char* const s) {
  u64 _ = *((u64*)(s));
  if CEXP (std::endian::native == std::endian::big) _ = bit::bswap(_);
  return _ = (_ & 0x0F0F0F0F0F0F0F0F) * 2561 >> 8, _ = (_ & 0x00FF00FF00FF00FF) * 6553601 >> 16, _ = (_ & 0x0000FFFF0000FFFF) * 42949672960001 >> 32, (u32)_;
}

}  // namespace tifa_libs

#endif