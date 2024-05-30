#ifndef TIFALIBS_FAST_UINT2STR_32
#define TIFALIBS_FAST_UINT2STR_32

#include "../util/util.hpp"

namespace tifa_libs {

CEXP u32 u32tostr_si16(u64 x, char *s) {
  if (x <= 9) {
    *s = (char)(x | 0x30);
    return 1;
  } else if (x <= 99) {
    u64 lo = x, ll = ((lo * 103) >> 9) & 0x1E;
    lo += ll * 3;
    ll = ((lo & 0xF0) >> 4) | ((lo & 0x0F) << 8);
    *(u16 *)s = (u16)(ll | 0x3030);
    return 2;
  }
  return 0;
}
CEXP u32 u32tostr_si32(u64 x, char *s) {
  u64 lo = 0, ll = 0;
  u32 digits = 0;
  if (x <= 99) return u32tostr_si16(x, s);
  lo = x;
  digits = (lo > 999) ? 4 : 3;
  ll = ((lo * 5243) >> 19) & 0xFF;
  lo = ((lo - ll * 100) << 16) | ll;
  ll = ((lo * 103) >> 9) & 0x1E001E;
  lo += ll * 3;
  ll = ((lo & 0x00F000F0) << 28) | ((lo & 0x000F000F) << 40) | 0x3030303000000000;
  u8 *p = (u8 *)&ll;
  if (digits == 4) *(u32 *)s = *(u32 *)(&p[4]);
  else {
    *(u16 *)s = *(u16 *)(&p[5]);
    *(((u8 *)s) + 2) = p[7];
  }

  return digits;
}

CEXP u32 u32tostr(u64 x, char *s) {
  u64 low = 0, ll = 0;
  u32 digits = 0;
  if (x <= 9999) return u32tostr_si32(x, s);
  if (x < 100000000) {
    if ((low = x) > 999999) digits = (low > 9999999) ? 8 : 7;
    else digits = (low > 99999) ? 6 : 5;
  } else {
    u64 high = (x * 0x55E63B89) >> 57;
    low = x - (high * 100000000);
    digits = u32tostr_si16(high, s);
    digits += 8;
  }

  ll = (low * 109951163) >> 40;
  (low -= ll * 10000) |= ll << 32;
  ll = ((low * 5243) >> 19) & 0x000000FF000000FF;
  low = ((low - ll * 100) << 16) | ll;
  ll = ((low * 103) >> 9) & 0x001E001E001E001E;
  low += ll * 3;
  ll = ((low & 0x00F000F000F000F0) >> 4) | (low & 0x000F000F000F000F) << 8;
  ll = (ll >> 32) | (ll << 32) | 0x3030303030303030;

  if (digits >= 8) memcpy(s + digits - 8, &ll, 8);
  else {
    u32 d = digits;
    char *s1 = s, *pll = &(((char *)&ll)[8 - digits]);
    if (d >= 4) {
      memcpy(s1, pll, 4);
      s1 += 4, pll += 4, d -= 4;
    }
    if (d >= 2) {
      memcpy(s1, pll, 2);
      s1 += 2, pll += 2, d -= 2;
    }
    if (d > 0) *(u8 *)s1 = *(u8 *)pll;
  }
  return digits;
}

}  // namespace tifa_libs

#endif