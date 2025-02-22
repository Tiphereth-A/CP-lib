#ifndef TIFALIBS_IO_FASTIO
#define TIFALIBS_IO_FASTIO

#include "../util/traits.hpp"

namespace tifa_libs {

class fastout {
  CEXP static u32 BUF = 0x200005, INTBUF = 41;
  FILE *f_ = nullptr;
  char int_buf[INTBUF];
  char buf[BUF], *p;
  const char *const ed = buf + BUF;
  std::chars_format fmt = std::chars_format::general;
  int precision = 6;

  template <bool use_memmove>
  fastout &write_str(const char *n) NE {
    usz len = strlen(n), l_;
    const char *n_ = n;
    if CEXP (use_memmove) {
      while (p + len >= ed) memmove(p, n_, l_ = usz(ed - p)), p += l_, n_ += l_, len -= l_, flush();
      memmove(p, n_, len), p += len;
    } else {
      while (p + len >= ed) memcpy(p, n_, l_ = usz(ed - p)), p += l_, n_ += l_, len -= l_, flush();
      memcpy(p, n_, len), p += len;
    }
    return *this;
  }

 public:
  fastout(FILE *f = stdout) NE { rebind(f); }
  ~fastout() NE { flush(); }
  void rebind(FILE *f) NE { f_ = f, p = buf; }
  void flush() NE { fwrite(buf, 1, usz(p - buf), f_), p = buf; }
  fastout &operator<<(char_c auto n) NE {
    if (p == ed) [[unlikely]]
      flush();
    return (*(p++) = n), *this;
  }
  fastout &operator<<(const char *n) NE { return write_str<false>(n); }
  template <class T>
  requires(std::signed_integral<T> && !char_c<T>)
  fastout &operator<<(T n) NE {
    if (n < 0) (*this << '-'), n = -n;
    return *this << to_uint_t<T>(n);
  }
  template <class T>
  requires(std::unsigned_integral<T> && !char_c<T>)
  fastout &operator<<(T n) NE {
    if CEXP (std::same_as<T, bool>) return *this << (char(n | '0'));
    return std::to_chars(int_buf, int_buf + INTBUF, n), write_str<true>(int_buf);
  }
  fastout &operator<<(std::floating_point auto n) NE { return std::to_chars(int_buf, int_buf + INTBUF, n, fmt, precision), write_str<true>(int_buf); }
  fastout &operator<<(strn CR str) NE { return *this << str.c_str(); }
  fastout &setf(std::chars_format f) NE { return (fmt = f), *this; }
  //! only tested in libstdc++
  fastout &operator<<(decltype(std::setprecision(0)) p) NE { return (precision = *(int *)(&p)), *this; }
  fastout &operator<<(fastout &(*func)(fastout &)) NE { return func(*this); }
};
inline fastout fout;
inline fastout &scientific(fastout &f) NE { return f.setf(std::chars_format::scientific); }
inline fastout &fixed(fastout &f) NE { return f.setf(std::chars_format::fixed); }
inline fastout &hexfloat(fastout &f) NE { return f.setf(std::chars_format::hex); }
inline fastout &defaultfloat(fastout &f) NE { return f.setf(std::chars_format::general); }
inline fastout &endl(fastout &f) NE { return (f << '\n').flush(), f; }
using std::setprecision;

}  // namespace tifa_libs

#endif