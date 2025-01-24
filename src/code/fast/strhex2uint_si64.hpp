#ifndef TIFALIBS_FAST_STRHEX2UINT_1E8
#define TIFALIBS_FAST_STRHEX2UINT_1E8

#include "../bit/bswap.hpp"
#include "../util/util.hpp"

namespace tifa_libs {

CEXP u32 strhex2uint_si64(const char* const s) NE {
  u64 _ = *((u64*)(s));
  if CEXP (std::endian::native == std::endian::big) _ = bit::bswap(_);
  u64 _0 = _ & 0x4F4F4F4F4F4F4F4F, _1 = _0 & 0x4040404040404040;
  return u32((((((!_1 ? _0 : ((_1 >> 6) * 9) + (_0 ^ _1)) * 0x1001 >> 8) & 0x00FF00FF00FF00FF) * 0x1000001 >> 16) & 0x0000FFFF0000FFFF) * 0x1000000000001 >> 32);
}

}  // namespace tifa_libs

#endif