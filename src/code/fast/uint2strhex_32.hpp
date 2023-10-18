#ifndef TIFA_LIBS_FAST_UINT2STRHEX_32
#define TIFA_LIBS_FAST_UINT2STRHEX_32

#include "../util/util.hpp"

namespace tifa_libs {

constexpr u32 uint2strhex_32(u64 num, char *s, bool lowerAlpha = true) {
  constexpr char digits[513] =
      "000102030405060708090A0B0C0D0E0F"
      "101112131415161718191A1B1C1D1E1F"
      "202122232425262728292A2B2C2D2E2F"
      "303132333435363738393A3B3C3D3E3F"
      "404142434445464748494A4B4C4D4E4F"
      "505152535455565758595A5B5C5D5E5F"
      "606162636465666768696A6B6C6D6E6F"
      "707172737475767778797A7B7C7D7E7F"
      "808182838485868788898A8B8C8D8E8F"
      "909192939495969798999A9B9C9D9E9F"
      "A0A1A2A3A4A5A6A7A8A9AAABACADAEAF"
      "B0B1B2B3B4B5B6B7B8B9BABBBCBDBEBF"
      "C0C1C2C3C4C5C6C7C8C9CACBCCCDCECF"
      "D0D1D2D3D4D5D6D7D8D9DADBDCDDDEDF"
      "E0E1E2E3E4E5E6E7E8E9EAEBECEDEEEF"
      "F0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF";
  constexpr char digitsLowerAlpha[513] =
      "000102030405060708090a0b0c0d0e0f"
      "101112131415161718191a1b1c1d1e1f"
      "202122232425262728292a2b2c2d2e2f"
      "303132333435363738393a3b3c3d3e3f"
      "404142434445464748494a4b4c4d4e4f"
      "505152535455565758595a5b5c5d5e5f"
      "606162636465666768696a6b6c6d6e6f"
      "707172737475767778797a7b7c7d7e7f"
      "808182838485868788898a8b8c8d8e8f"
      "909192939495969798999a9b9c9d9e9f"
      "a0a1a2a3a4a5a6a7a8a9aaabacadaeaf"
      "b0b1b2b3b4b5b6b7b8b9babbbcbdbebf"
      "c0c1c2c3c4c5c6c7c8c9cacbcccdcecf"
      "d0d1d2d3d4d5d6d7d8d9dadbdcdddedf"
      "e0e1e2e3e4e5e6e7e8e9eaebecedeeef"
      "f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff";
  u32 x = (u32)num;
  int i = 3;
  char *lut = (char *)(lowerAlpha ? digitsLowerAlpha : digits);
  while (i >= 0) {
    int pos = (x & 0xFF) * 2;
    char ch = lut[pos];
    s[i * 2] = ch;
    ch = lut[pos + 1];
    s[i * 2 + 1] = ch;
    x >>= 8;
    i -= 1;
  }
  return 0;
}

}  // namespace tifa_libs

#endif