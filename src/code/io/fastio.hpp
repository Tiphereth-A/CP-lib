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
  fastin(FILE *f = stdin) { assert(f), rebind(f); }
  ~fastin() { rebind(); }
  void rebind(FILE *f = nullptr) {
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
    if (!f_) munmap(bg, Fl.st_size + 1);
#pragma GCC diagnostic warning "-Wmaybe-uninitialized"
    if (!f) return;
    auto fd = fileno(f_ = f);
    fstat(fd, &Fl), p = (bg = (char *)mmap(0, Fl.st_size + 4, PROT_READ, MAP_PRIVATE, fd, 0)), ed = bg + Fl.st_size, madvise(bg, Fl.st_size + 4, MADV_SEQUENTIAL);
  }
  char peek() { return *p; }
  char get() { return *p++; }
  bool iseof() { return p == ed; }

#else
  char buf[BUF], *ed, *p;

 public:
  fastin(FILE *f = stdin) { rebind(f); }
  void rebind(FILE *f) { f_ = f, p = ed = buf; }
  char peek() { return p == ed && (ed = (p = buf) + fread(buf, 1, BUF, f_), p == ed) ? EOF : *p; }
  char get() { return p == ed && (ed = (p = buf) + fread(buf, 1, BUF, f_), p == ed) ? EOF : *p++; }
  bool iseof() { return peek() == EOF; }
#endif
  template <class T>
  requires(sint_c<T> && !char_c<T>)
  fastin &read(T &n) {
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
  fastin &read(T &n) {
    char ch = get();
    while (!isdigit(ch)) ch = get();
    n = 0;
    while (isdigit(ch)) (n *= 10) += ch & 15, ch = get();
    return *this;
  }
  template <mint_c T>
  fastin &read(T &n) {
    decltype(std::declval<T>().sval()) x;
    return read(x), n = T(x), *this;
  }
  //! ignore cntrl and space
  template <char_c T>
  fastin &read(T &n) {
    while (!isgraph(n = get()));
    return *this;
  }
  fastin &read(strn &n) {
    n.clear();
    char n_;
    while (!isgraph(n_ = get()));
    n.push_back(n_);
    while (isgraph(n_ = get())) n.push_back(n_);
    return *this;
  }
  template <class T, class U>
  fastin &read(std::pair<T, U> &p) { return read(p.first).read(p.second); }
  template <class... Ts>
  fastin &read(std::tuple<Ts...> &p) {
    return std::apply([&](Ts &...targs) { ((read(targs)), ...); }, p), *this;
  }
  template <container_c T>
  fastin &read(T &p) {
    if (p.begin() == p.end()) return *this;
    for (auto &i : p) read(i);
    return *this;
  }
  fastin &getline(char *n) {
    char *n_ = n;
    while (!isprint(*n_ = get()));
    while (isprint(*(++n_) = get()));
    return *n_ = '\0', *this;
  }
  fastin &getline(strn &n) {
    char n_;
    while (!isprint(n_ = get()));
    n.push_back(n_);
    while (isprint(n_ = get())) n.push_back(n_);
    return *this;
  }
  //! NOT ignore cntrl and space
  template <char_c T>
  fastin &strict_read(T &n) { return n = get(), *this; }
  template <class T>
  fastin &operator>>(T &val) { return read(val); }
};
template <u32 BUF, u32 INTBUF>
class fastout {
  FILE *f_ = nullptr;
  char int_buf[INTBUF], *p_ib = int_buf;
  char buf[BUF], *p;
  const char *const ed = buf + BUF;

 public:
  fastout(FILE *f = stdout) { rebind(f); }
  ~fastout() { flush(); }
  void rebind(FILE *f) { f_ = f, p = buf; }
  void flush() { fwrite(buf, 1, usz(p - buf), f_), p = buf; }
  template <char_c T>
  fastout &write(T n) {
    if (p == ed) [[unlikely]]
      flush();
    return *(p++) = n, *this;
  }
  fastout &write(const char *n) {
    usz len = strlen(n), l_;
    const char *n_ = n;
    while (p + len >= ed) memcpy(p, n_, l_ = usz(ed - p)), p += l_, n_ += l_, len -= l_, flush();
    return memcpy(p, n_, len), p += len, *this;
  }
  template <class T>
  requires(sint_c<T> && !char_c<T>)
  fastout &write(T n) {
    if (n < 0) write('-');
    return write(n < 0 ? -to_uint_t<T>(n) : to_uint_t<T>(n));
  }
  template <class T>
  requires(uint_c<T> && !char_c<T>)
  fastout &write(T n) {
    if CEXP (sizeof(T) <= 4) return memset(p_ib = int_buf, 0, 11), u32tostr(n, p_ib), write(p_ib);
    p_ib = int_buf + INTBUF - 1;
    do *(--(p_ib)) = char(n % 10) | '0';
    while (n /= 10);
    return write(p_ib);
  }
  template <mint_c T>
  fastout &write(T n) { return write(n.val()); }
  fastout &write(strn CR str) { return write(str.c_str()); }
  template <class T, class U>
  fastout &write(std::pair<T, U> CR p) { return write(p.first).space().write(p.second); }
  template <class... Ts>
  fastout &write(std::tuple<Ts...> CR p) {
    return std::apply([&](Ts CR... targs) { usz n{0}; ((write(targs).space_if(++n != sizeof...(Ts))), ...); }, p), *this;
  }
  template <container_c T>
  fastout &write(T CR p) {
    if (p.begin() == p.end()) return *this;
    auto it = p.begin();
    for (write(*it++); it != p.end(); ++it) space().write(*it);
    return *this;
  }
  fastout &linebreak() { return write('\n'); }
  fastout &linebreak_if(bool flag) { return flag ? linebreak() : *this; }
  fastout &space() { return write(' '); }
  fastout &space_if(bool flag) { return flag ? space() : *this; }
  template <class T>
  fastout &operator<<(T CR val) { return write(val); }
};
}  // namespace fastio_impl_
inline fastio_impl_::fastin<0x200005> fin;
inline fastio_impl_::fastout<0x200005, 41> fout;

}  // namespace tifa_libs

#endif