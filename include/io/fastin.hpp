#ifndef TIFALIBS_IO_FASTIN
#define TIFALIBS_IO_FASTIN

#include "../util/alias_others.hpp"
#include "../util/traits_math.hpp"
#ifdef __linux__
#include <sys/mman.h>
#include <sys/stat.h>
#endif

namespace tifa_libs {

//! UB if EOF occured during reading
class fastin {
  CEXP static u32 BUF = 0x200005;
  FILE *f_ = nullptr;
#ifdef __linux__
  char *bg, *ed, *p;
  struct stat Fl;

  template <bool ignore_space = true>
  void read_str(strn &n) NE {
    char *l;
    if CEXP (ignore_space) {
      skip_cntrls(), l = p;
      while (isgraph(*p)) ++p;
    } else {
      skip_cntrl(), l = p;
      while (isprint(*p)) ++p;
    }
    n.assign(l, p);
  }

 public:
  fastin(FILE *f = stdin) NE { assert(f), rebind(f); }
  fastin(fastin CR) = delete;
  fastin &operator=(fastin CR) = delete;
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
  bool iseof() NE { return p == ed; }
#else
  char buf[BUF], *ed, *p;

  template <bool ignore_space>
  void read_str(strn &n) NE {
    n.clear(), n.reserve(23);
    if CEXP (ignore_space) {
      n.push_back(skip_cntrls().get());
      while (isgraph(get())) n.push_back(peek());
    } else {
      n.push_back(skip_cntrl().get());
      while (isprint(get())) n.push_back(peek());
    }
  }

 public:
  fastin(FILE *f = stdin) NE { rebind(f); }
  fastin(fastin CR) = delete;
  fastin &operator=(fastin CR) = delete;
  void rebind(FILE *f) NE { f_ = f, p = ed = buf; }
  bool iseof() NE {
    if (p == ed) [[unlikely]]
      ed = (p = buf) + fread(buf, 1, BUF, f_);
    return p == ed;
  }
#endif
  char peek() NE {
    if (iseof()) [[unlikely]]
      return EOF;
    return *p;
  }
  char get_unchk() NE { return *p++; }
  char get() NE {
    if (iseof()) [[unlikely]]
      return EOF;
    return get_unchk();
  }
#define SKIP(name, pred)              \
  fastin &skip_##name() NE {          \
    while (pred(peek())) get_unchk(); \
    return *this;                     \
  }
  SKIP(cntrl, iscntrl)
  SKIP(cntrls, !isgraph)
  SKIP(ndigit, !isdigit)
#undef SKIP
  template <class T>
  requires(imost64_c<T> && !char_c<T>)
  fastin &operator>>(T &n) NE {
    if CEXP (std::same_as<T, bool>) n = skip_ndigit().get() != '0';
    else {
      n = 0;
      bool is_neg = false;
      if CEXP (std::signed_integral<T>)
        while (!isdigit(peek())) is_neg |= get_unchk() == '-';
      else skip_ndigit();
      std::conditional_t<sizeof(T) < sizeof(u32), u32, to_uint_t<T>> n_ = 0;
      while (isdigit(peek())) (n_ *= 10) += get_unchk() & 15;
      if CEXP (sint_c<T>)
        if (is_neg) n_ = -n_;
      n = (T)n_;
    }
    return *this;
  }
  fastin &operator>>(std::floating_point auto &n) NE {
    static strn s;
    (*this >> s), std::from_chars(begin(s).base(), end(s).base(), n);
    return *this;
  }
  //! ignore cntrl and space
  fastin &operator>>(char_c auto &n) NE {
    n = skip_cntrls().get();
    return *this;
  }
  fastin &operator>>(strn &n) NE {
    read_str<true>(n);
    return *this;
  }
  fastin &getline(strn &n) NE {
    read_str<false>(n);
    return *this;
  }
  //! NOT ignore cntrl and space
  fastin &strict_read(char_c auto &n) NE {
    n = get();
    return *this;
  }
  fastin &operator>>(fastin &(*func)(fastin &)) NE { return func(*this); }
  auto flags() CNE { return std::ios_base::dec; }
};
inline fastin fin;
inline fastin &ws(fastin &f) NE { return f.skip_cntrls(); }

}  // namespace tifa_libs

#endif