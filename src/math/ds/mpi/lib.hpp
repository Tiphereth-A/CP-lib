#pragma once

#include "../../../conv/add/u128/lib.hpp"
#include "../../../fast/s2u/u32/lib.hpp"
#include "../../../util/strip/lib.hpp"
#include "../../../util/traits/others/lib.hpp"

namespace tifa_libs {

struct mpi : vecu {
  static CEXP u32 D = 1e8, lgD = 8, sqrtD = 1e4;
  static_assert(sqrtD * sqrtD == D);
  static CEXP u32 hex_lgD = 6, hex_D = 1u << 24;

 private:
  static CEXP arr<u32, hex_lgD + 1> hex_pow = {1u, 16u, 256u, 4096u, 65536u, 1048576u, hex_D};
  struct ict4 {
    CEXP static auto num = [] {
      arr<u32, sqrtD> num;
      for (u32 e0 = (48 << 0), j = 0; e0 < (58 << 0); e0 += (1 << 0))
        for (u32 e1 = (48 << 8); e1 < (58 << 8); e1 += (1 << 8))
          for (u32 e2 = (48 << 16); e2 < (58 << 16); e2 += (1 << 16))
            for (u32 e3 = (48 << 24); e3 < (58 << 24); e3 += (1 << 24)) num[j++] = e0 ^ e1 ^ e2 ^ e3;
      return num;
    }();
    static auto get(u32 x) NE { return (const char*)(num.data() + x); }
  };

  bool neg = false, hmd_ = false;
  vecu hbits_;

#define vec_like std::derived_from<vecu> auto
  // name starts with u  ==>  ignore sign
  static CEXP auto ucmp(vec_like CR a, vec_like CR b) NE {
    if (a.size() != b.size()) return a.size() <=> b.size();
    return std::lexicographical_compare_three_way(a.rbegin(), a.rend(), b.rbegin(), b.rend());
  }
  static CEXP auto cmp(mpi CR a, mpi CR b) NE {
    if (a.neg) {
      retif_((b.neg), ucmp(b, a), std::strong_ordering::less);
    } else retif_((b.neg), std::strong_ordering::greater, ucmp(a, b));
  }
  static CEXP bool is_0(vec_like CR a) NE { return a.empty(); }
  static CEXP bool is_pm1(vec_like CR a) NE { return a.size() == 1 && a[0] == 1; }
  static CEXP bool is_1(mpi CR a) NE { return !a.neg && is_pm1(a); }
  static CEXP void shrink_(vec_like& a) NE {
    auto [_, r] = rstrip_view(a, [](u32 x) { return !x; });
    a.erase(r, a.end());
  }
  template <int_c T>
  static CEXP vecu int2vecu(T x) NE {
    if CEXP (sint_c<T>) assert(x >= 0);
    vecu res;
    while (x) res.push_back(u32(x % D)), x /= D;
    return res;
  }
  static CEXP i64 uvec2i64(vec_like CR a) NE {
    i64 res = 0;
    for (u32 i = (u32)a.size() - 1; ~i; --i) res = res * D + a[i];
    return res;
  }

 public:
  CEXP mpi() NE = default;
  CEXP mpi(bool n, itlu x) NE : vecu(x), neg(n) {}
  CEXP mpi(bool n, spnu d) NE : vecu(d.begin(), d.end()), neg(n) {}
  template <int_c T>
  CEXP mpi(T x) NE : mpi() {
    if CEXP (sint_c<T>)
      if (x < 0) neg = true, x = -x;
    while (x) push_back(u32(to_uint_t<T>(x) % D)), x /= (T)D;
  }
  CEXP mpi(strn s) NE : mpi() {
    if (assert(!s.empty()); s.size() == 1u) {
      if (s[0] == '0') return;
      assert(isdigit(s[0])), push_back(s[0] & 15);
      return;
    }
    u32 l = 0;
    if (s[0] == '-') ++l, neg = true;
    u32 _ = 0;
    if (u32 ofs = u32(s.size() - l) & 7; ofs) {
      flt_ (u32, i, l, l + ofs) _ = _ * 10 + (s[i] & 15);
      l += ofs;
    }
    if (l) s = s.substr(l);
    for (u32 ie = (u32)s.size(); ie >= lgD; ie -= lgD)
      push_back(str2uint_si64(s.data() + ie - lgD));
    if (_) push_back(_);
  }
  CEXP static mpi from_hex_str(strn s) NE {
    mpi res;
    res.hmd_ = true;
    if (assert(!s.empty()); s.size() == 1u && s[0] == '0') return res;
    u32 l = 0;
    if (s[0] == '-') ++l, res.neg = true;
    if (l + 1 < s.size() && s[l] == '0' && (s[l + 1] == 'x' || s[l + 1] == 'X')) l += 2;
    assert(l < s.size());
    for (u32 r = (u32)s.size(); l < r;) {
      u32 is = r > lgD ? r - lgD : l, x = 0;
      flt_ (u32, i, is, r) x = (x << 4) | hex_to_u32_(s[i]);
      res.hbits_.push_back(x), r = is;
    }
    if (h_shrink_(res.hbits_); res.hbits_.empty()) res.neg = false;
    return res;
  }

  CEXP void set_neg(bool s) NE { neg = is_zero() ? false : s; }
  CEXP bool is_neg() CNE { return neg; }
  CEXP bool is_zero() CNE { return hmd_ ? hbits_.empty() : is_0(*this); }
  CEXP void shrink() NE {
    if (hmd_) h_shrink_(hbits_);
    else shrink_(*this);
    if (is_zero()) neg = false;
  }
  friend CEXP mpi abs(mpi m) NE {
    m.neg = false;
    return m;
  }

  friend CEXP mpi operator+(mpi CR l, mpi CR r) NE {
    if (l.hmd_ && r.hmd_) {
      if (l.neg == r.neg) return make_hex_(l.neg, h_add_(l.hbits_, r.hbits_));
      i32 ccmp = h_cmp_mag_(l.hbits_, r.hbits_);
      if (!ccmp) return make_hex_(false, {});
      if (ccmp < 0) {
        auto c = h_sub_(r.hbits_, l.hbits_);
        bool n = c.empty() ? false : r.neg;
        return make_hex_(n, std::move(c));
      }
      auto c = h_sub_(l.hbits_, r.hbits_);
      bool n = c.empty() ? false : l.neg;
      return make_hex_(n, std::move(c));
    }
    auto ld = l.as_dec_(), rd = r.as_dec_();
    if (ld.neg == rd.neg) return {ld.neg, uadd(ld, rd)};
    if (std::is_lteq(ucmp(ld, rd))) {
      auto c = usub(rd, ld);
      return {is_0(c) ? false : rd.neg, c};
    }
    auto c = usub(ld, rd);
    return {is_0(c) ? false : ld.neg, c};
  }
  friend CEXP mpi operator-(mpi CR l, mpi CR r) NE { return l + (-r); }
  friend CEXP mpi operator*(mpi CR l, mpi CR r) NE {
    if (l.hmd_ && r.hmd_) {
      auto c = h_mul_(l.hbits_, r.hbits_);
      bool n = c.empty() ? false : bool(l.neg ^ r.neg);
      return make_hex_(n, std::move(c));
    }
    auto ld = l.as_dec_(), rd = r.as_dec_();
    auto c = umul(ld, rd);
    bool n = is_0(c) ? false : (ld.neg ^ rd.neg);
    return {n, c};
  }
  friend CEXP ptt<mpi> divmod(mpi CR l, mpi CR r) NE {
    if (l.hmd_ && r.hmd_) {
      auto dm = h_divmod_(l.hbits_, r.hbits_);
      bool qn = dm.first.empty() ? false : (l.neg != r.neg), rn = dm.second.empty() ? false : l.neg;
      return {make_hex_(qn, std::move(dm.first)), make_hex_(rn, std::move(dm.second))};
    }
    auto ld = l.as_dec_(), rd = r.as_dec_();
    auto dm = udivmod(ld, rd);
    return {mpi{is_0(dm.first) ? false : ld.neg != rd.neg, dm.first}, mpi{is_0(dm.second) ? false : ld.neg, dm.second}};
  }
  friend CEXP mpi operator/(mpi CR l, mpi CR r) NE { return divmod(l, r).first; }
  friend CEXP mpi operator%(mpi CR l, mpi CR r) NE { return divmod(l, r).second; }
  CEXP mpi& operator+=(mpi CR r) NE { return (*this) = (*this) + r; }
  CEXP mpi& operator-=(mpi CR r) NE { return (*this) = (*this) - r; }
  CEXP mpi& operator*=(mpi CR r) NE { return (*this) = (*this) * r; }
  CEXP mpi& operator/=(mpi CR r) NE { return (*this) = (*this) / r; }
  CEXP mpi& operator%=(mpi CR r) NE { return (*this) = (*this) % r; }
  CEXP mpi operator-() CNE {
    if (is_zero()) return *this;
    auto ret = *this;
    ret.neg = !ret.neg;
    return ret;
  }
  CEXP mpi operator+() CNE { return *this; }
  friend CEXP auto operator<=>(mpi CR l, mpi CR r) NE {
    if (l.hmd_ && r.hmd_) {
      if (l.neg != r.neg) return l.neg ? std::strong_ordering::less : std::strong_ordering::greater;
      if (h_eq_(l.hbits_, r.hbits_)) return std::strong_ordering::equal;
      return l.neg ^ h_lt_(l.hbits_, r.hbits_) ? std::strong_ordering::less : std::strong_ordering::greater;
    }
    return cmp(l.as_dec_(), r.as_dec_());
  }
  friend CEXP bool operator==(mpi CR l, mpi CR r) NE { return std::is_eq(l <=> r); }

  CEXP strn to_str() CNE {
    if (is_zero()) return "0";
    strn r;
    if (r.reserve(size() * 8 + 1); neg) r.push_back('-');
    char int_buf[11];
    auto res = std::to_chars(int_buf, int_buf + 11, back());
    r.append(int_buf, u32(res.ptr - int_buf));
    for (u32 i = (u32)size() - 2; ~i; --i) r.append(ict4::get((*this)[i] / 10000u), 4), r.append(ict4::get((*this)[i] % 10000u), 4);
    return r;
  }
  CEXP strn to_hex_str() CNE {
    if (hmd_) {
      if (hbits_.empty()) return "0";
      strn res;
      if (neg) res.push_back('-');
      for (u32 i = (u32)hbits_.size() - 1; ~i; --i) res += h_u32_to_hex_(hbits_[i], i + 1 != hbits_.size());
      return res;
    }
    if (is_zero()) return "0";
    mpi x = abs(*this);
    vecu rems;
    rems.reserve((x.size() * 27 + 23) / 24);
    while (!x.is_zero()) {
      auto [q, r] = udivmod_1e8(x, vecu{hex_D});
      x = mpi{false, q}, rems.push_back(r.empty() ? 0 : r[0]);
    }
    strn res;
    if (res.reserve(neg + rems.size() * hex_lgD); neg) res.push_back('-');
    res += u32_to_hex_(rems.back(), false);
    for (u32 i = (u32)rems.size() - 1; i; --i) res += u32_to_hex_(rems[i - 1], true);
    return res;
  }
  CEXP mpi as_mpi() CNE { return *this; }
  CEXP i64 to_i64() CNE { retif_((i64 res = uvec2i64(*this); neg), -res, res); }
  CEXP i128 to_i128() CNE {
    i128 res = 0;
    for (u32 i = (u32)size() - 1; ~i; --i) res = res * D + (*this)[i];
    retif_((neg), -res, res);
  }
  friend auto& operator>>(istream_c auto& is, mpi& m) NE {
    strn s;
    is >> s, m = mpi{s};
    return is;
  }
  friend auto& operator<<(ostream_c auto& os, mpi CR m) NE { return os << m.to_str(); }

 private:
  static CEXP mpi make_hex_(bool n, vecu bits) NE {
    mpi x;
    x.hmd_ = true, x.hbits_ = std::move(bits), h_shrink_(x.hbits_), x.neg = x.hbits_.empty() ? false : n;
    return x;
  }
  CEXP mpi as_dec_() CNE {
    if (!hmd_) return *this;
    mpi r;
    r.neg = neg;
    for (u32 i = (u32)hbits_.size() - 1; ~i; --i) umuladd_(r, 65536u, 0), umuladd_(r, 65536u, hbits_[i] >> 16), umuladd_(r, 65536u, hbits_[i] & 65535u);
    if (r.empty()) r.neg = false;
    return r;
  }

  static CEXP u32 hex_to_u32_(char c) NE { return (c & 15) + ((c & 64) >> 6) * 9; }
  static CEXP strn u32_to_hex_(u32 x, bool pad0) NE {
    arr<char, hex_lgD> buf;
    flt_ (u32, i, 0, hex_lgD) {
      u32 d = x & 15;
      buf[hex_lgD - 1 - i] = char(d + (d < 10 ? 48 : 55)), x >>= 4;
    }
    if (pad0) return {buf.begin(), buf.end()};
    u32 l = 0;
    while (l + 1 < hex_lgD && buf[l] == '0') ++l;
    return {buf.begin() + l, buf.end()};
  }
  static CEXP strn h_u32_to_hex_(u32 x, bool pad0) NE {
    strn res;
    res.reserve(8);
    flt_ (u32, _, 0, 8) {
      u32 d = x & 15;
      res.push_back(char(d + (d < 10 ? 48 : 55))), x >>= 4;
    }
    if (!pad0) {
      while (!res.empty() && res.back() == '0') res.pop_back();
      if (res.empty()) res.push_back('0');
    }
    reverse(res);
    return res;
  }
  static CEXP void umuladd_(vecu& a, u32 mul, u32 add) NE {
    if (a.empty() && !add) return;
    u64 carry = add;
    flt_ (u32, i, 0, (u32)a.size()) a[i] = u32((carry += (u64)a[i] * mul) % D), carry /= D;
    while (carry) a.push_back(u32(carry % D)), carry /= D;
  }

  using iter = u32*;
  using citer = u32 const*;

  static CEXP usz h_nz_size_(vecu CR a) NE {
    usz n = a.size();
    while (n && !a[n - 1]) --n;
    return n;
  }
  static CEXP bool h_eq_(vecu CR a, vecu CR b) NE {
    usz asz = h_nz_size_(a);
    if (asz != h_nz_size_(b)) return false;
    flt_ (usz, i, 0, asz)
      if (a[i] != b[i]) return false;
    return true;
  }
  static CEXP bool h_is0_(vecu CR a) NE { return a.empty(); }
  static CEXP bool h_is_one_(vecu CR a) NE { return a.size() == 1 && a[0] == 1; }
  static CEXP void h_shrink_(vecu& a) NE {
    while (!a.empty() && !a.back()) a.pop_back();
  }
  static CEXP bool h_lt_(citer a, citer a_end, citer b, citer b_end) NE {
    usz asz = usz(a_end - a), bsz = usz(b_end - b);
    if (asz != bsz) {
      if (asz < bsz) {
        if (find_if(b + asz, b_end, [](u32 x) { return x; }) != b_end) return true;
        b_end = b + asz;
      } else {
        if (find_if(a + bsz, a_end, [](u32 x) { return x; }) != a_end) return false;
        a_end = a + bsz;
      }
      asz = usz(a_end - a);
    }
    for (usz i = asz - 1; ~i; --i)
      if (a[i] != b[i]) return a[i] < b[i];
    return false;
  }
  static CEXP bool h_lt_(vecu CR a, vecu CR b) NE {
    usz asz = h_nz_size_(a), bsz = h_nz_size_(b);
    if (asz != bsz) return asz < bsz;
    for (usz i = asz - 1; ~i; --i)
      if (a[i] != b[i]) return a[i] < b[i];
    return false;
  }
  static CEXP bool h_leq_(vecu CR a, vecu CR b) NE { return h_eq_(a, b) || h_lt_(a, b); }
  static CEXP i32 h_cmp_mag_(vecu CR a, vecu CR b) NE {
    usz asz = h_nz_size_(a), bsz = h_nz_size_(b);
    if (asz != bsz) {
      retif_((asz < bsz), -1, 1);
    }
    for (usz i = asz - 1; ~i; --i)
      if (a[i] != b[i]) {
        retif_((a[i] < b[i]), -1, 1);
      }
    return 0;
  }

  static CEXP void h_add_(citer a, citer a_end, citer b, citer b_end, iter c, iter c_end) NE {
    if (a_end - a < b_end - b) std::swap(a, b), std::swap(a_end, b_end);
    usz asz = usz(a_end - a), bsz = usz(b_end - b);
    assert(asz <= usz(c_end - c));
    u32 carry = 0;
    u64 v;
    flt_ (usz, i, 0, bsz) c[i] = u32(v = (u64)a[i] + b[i] + carry), carry = u32(v >> 32);
    flt_ (usz, i, bsz, asz) c[i] = u32(v = (u64)a[i] + carry), carry = u32(v >> 32);
    if (carry) c[asz] = carry;
  }
  static CEXP void h_add_(iter a, iter a_end, citer b, citer b_end) NE {
    usz asz = usz(a_end - a), bsz = usz(b_end - b);
    u32 carry = 0;
    u64 v;
    flt_ (usz, i, 0, bsz) a[i] = u32(v = (u64)a[i] + b[i] + carry), carry = u32(v >> 32);
    for (usz i = bsz; carry && i < asz; ++i) a[i] = u32(v = (u64)a[i] + carry), carry = u32(v >> 32);
  }
  static CEXP vecu h_add_(vecu CR a, vecu CR b) NE {
    vecu c(max(a.size(), b.size()) + 1);
    h_add_(a.data(), a.data() + a.size(), b.data(), b.data() + b.size(), c.data(), c.data() + c.size()), h_shrink_(c);
    return c;
  }

  static CEXP void h_sub_(iter a, iter a_end, citer b, citer b_end) NE {
    usz asz = usz(a_end - a), bsz = usz(b_end - b);
    i32 carry = 0;
    i64 v;
    flt_ (usz, i, 0, bsz) a[i] = u32(v = (i64)a[i] - b[i] + carry), carry = i32(v >> 32);
    for (usz i = bsz; carry && i < asz; ++i) a[i] = u32(v = (i64)a[i] + carry), carry = i32(v >> 32);
    assert(!carry);
  }
  static CEXP vecu h_sub_(vecu CR a, vecu CR b) NE {
    assert(h_leq_(b, a));
    vecu c = a;
    h_sub_(c.data(), c.data() + c.size(), b.data(), b.data() + b.size()), h_shrink_(c);
    return c;
  }

  static CEXP void h_mul_naive_(citer a, citer a_end, citer b, citer b_end, iter c, iter c_end) NE {
    usz asz = usz(a_end - a), bsz = usz(b_end - b);
    if (!asz || !bsz) return;
    assert(usz(c_end - c) == asz + bsz);
    flt_ (usz, i, 0, asz) {
      u32 carry = 0;
      u64 p;
      flt_ (usz, j, 0, bsz) c[i + j] = u32(p = (u64)a[i] * b[j] + carry + c[i + j]), carry = u32(p >> 32);
      c[i + bsz] = carry;
    }
  }
  static CEXP void h_mul_(citer a, citer a_end, citer b, citer b_end, iter c, iter c_end) NE {
    if (a_end - a < b_end - b) std::swap(a, b), std::swap(a_end, b_end);
    usz asz = usz(a_end - a), bsz = usz(b_end - b);
    assert(usz(c_end - c) == asz + bsz);
    if (bsz <= 128) return h_mul_naive_(a, a_end, b, b_end, c, c_end);
    usz n = (asz + 1) >> 1;
    if (bsz <= n) {
      h_mul_(a, a + n, b, b_end, c, c + (n + bsz));
      vecu carry(c + n, c + (n + bsz));
      fill(c + n, c + (n + bsz), 0), h_mul_(a + n, a_end, b, b_end, c + n, c_end), h_add_(c + n, c_end, carry.data(), carry.data() + carry.size());
      return;
    }
    vecu a1(n + 1), b1(n + 1), z1(2 * n + 2);
    h_mul_(a, a + n, b, b + n, c, c + (n + n)), h_mul_(a + n, a_end, b + n, b_end, c + (n + n), c_end), h_add_(a, a + n, a + n, a_end, a1.data(), a1.data() + a1.size()), h_add_(b, b + n, b + n, b_end, b1.data(), b1.data() + b1.size()), h_mul_(a1.data(), a1.data() + a1.size(), b1.data(), b1.data() + b1.size(), z1.data(), z1.data() + z1.size()), h_sub_(z1.data(), z1.data() + z1.size(), c, c + (n + n)), h_sub_(z1.data(), z1.data() + z1.size(), c + (n + n), c_end), h_shrink_(z1), h_add_(c + n, c_end, z1.data(), z1.data() + z1.size());
  }
  static CEXP vecu h_mul_(vecu CR a, vecu CR b) NE {
    if (h_is0_(a) || h_is0_(b)) return {};
    if (h_is_one_(a)) return b;
    if (h_is_one_(b)) return a;
    vecu c(a.size() + b.size());
    h_mul_(a.data(), a.data() + a.size(), b.data(), b.data() + b.size(), c.data(), c.data() + c.size()), h_shrink_(c);
    return c;
  }

  static CEXP u64 h_it2u64_(citer it, citer end) NE {
    u64 res = 0;
    u32 sh = 0;
    while (it != end) res |= ((u64)*it++) << sh, sh += 32;
    return res;
  }
  static CEXP void h_u642it_(u64 x, iter it, iter end) NE {
    while (x) {
      assert(it < end);
      *it++ = (u32)x, x >>= 32;
    }
  }
  static CEXP void h_lsh_(iter a, iter a_end, int shift) NE {
    if (!shift) return;
    int back = 32 - shift;
    u32 carry = 0, v;
    flt_ (iter, it, a, a_end) v = (*it << shift) | carry, carry = (*it >> back), *it = v;
    assert(!carry);
  }
  static CEXP void h_rsh_(iter a, iter a_end, int shift) NE {
    if (!shift) return;
    int back = 32 - shift;
    u32 carry = 0, v;
    for (iter it = a_end - 1; a <= it; --it) v = (*it >> shift) | carry, carry = (*it << back), *it = v;
    assert(!carry);
  }

  static CEXP u32 h_div_naive_th_ = 64;
  static CEXP void h_divmod_naive_(citer a, citer a_end, citer b, citer b_end, iter quo, iter quo_end, iter rem, iter rem_end) NE {
    usz asz = usz(a_end - a), bsz = usz(b_end - b);
    assert(bsz > 0);
    if (bsz == 1) {
      u64 carry = 0, v;
      for (usz i = asz - 1; ~i; --i) quo[i] = u32((v = (carry << 32) | a[i]) / (*b)), carry = v - quo[i] * (*b);
      *rem = (u32)carry;
      return;
    }
    if (max(asz, bsz) <= 2) {
      u64 a64 = h_it2u64_(a, a_end), b64 = h_it2u64_(b, b_end);
      h_u642it_(a64 / b64, quo, quo_end), h_u642it_(a64 % b64, rem, rem_end);
      return;
    }
    if (h_lt_(a, a_end, b, b_end)) {
      if (asz > bsz) a_end = a + bsz;
      copy(a, a_end, rem);
      return;
    }
    auto sh = std::countl_zero(*(b_end - 1));
    vecu x(asz + (std::countl_zero(*(a_end - 1)) < sh)), y(usz(b_end - b));
    copy(a, a_end, x.begin()), copy(b, b_end, y.data()), h_lsh_(x.data(), x.data() + x.size(), sh), h_lsh_(y.data(), y.data() + y.size(), sh);
    u32 yb = y.back();
    vecu qv(x.size() - y.size() + 1), rv(x.end() - (int)y.size(), x.end());
    for (usz i = (u32)qv.size() - 1; ~i; --i) {
      if (rv.size() == y.size()) {
        if (h_leq_(y, rv)) qv[i] = 1, rv = h_sub_(rv, y);
      } else if (rv.size() > y.size()) {
        u64 q = (((u64)rv[rv.size() - 1] << 32) | rv[rv.size() - 2]) / yb;
        if (q > (u64)-1_u32) q = (u64)-1_u32;
        vecu yq = h_mul_(y, vecu{(u32)q});
        while (h_lt_(rv, yq)) --q, yq = h_sub_(yq, y);
        rv = h_sub_(rv, yq);
        while (h_leq_(y, rv)) ++q, rv = h_sub_(rv, y);
        qv[i] = (u32)q;
      }
      if (i) rv.insert(rv.begin(), x[i - 1]);
      h_shrink_(rv);
    }
    h_shrink_(qv), h_rsh_(rv.data(), rv.data() + rv.size(), sh), h_shrink_(rv), copy(qv.data(), qv.data() + qv.size(), quo), copy(rv.data(), rv.data() + rv.size(), rem);
  }

  static CEXP void h_divmod_d2n1n_(citer a, citer a_end, citer b, citer b_end, iter quo, iter quo_end, iter rem, iter rem_end) {
    usz n = usz(b_end - b);
    if ((n & 1) || n <= h_div_naive_th_) {
      h_divmod_naive_(a, a_end, b, b_end, quo, quo_end, rem, rem_end);
      return;
    }
    usz half = n >> 1;
    vecu r1(n + half + 1);
    copy(a, a + half, r1.data()), h_divmod_d3n2n_impl_(a + half, a_end, b, b_end, quo + half, quo_end, r1.data() + half, r1.data() + r1.size()), h_divmod_d3n2n_impl_(r1.data(), r1.data() + r1.size() - 1, b, b_end, quo, quo + half, rem, rem_end);
  }
  static CEXP void h_divmod_d3n2n_impl_(citer a, citer a_end, citer b, citer b_end, iter quo, iter quo_end, iter rem, iter rem_end) {
    usz n = usz(b_end - b) >> 1;
    vecu d(2 * n);
    if (h_lt_(a + (n + n), a_end, b + n, b_end)) h_divmod_d2n1n_(a + n, a_end, b + n, b_end, quo, quo_end, rem + n, rem_end), h_mul_(quo, quo_end, b, b + n, d.data(), d.data() + d.size());
    else fill(quo, quo_end, -1_u32), h_add_(a + n, a + (n + n), b + n, b_end, rem + n, rem_end), copy(b, b + n, d.data() + n), h_sub_(d.data(), d.data() + d.size(), b, b + n);
    copy(a, a + n, rem);
    while (h_lt_(rem, rem_end, d.data(), d.data() + d.size())) {
      vecu one{1};
      h_add_(rem, rem_end, b, b_end), h_sub_(quo, quo_end, one.data(), one.data() + one.size());
    }
    h_sub_(rem, rem_end, d.data(), d.data() + d.size());
  }

  static CEXP void h_divmod_(citer a, citer a_end, citer b, citer b_end, iter q, iter q_end, iter r, iter r_end) NE {
    usz asz = usz(a_end - a), bsz = usz(b_end - b), rsz = usz(r_end - r);
    if (std::min(asz - bsz, bsz) <= h_div_naive_th_) return h_divmod_naive_(a, a_end, b, b_end, q, q_end, r, r_end);
    usz n;
    {
      usz m = (bsz + h_div_naive_th_ - 1) / h_div_naive_th_;
      if (m > 1) m = 1_usz << (32 - std::countl_zero(u32(m - 1)));
      n = ((bsz + m - 1) / m) * m;
    }
    int sd = (int)n - (int)bsz, ssh = std::countl_zero(*(b_end - 1));
    vecu x(asz + (usz)sd + (std::countl_zero(*(a_end - 1)) <= ssh)), y(n), rr(n + 1), z(2 * n);
    copy(a, a_end, x.begin() + sd), copy(b, b_end, y.begin() + sd), h_lsh_(x.data() + sd, x.data() + x.size(), ssh), h_lsh_(y.data() + sd, y.data() + y.size(), ssh);
    usz t = max(2_usz, (x.size() + n - 1) / n);
    copy(x.data() + ((t - 2) * n), x.data() + x.size(), z.data());
    if (usz q_ulen = usz(q_end - (q + ((t - 2) * n))); q_ulen < n) {
      vecu qq(n);
      h_divmod_d2n1n_(z.data(), z.data() + z.size(), y.data(), y.data() + y.size(), qq.data(), qq.data() + qq.size(), rr.data(), rr.data() + rr.size()), copy(qq.data(), qq.data() + q_ulen, q + ((t - 2) * n));
    } else h_divmod_d2n1n_(z.data(), z.data() + z.size(), y.data(), y.data() + y.size(), q + ((t - 2) * n), q + ((t - 1) * n), rr.data(), rr.data() + rr.size());
    for (u32 i = (u32)t - 3; ~i; --i) copy(x.data() + i * n, x.data() + (i + 1) * n, z.data()), copy(rr.data(), rr.data() + n, z.data() + n), fill(rr.data(), rr.data() + rr.size(), 0), h_divmod_d2n1n_(z.data(), z.data() + z.size(), y.data(), y.data() + y.size(), q + i * n, q + (i + 1) * n, rr.data(), rr.data() + rr.size());
    h_shrink_(rr), copy(rr.data() + sd, rr.data() + sd + rsz, r), h_rsh_(r, r_end, ssh);
  }

  static CEXP ptt<vecu> h_divmod_(vecu CR a, vecu CR b) NE {
    assert(!h_is0_(b));
    if (a.size() < b.size()) return {{}, a};
    vecu q(a.size() - b.size() + 1), r(b.size());
    h_divmod_(a.data(), a.data() + a.size(), b.data(), b.data() + b.size(), q.data(), q.data() + q.size(), r.data(), r.data() + r.size()), h_shrink_(q), h_shrink_(r);
    return {q, r};
  }

  static CEXP vecu uadd(vec_like CR a, vec_like CR b) NE {
    vecu c(max(a.size(), b.size()) + 1);
    flt_ (u32, i, 0, (u32)a.size()) c[i] += a[i];
    flt_ (u32, i, 0, (u32)b.size()) c[i] += b[i];
    flt_ (u32, i, 0, (u32)c.size() - 1)
      if (c[i] >= D) c[i] -= D, ++c[i + 1];
    shrink_(c);
    return c;
  }
  static CEXP vecu usub(vec_like CR a, vec_like CR b) NE {
    assert(std::is_lteq(ucmp(b, a)));
    vecu c = a;
    u32 borrow = 0;
    flt_ (u32, i, 0, (u32)a.size()) {
      if (i < b.size()) borrow += b[i];
      if (c[i] -= borrow, borrow = 0; (i32)c[i] < 0) c[i] += D, borrow = 1;
    }
    assert(!borrow);
    shrink_(c);
    return c;
  }
  static CEXP vecu umul_3ntt(vec_like CR a, vec_like CR b) NE {
    if (a.empty() || b.empty()) return {};
    auto m = conv_u128(a, b);
    vecu c;
    c.reserve(m.size() + 3);
    u128 x = 0;
    for (u32 i = 0;; ++i) {
      if (i >= m.size() && !x) break;
      if (i < m.size()) x += m[i];
      c.push_back(u32(x % D)), x /= D;
    }
    shrink_(c);
    return c;
  }
  static CEXP vecu umul_bf(vec_like CR a, vec_like CR b) NE {
    if (a.empty() || b.empty()) return {};
    vecuu prod(a.size() + b.size() - 1 + 1);
    flt_ (u32, i, 0, (u32)a.size())
      flt_ (u32, j, 0, (u32)b.size())
        if ((prod[i + j] += (u64)a[i] * b[j]) >= 4_u64 * D * D) prod[i + j] -= 4_u64 * D * D, prod[i + j + 1] += 4_u64 * D;
    vecu c(prod.size() + 1);
    u64 x = 0;
    u32 i = 0;
    for (; i < prod.size(); ++i) x += prod[i], c[i] = u32(x % D), x /= D;
    while (x) c[i] = u32(x % D), x /= D, ++i;
    shrink_(c);
    return c;
  }
  static CEXP vecu umul(vec_like CR a, vec_like CR b) NE {
    if (is_0(a) || is_0(b)) return {};
    if (is_pm1(a)) return b;
    if (is_pm1(b)) return a;
    if (min(a.size(), b.size()) <= CONV_NAIVE_THRESHOLD) {
      retif_((a.size() < b.size()), umul_bf(b, a), umul_bf(a, b));
    } else return umul_3ntt(a, b);
  }
  // 0 <= A < 1e16, 1 <= B < 1e8
  static CEXP ptt<vecu> udivmod_li(vec_like CR a, vec_like CR b) NE {
    assert(a.size() <= 2 && b.size() == 1);
    i64 va = uvec2i64(a);
    u32 vb = b[0];
    return {int2vecu(va / vb), int2vecu(va % vb)};
  }
  // 0 <= A < 1e16, 1 <= B < 1e16
  static CEXP ptt<vecu> udivmod_ll(vec_like CR a, vec_like CR b) NE {
    assert(a.size() <= 2 && b.size() && b.size() <= 2);
    i64 va = uvec2i64(a), vb = uvec2i64(b);
    return {int2vecu(va / vb), int2vecu(va % vb)};
  }
  // 1 <= B < 1e8
  static CEXP ptt<vecu> udivmod_1e8(vec_like CR a, vec_like CR b) NE {
    if (assert(b.size() == 1); b[0] == 1) return {a, {}};
    if (a.size() <= 2) return udivmod_li(a, b);
    vecu quo(a.size());
    u64 d = 0;
    u32 b0 = b[0];
    for (u32 i = (u32)a.size() - 1; ~i; --i) d = d * D + a[i], assert(d < (u64)D * b0), quo[i] = u32(d / b0), d = d % b0;
    shrink_(quo);
    return {quo, d ? vecu{u32(d)} : vecu{}};
  }
  // 0 <= A, 1 <= B
  static CEXP ptt<vecu> udivmod_bf(vec_like CR a, vec_like CR b) NE {
    if (assert(!is_0(b) && b.size()); b.size() == 1) return udivmod_1e8(a, b);
    if (max(a.size(), b.size()) <= 2) return udivmod_ll(a, b);
    if (std::is_lt(ucmp(a, b))) return {{}, a};
    // B >= 1e8, A >= B
    u32 norm = D / (b.back() + 1);
    vecu x = umul(a, vecu{norm}), y = umul(b, vecu{norm});
    u32 yb = y.back();
    vecu quo(x.size() - y.size() + 1), rem(x.end() - (int)y.size(), x.end());
    for (u32 i = (u32)quo.size() - 1; ~i; --i) {
      if (rem.size() == y.size()) {
        if (std::is_lteq(ucmp(y, rem))) quo[i] = 1, rem = usub(rem, y);
      } else if (rem.size() > y.size()) {
        assert(y.size() + 1 == rem.size());
        u32 q = u32(((u64)rem[rem.size() - 1] * D + rem[rem.size() - 2]) / yb);
        vecu yq = umul(y, vecu{q});
        while (std::is_lt(ucmp(rem, yq))) --q, yq = usub(yq, y);
        rem = usub(rem, yq);
        while (std::is_lteq(ucmp(y, rem))) ++q, rem = usub(rem, y);
        quo[i] = q;
      }
      if (i) rem.insert(rem.begin(), x[i - 1]);
    }
    shrink_(quo), shrink_(rem);
    auto [q2, r2] = udivmod_1e8(rem, vecu{norm});
    assert(is_0(r2));
    return {quo, q2};
  }
  // 1 / a, abserr = B^{-deg}
  static CEXP vecu inv_(vec_like CR a, u32 deg) {
    assert(!a.empty() && D / 2 <= a.back() && a.back() < D);
    u32 k = deg, c = (u32)a.size();
    while (k > 64) k = (k + 1) / 2;
    vecu z(c + k + 1);
    z.back() = 1, z = udivmod_bf(z, a).first;
    while (k < deg) {
      vecu s = umul(z, z);
      s.insert(s.begin(), 0);
      u32 d = min(c, 2 * k + 1);
      vecu t{a.end() - d, a.end()}, u = umul(s, t), w(k + 1), w2 = uadd(z, z);
      u.erase(u.begin(), u.begin() + d), copy(w2, std::back_inserter(w));
      (z = usub(w, u)).erase(z.begin()), k *= 2;
    }
    z.erase(z.begin(), z.begin() + k - deg);
    return z;
  }
  static CEXP ptt<vecu> udivmod(vec_like CR a, vec_like CR b) NE {
    if (assert(!is_0(b)); b.size() <= 64) return udivmod_bf(a, b);
    if ((int)(a.size() - b.size()) <= 64) return udivmod_bf(a, b);
    u32 norm = D / (b.back() + 1);
    vecu x = umul(a, vecu{norm}), y = umul(b, vecu{norm});
    u32 s = (u32)x.size(), t = (u32)y.size(), deg = s + 2 - t;
    vecu z = inv_(y, deg), q = umul(x, z);
    q.erase(q.begin(), q.begin() + t + deg);
    vecu yq = umul(y, vecu{q});
    while (std::is_lt(ucmp(x, yq))) q = usub(q, vecu{1}), yq = usub(yq, y);
    vecu r = usub(x, yq);
    while (std::is_lteq(ucmp(y, r))) q = uadd(q, vecu{1}), r = usub(r, y);
    shrink_(q), shrink_(r);
    auto [q2, r2] = udivmod_1e8(r, vecu{norm});
    assert(is_0(r2));
    return {q, q2};
  }

#undef vec_like
};

}  // namespace tifa_libs
