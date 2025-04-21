#ifndef TIFALIBS_DS_DBITSET
#define TIFALIBS_DS_DBITSET

#include "../util/traits_math.hpp"
#include "../util/traits_others.hpp"

namespace tifa_libs::ds {

struct dbitset {
  using word_t = u64;
  static CEXP u32 word_width = 64;

 protected:
  u64 sz;
  vec<word_t> data;

  static CEXP auto idx_word(u64 n) NE { return u32(n / word_width); }
  static CEXP auto idx_bit(u64 n) NE { return (u32)n % word_width; }
  static CEXP auto word_count(u64 n) NE { return idx_word(n) + !!idx_bit(n); }
  static CEXP auto mask_bit(u64 n) NE { return 1_u64 << idx_bit(n); }
  static CEXP u64 mask_outrange(u64 n) NE {
    if (!idx_bit(n)) return 0;
    return -1_u64 << idx_bit(n);
  }

  CEXP void lsh_(umost64_c auto n) NE {
    if (data.empty()) {
      bit_resize(n);
      return;
    }
    if (!n) return;
    const auto pre = data.size();
    const u32 w = idx_word(n), ofs = idx_bit(n);
    data.resize(data.size() + w);
    if (!ofs)
      for (auto i = pre - 1; ~i; --i) data[i + w] = data[i];
    else {
      const u32 cofs = word_width - ofs;
      for (auto i = pre - 1; i; --i) data[i + w] = data[i] << ofs | data[i - 1] >> cofs;
      data[w] = data[0] << ofs;
    }
    fill(data.begin(), data.begin() + w, 0), sz += n;
  }
  CEXP void rsh_(umost64_c auto n) NE {
    if (n >= sz) {
      sz = 0, data.clear();
      return;
    }
    if (!n) return;
    const u32 w = idx_word(n), ofs = idx_bit(n);
    const u32 lim = word_size() - w - 1;
    if (!ofs)
      flt_ (u32, i, 0, lim + 1) data[i] = data[i + w];
    else {
      const u32 cofs = word_width - ofs;
      flt_ (u32, i, 0, lim) data[i] = data[i + w] >> ofs | data[i + w + 1] << cofs;
      data[lim] = data.back() >> ofs;
    }
    data.resize(data.size() - w), sz -= n;
  }

 public:
  CEXPE dbitset(usz n, bool val = false) NE { bit_resize(n, val); }
  CEXP dbitset(strnv s, usz pos = 0, usz n = -1_usz, char zero = '0', char one = '1') NE { set(s, pos, n, zero, one); }

  CEXP dbitset& set(strnv s, usz pos = 0, usz n = -1_usz, char = '0', char one = '1') NE {
    const auto nbits = min({sz, n, s.size() - pos});
    reset(), bit_resize(nbits);
    for (usz i = nbits; i; --i)
      if (s[pos + nbits - i] == one) set(i - 1);
    return *this;
  }

  friend CEXP bool operator==(dbitset CR l, dbitset CR r) NE { return l.sz == r.sz && l.data == r.data; }

  CEXP u64 find_first() CNE {
    flt_ (u32, i, 0, word_size())
      if (data[i]) return i * 64_u64 + (u32)std::countr_zero(data[i]);
    return sz;
  }
  CEXP u64 find_next(u64 prev) CNE {
    if (++prev >= sz) return sz;
    size_t i = idx_word(prev);
    if (word_t _ = data[i] & -1_u64 << idx_bit(prev); _) return i * word_width + (u32)std::countr_zero(_);
    for (++i; i < word_size(); ++i)
      if (data[i]) return i * word_width + (u32)std::countr_zero(data[i]);
    return sz;
  }

  CEXP word_t CR getword(usz n) CNE { return data[idx_word(n)]; }
  CEXP word_t& getword(usz n) NE { return data[idx_word(n)]; }
  CEXP bool operator[](usz n) CNE { return getword(n) & mask_bit(n); }

  CEXP bool all() CNE {
    if (data.empty()) return false;
    flt_ (u32, i, 0, (u32)data.size() - !!idx_bit(sz))
      if (~data[i]) return false;
    if (idx_bit(sz)) return (data.back() & ~mask_outrange(sz)) == ~mask_outrange(sz);
    return true;
  }
  CEXP bool any() CNE {
    if (data.empty()) return false;
    for (auto i : data)
      if (i) return true;
    return false;
  }
  CEXP bool none() CNE {
    if (data.empty()) return false;
    return !any();
  }
  CEXP u64 count() CNE {
    u64 ans = 0;
    for (const auto i : data) ans += (u32)std::popcount(i);
    return ans;
  }

  CEXP u64 CR bit_size() CNE { return sz; }
  CEXP u32 word_size() CNE { return (u32)data.size(); }
  CEXP void bit_resize(usz n, bool val = false) NE {
    data.resize(word_count(sz = n), val ? -1_u64 : 0);
    if (val && !data.empty()) data.back() &= ~mask_outrange(sz);
  }

#define OP__(op)                                              \
  CEXP dbitset& operator op##=(dbitset CR r) NE {             \
    if (r.sz > sz) data.resize(r.word_size()), sz = r.sz;     \
    if (data.empty()) return *this;                           \
    flt_ (u32, i, 0, r.word_size()) data[i] op## = r.data[i]; \
    data.back() &= ~mask_outrange(sz);                        \
    return *this;                                             \
  }                                                           \
  CEXP dbitset operator op(dbitset CR r) CNE { return dbitset(*this) op## = r; }
  OP__(&)
  OP__(|)
  OP__(^)
#undef OP__
  CEXP dbitset operator~() CNE { return dbitset(*this).flip(); }
  CEXP dbitset& operator<<=(imost64_c auto n) NE {
    if (n < 0) [[unlikely]]
      rsh_((to_uint_t<decltype(n)>)-n);
    else lsh_((to_uint_t<decltype(n)>)n);
    return *this;
  }
  CEXP dbitset operator<<(imost64_c auto n) CNE { return dbitset(*this) <<= n; }
  CEXP dbitset& operator>>=(imost64_c auto n) NE {
    if (n < 0) [[unlikely]]
      lsh_((to_uint_t<decltype(n)>)-n);
    else rsh_((to_uint_t<decltype(n)>)n);
    return *this;
  }
  CEXP dbitset operator>>(imost64_c auto n) CNE { return dbitset(*this) >>= n; }

  CEXP dbitset& set() NE {
    fill(data, -1_u64);
    if (!data.empty()) data.back() &= ~mask_outrange(sz);
    return *this;
  }
  CEXP dbitset& set(usz pos, bool val = true) NE {
    if (val) getword(pos) |= mask_bit(pos);
    else return reset(pos);
    return *this;
  }
  CEXP dbitset& reset() NE {
    fill(data, 0);
    return *this;
  }
  CEXP dbitset& reset(usz pos) NE {
    getword(pos) &= ~mask_bit(pos);
    return *this;
  }
  CEXP dbitset& flip() NE {
    for (auto& i : data) i = ~i;
    if (!data.empty()) data.back() &= ~mask_outrange(sz);
    return *this;
  }
  CEXP dbitset& flip(usz pos) NE {
    getword(pos) ^= mask_bit(pos);
    return *this;
  }

  CEXP strn to_string(char zero = '0', char one = '1') CNE {
    strn ans(sz, zero);
    if (zero != one) [[likely]]
      for (auto n = find_first(); n < sz; n = find_next(n)) ans[sz - n - 1] = one;
    return ans;
  }
  template <int_c T>
  CEXP T to_integer() CNE {
    if CEXP (sizeof(T) * 8 <= word_width) return T(data.empty() ? 0 : data[0]);
    else return T(data.size() > 1 ? data[1] : 0) << word_width | T(data.empty() ? 0 : data[0]);
  }
  CEXP u32 to_ulong() CNE { return to_integer<unsigned long>(); }
  CEXP u64 to_ullong() CNE { return to_integer<unsigned long long>(); }

  friend auto& operator>>(istream_c auto& is, dbitset& b) NE {
    strn s;
    (is >> s), b.set(s);
    return is;
  }
  friend auto& operator<<(ostream_c auto& os, dbitset CR b) NE { return os << b.to_string(); }
};

}  // namespace tifa_libs::ds

#endif