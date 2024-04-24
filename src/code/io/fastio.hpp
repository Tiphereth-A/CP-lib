#ifndef TIFALIBS_IO_FASTIO
#define TIFALIBS_IO_FASTIO

#include "../fast/u32tostr.hpp"
#include "../util/traits.hpp"

namespace tifa_libs {
namespace fastio_impl_ {
//! UB if EOF occured during reading
template <u32 BUF>
class fastin {
  char bf_[BUF], *now_ = bf_, *end_ = bf_;
  FILE *f_;

 public:
  explicit fastin(FILE *f = stdin) : f_(f) {}

  char get() { return now_ == end_ && (end_ = (now_ = bf_) + fread(bf_, 1, BUF, f_), now_ == end_) ? EOF : *(now_)++; }
  char peek() { return now_ == end_ && (end_ = (now_ = bf_) + fread(bf_, 1, BUF, f_), now_ == end_) ? EOF : *(now_); }
  void rebind(FILE *f) {
    f_ = f;
    now_ = end_ = bf_;
  }

  bool iseof() { return peek() == EOF; }

  template <class T>
  requires(sint_c<T> && !char_c<T>)
  fastin &read(T &n) {
    bool is_neg = false;
    char ch = get();
    while (!isdigit(ch)) {
      is_neg |= ch == '-';
      ch = get();
    }
    n = 0;
    while (isdigit(ch)) {
      (n *= 10) += ch & 15;
      ch = get();
    }
    if (is_neg) n = -n;
    return *this;
  }
  template <class T>
  requires(uint_c<T> && !char_c<T>)
  fastin &read(T &n) {
    char ch = get();
    while (!isdigit(ch)) ch = get();
    n = 0;
    while (isdigit(ch)) {
      (n *= 10) += ch & 15;
      ch = get();
    }
    return *this;
  }
  template <mint_c T>
  fastin &read(T &n) {
    decltype(std::declval<T>().sval()) x;
    read(x);
    n = T(x);
    return *this;
  }
  //! ignore cntrl and space
  template <char_c T>
  fastin &read(T &n) {
    while (!isgraph(n = get()));
    return *this;
  }
  fastin &read(char *n) {
    char *n_ = n;
    while (!isgraph(*n_ = get()));
    while (isgraph(*(++n_) = get()));
    *n_ = '\0';
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
    std::apply([&](Ts &...targs) { ((read(targs)), ...); }, p);
    return *this;
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
    *n_ = '\0';
    return *this;
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
  fastin &strict_read(T &n) {
    n = get();
    return *this;
  }

  template <class T>
  fastin &operator>>(T &val) { return read(val); }
};
template <u32 BUF, u32 INTBUF>
class fastout {
  char int_bf_[INTBUF], *now_ib_ = int_bf_;

  FILE *f_;
  char *now_, bf_[BUF];
  const char *const end_ = bf_ + BUF;

 public:
  explicit fastout(FILE *file = stdout) : f_(file), now_(bf_) {}

  fastout &operator=(fastout const &r) {
    if (&r == this) return *this;
    f_ = r.f_;
    now_ = bf_ + (r.now_ - r.bf_);
    memcpy(bf_, r.bf_, sizeof(*bf_) * (r.now_ - r.bf_));
    return *this;
  }
  fastout(fastout const &r) { *this = r; }

  ~fastout() { flush(); }

  void flush() {
    fwrite(bf_, 1, usz(now_ - bf_), f_);
    now_ = bf_;
  }
  void rebind(FILE *file) { f_ = file; }

  template <char_c T>
  fastout &write(T const &n) {
    if (now_ == end_) flush();
    *(now_++) = n;
    return *this;
  }
  fastout &write(const char *n) {
    usz len = strlen(n), l_;
    const char *n_ = n;
    while (now_ + len >= end_) {
      memcpy(now_, n_, l_ = usz(end_ - now_));
      now_ += l_;
      n_ += l_;
      len -= l_;
      flush();
    }
    memcpy(now_, n_, len);
    now_ += len;
    return *this;
  }
  template <class T>
  requires(sint_c<T> && !char_c<T>)
  fastout &write(T n) {
    if (n < 0) {
      write('-');
      n = -n;
    }
    return write(to_uint_t<T>(n));
  }
  template <class T>
  requires(uint_c<T> && !char_c<T>)
  fastout &write(T n) {
    if constexpr (sizeof(T) <= 4) {
      memset(now_ib_ = int_bf_, 0, 11);
      u32tostr(n, now_ib_);
      return write(now_ib_);
    }
    now_ib_ = int_bf_ + INTBUF - 1;
    do {
      *(--(now_ib_)) = char(n % 10) | '0';
    } while (n /= 10);
    return write(now_ib_);
  }
  template <mint_c T>
  fastout &write(T n) { return write(n.val()); }
  fastout &write(strn const &str) { return write(str.c_str()); }
  template <class T, class U>
  fastout &write(std::pair<T, U> const &p) { return write(p.first).space().write(p.second); }
  template <class... Ts>
  fastout &write(std::tuple<Ts...> const &p) {
    std::apply(
        [&](Ts const &...targs) {
          usz n{0};
          ((write(targs).space_if(++n != sizeof...(Ts))), ...);
        },
        p);
    return *this;
  }
  template <container_c T>
  fastout &write(T const &p) {
    if (p.begin() == p.end()) return *this;
    auto it = p.begin();
    write(*it++);
    for (; it != p.end(); ++it) space().write(*it);
    return *this;
  }

  fastout &linebreak() { return write('\n'); }
  fastout &linebreak_if(bool flag) { return flag ? linebreak() : *this; }
  fastout &space() { return write(' '); }
  fastout &space_if(bool flag) { return flag ? space() : *this; }

  template <class T>
  fastout &operator<<(T const &val) { return write(val); }
};
}  // namespace fastio_impl_

inline fastio_impl_::fastin<0x200005> fin;
inline fastio_impl_::fastout<0x200005, 41> fout;

}  // namespace tifa_libs

#endif