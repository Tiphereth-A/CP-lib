#ifndef TIFALIBS_IO_FASTIO
#define TIFALIBS_IO_FASTIO

#include "../util/traits.hpp"

namespace tifa_libs {

class fastout {
  CEXP static u32 BUF = 0x200005, INTBUF = 63;
  FILE *f_ = nullptr;
  char int_buf[INTBUF];
  char buf[BUF], *p;
  const char *const ed = buf + BUF;
  std::chars_format fmt = std::chars_format::general;
  int precision = 6;

  fastout &write_str(const char *n, usz len = 0) NE {
    if (!len) len = strlen(n);
    usz l_;
    const char *n_ = n;
    while (p + len >= ed) memcpy(p, n_, l_ = usz(ed - p)), p += l_, n_ += l_, len -= l_, flush();
    return memcpy(p, n_, len), p += len, *this;
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
  fastout &operator<<(const char *n) NE { return write_str(n); }
  fastout &operator<<(strn CR str) NE { return *this << str.c_str(); }
  fastout &operator<<(strnv str) NE { return write_str(str.data(), str.size()); }
  template <class T>
  requires(sint_c<T> && !char_c<T> && sizeof(T) <= 8)
  fastout &operator<<(T n) NE {
    if (n < 0) (*this << '-'), n = -n;
    return *this << to_uint_t<T>(n);
  }
  template <class T>
  requires(uint_c<T> && !char_c<T> && sizeof(T) <= 8)
  fastout &operator<<(T n) NE {
    if CEXP (std::same_as<T, bool>) return *this << (char(n | '0'));
    else {
      auto res = std::to_chars(int_buf, int_buf + INTBUF, n);
      return write_str(int_buf, res.ptr - int_buf);
    }
  }
  fastout &operator<<(std::floating_point auto n) NE {
    auto res = std::to_chars(int_buf, int_buf + INTBUF, n, fmt, precision);
    return write_str(int_buf, res.ptr - int_buf);
  }
  fastout &setf(std::chars_format f) NE {
    fmt = f;
    return *this;
  }
  //! only tested in libstdc++
  fastout &operator<<(decltype(std::setprecision(0)) p) NE {
    precision = *(int *)(&p);
    return *this;
  }
  fastout &operator<<(fastout &(*func)(fastout &)) NE { return func(*this); }
};
inline fastout fout;
inline fastout &scientific(fastout &f) NE { return f.setf(std::chars_format::scientific); }
inline fastout &fixed(fastout &f) NE { return f.setf(std::chars_format::fixed); }
inline fastout &hexfloat(fastout &f) NE { return f.setf(std::chars_format::hex); }
inline fastout &defaultfloat(fastout &f) NE { return f.setf(std::chars_format::general); }
inline fastout &endl(fastout &f) NE {
  (f << '\n').flush();
  return f;
}
using std::setprecision;

}  // namespace tifa_libs

#endif