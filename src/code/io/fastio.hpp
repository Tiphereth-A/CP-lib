#ifndef TIFALIBS_IO_FASTIO
#define TIFALIBS_IO_FASTIO

#include "../fast/u32tostr.hpp"
#include "../util/traits.hpp"
#ifdef __linux__
#include <sys/mman.h>
#include <sys/stat.h>
#endif

namespace tifa_libs {
namespace fastio_impl_ {
//! UB if EOF occured during reading
template <u32 BUF>
class fastin {
  FILE *f_ = nullptr;
#ifdef __linux__
  char *bg, *ed, *p;
  struct stat Fl;

 public:
  fastin(FILE *f = stdin) NE { assert(f), rebind(f); }
  ~fastin() NE { rebind(); }
  void rebind(FILE *f = nullptr) NE {
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
    if (!f_) munmap(bg, Fl.st_size + 1);
#pragma GCC diagnostic warning "-Wmaybe-uninitialized"
    if (!f) return;
    auto fd = fileno(f_ = f);
    fstat(fd, &Fl);
    p = (bg = (char *)mmap(nullptr, Fl.st_size + 4, PROT_READ, MAP_PRIVATE, fd, 0));
    ed = bg + Fl.st_size;
    madvise(bg, Fl.st_size + 4, MADV_SEQUENTIAL);
  }
  char peek() NE { return *p; }
  char get() NE { return *p++; }
  bool iseof() NE { return p == ed; }

#else
  char buf[BUF], *ed, *p;

 public:
  fastin(FILE *f = stdin) NE { rebind(f); }
  void rebind(FILE *f) NE { f_ = f, p = ed = buf; }
  char peek() NE { return p == ed && (ed = (p = buf) + fread(buf, 1, BUF, f_), p == ed) ? EOF : *p; }
  char get() NE { return p == ed && (ed = (p = buf) + fread(buf, 1, BUF, f_), p == ed) ? EOF : *p++; }
  bool iseof() NE { return peek() == EOF; }
#endif
  template <class T>
  requires(sint_c<T> && !char_c<T>)
  fastin &read(T &n) NE {
    bool is_neg = false;
    char ch = get();
    while (!isdigit(ch)) is_neg |= ch == '-', ch = get();
    n = 0;
    while (isdigit(ch)) (n *= 10) += ch & 15, ch = get();
    if (is_neg) n = -n;
    return *this;
  }
  template <class T>
  requires(uint_c<T> && !char_c<T>)
  fastin &read(T &n) NE {
    char ch = get();
    while (!isdigit(ch)) ch = get();
    n = 0;
    while (isdigit(ch)) (n *= 10) += ch & 15, ch = get();
    return *this;
  }
  template <mint_c T>
  fastin &read(T &n) NE {
    decltype(std::declval<T>().sval()) x;
    read(x), n = T(x);
    return *this;
  }
  //! ignore cntrl and space
  fastin &read(char_c auto &n) NE {
    while (!isgraph(n = get()));
    return *this;
  }
  fastin &read(strn &n) NE {
    n.clear();
    char n_;
    while (!isgraph(n_ = get()));
    n.push_back(n_);
    while (isgraph(n_ = get())) n.push_back(n_);
    return *this;
  }
  template <class T, class U>
  fastin &read(std::pair<T, U> &p) NE { return read(p.first).read(p.second); }
  template <class... Ts>
  fastin &read(std::tuple<Ts...> &p) NE {
    std::apply([&](Ts &...targs) NE { ((read(targs)), ...); }, p);
    return *this;
  }
  fastin &read(container_c auto &p) NE {
    if (p.begin() == p.end()) return *this;
    for (auto &i : p) read(i);
    return *this;
  }
  fastin &getline(char *n) NE {
    char *n_ = n;
    while (!isprint(*n_ = get()));
    while (isprint(*(++n_) = get()));
    *n_ = '\0';
    return *this;
  }
  fastin &getline(strn &n) NE {
    char n_;
    while (!isprint(n_ = get()));
    n.push_back(n_);
    while (isprint(n_ = get())) n.push_back(n_);
    return *this;
  }
  //! NOT ignore cntrl and space
  fastin &strict_read(char_c auto &n) NE {
    n = get();
    return *this;
  }
  template <class T>
  fastin &operator>>(T &val) NE { return read(val); }
};
template <u32 BUF, u32 INTBUF>
class fastout {
  FILE *f_ = nullptr;
  char int_buf[INTBUF], *p_ib = int_buf;
  char buf[BUF], *p;
  const char *const ed = buf + BUF;

 public:
  fastout(FILE *f = stdout) NE { rebind(f); }
  ~fastout() NE { flush(); }
  void rebind(FILE *f) NE { f_ = f, p = buf; }
  void flush() NE { fwrite(buf, 1, usz(p - buf), f_), p = buf; }
  template <char_c T>
  fastout &write(T n) NE {
    if (p == ed) [[unlikely]]
      flush();
    *(p++) = n;
    return *this;
  }
  fastout &write(const char *n) NE {
    usz len = strlen(n), l_;
    const char *n_ = n;
    while (p + len >= ed) memcpy(p, n_, l_ = usz(ed - p)), p += l_, n_ += l_, len -= l_, flush();
    memcpy(p, n_, len), p += len;
    return *this;
  }
  template <class T>
  requires(sint_c<T> && !char_c<T>)
  fastout &write(T n) NE {
    if (n < 0) write('-');
    return write(n < 0 ? -to_uint_t<T>(n) : to_uint_t<T>(n));
  }
  template <class T>
  requires(uint_c<T> && !char_c<T>)
  fastout &write(T n) NE {
    if CEXP (sizeof(T) <= 4) {
      memset(p_ib = int_buf, 0, 11), u32tostr(n, p_ib);
      return write(p_ib);
    }
    p_ib = int_buf + INTBUF - 1;
    do *(--(p_ib)) = char(n % 10) | '0';
    while (n /= 10);
    return write(p_ib);
  }
  fastout &write(mint_c auto n) NE { return write(n.val()); }
  fastout &write(strn CR str) NE { return write(str.c_str()); }
  template <class T, class U>
  fastout &write(std::pair<T, U> CR p) NE { return write(p.first).space().write(p.second); }
  template <class... Ts>
  fastout &write(std::tuple<Ts...> CR p) NE {
    std::apply([&](Ts CR... targs) NE { usz n{0}; ((write(targs).space_if(++n != sizeof...(Ts))), ...); }, p);
    return *this;
  }
  fastout &write(container_c auto CR p) NE {
    if (p.begin() == p.end()) return *this;
    auto it = p.begin();
    for (write(*it++); it != p.end(); ++it) space().write(*it);
    return *this;
  }
  fastout &linebreak() NE { return write('\n'); }
  fastout &linebreak_if(bool flag) NE { return flag ? linebreak() : *this; }
  fastout &space() NE { return write(' '); }
  fastout &space_if(bool flag) NE { return flag ? space() : *this; }
  template <class T>
  fastout &operator<<(T CR val) NE { return write(val); }
};
}  // namespace fastio_impl_
inline fastio_impl_::fastin<0x200005> fin;
inline fastio_impl_::fastout<0x200005, 41> fout;

}  // namespace tifa_libs

#endif