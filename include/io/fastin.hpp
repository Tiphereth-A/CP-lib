#ifndef TIFALIBS_IO_FASTIN
#define TIFALIBS_IO_FASTIN

#include "../util/alias_others.hpp"
#include "../util/traits_math.hpp"
#ifdef __linux__
#include <sys/mman.h>
#include <sys/stat.h>
#endif

namespace tifa_libs {

struct fastin_data {
  CEXP static u32 BUF = 0x200005;
  FILE* f_ = nullptr;
#ifdef __linux__
  char *bg, *ed, *p;
  struct stat Fl;

  void rebind(FILE* f = nullptr) NE {
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
    if (!f_) munmap(bg, Fl.st_size + 1);
#pragma GCC diagnostic warning "-Wmaybe-uninitialized"
    if (!f) return;
    auto fd = fileno(f_ = f);
    fstat(fd, &Fl);
    p = (bg = (char*)mmap(nullptr, Fl.st_size + 4, PROT_READ, MAP_PRIVATE, fd, 0));
    ed = bg + Fl.st_size;
    madvise(bg, Fl.st_size + 4, MADV_SEQUENTIAL);
  }

  bool iseof() CNE { return p == ed; }
  ~fastin_data() NE { rebind(); }
#else
  char buf[BUF], *ed, *p;

  void rebind(FILE* f) NE { f_ = f, p = ed = buf; }
  bool iseof() NE {
    if (p == ed) [[unlikely]]
      ed = (p = buf) + fread(buf, 1, BUF, f_);
    return p == ed;
  }
#endif

  fastin_data(FILE* f = stdin) NE { assert(f), rebind(f); }
  fastin_data(fastin_data CR) = delete;
  fastin_data& operator=(fastin_data CR) = delete;
};
// clang-format off
enum FIN_SET { FS_NEWLINE = 1, FS_SPACE = 2, FS_NEG = 4, FS_NUM = 8, FS_ALPHA = 16, FS_OTHERS = 32 };
// clang-format on
template <u32 charset>
class fastin {
  fastin_data& data;

  static CEXP bool is_cntrl(char c) NE {
    if CEXP (charset & FS_OTHERS) return iscntrl(c);
    else if CEXP (charset & FS_NEWLINE) return c < 32;
    else return false;
  }
  static CEXP bool is_cntrls(char c) NE {
    if CEXP (charset & FS_OTHERS) return !isgraph(c);
    else if CEXP (charset & (FS_NEWLINE | FS_SPACE)) return c <= 32;
    else return false;
  }
  static CEXP bool is_digit(char c) NE {
    if CEXP (charset & (FS_ALPHA | FS_OTHERS)) return isdigit(c);
    else if CEXP (!(charset & FS_NUM)) return false;
    else if CEXP (!(charset & FS_NEG)) return c > 32;
    else return c >= 48;
  }
  static CEXP bool is_neg_digit(char c) NE {
    if CEXP (!(charset & FS_NEG)) return is_digit(c);
    else if CEXP (charset & (FS_ALPHA | FS_OTHERS)) return c == '-' || isdigit(c);
    else return c > 32;
  }
#ifdef __linux__
  template <bool ignore_space = true>
  void read_str(strn& n) NE {
    char* l;
    if CEXP (ignore_space) {
      skip_cntrls(), l = data.p;
      while (!is_cntrls(*data.p)) ++data.p;
    } else {
      skip_cntrl(), l = data.p;
      while (!is_cntrl(*data.p)) ++data.p;
    }
    n.assign(l, data.p);
  }
#else
  template <bool ignore_space>
  void read_str(strn& n) NE {
    if CEXP (n.clear(); ignore_space) {
      n.push_back(skip_cntrls().get());
      while (!is_cntrls(peek())) n.push_back(get());
    } else {
      n.push_back(skip_cntrl().get());
      while (!is_cntrl(peek())) n.push_back(get());
    }
  }
#endif
 public:
  fastin(fastin_data& data) NE : data(data) {}
  fastin(fastin CR) = delete;
  fastin& operator=(fastin CR) = delete;

  char peek() NE {
    if (data.iseof()) [[unlikely]]
      return EOF;
    return *data.p;
  }
  char get_unchk() NE { return *data.p++; }
  char get() NE {
    if (data.iseof()) [[unlikely]]
      return EOF;
    return get_unchk();
  }
#define SKIP(name, pred)              \
  fastin& skip_##name() NE {          \
    while (pred(peek())) get_unchk(); \
    return *this;                     \
  }
  SKIP(cntrl, is_cntrl)
  SKIP(cntrls, is_cntrls)
  SKIP(ndigit, !is_digit)
  SKIP(nnegdigit, !is_neg_digit)
#undef SKIP
  template <class T>
  requires(imost64_c<T> && !char_c<T>)
  fastin& operator>>(T& n) NE {
    if CEXP (std::same_as<T, bool>) n = skip_ndigit().get() != '0';
    else {
      n = 0;
      bool is_neg = false;
      if CEXP ((charset & FS_NEG) && std::signed_integral<T>) is_neg = (skip_nnegdigit().peek() == '-' && get_unchk());
      else skip_ndigit();
      std::conditional_t<sizeof(T) < sizeof(u32), u32, to_uint_t<T>> n_ = 0;
#ifdef __linux__
      // clang-format off
#define _ {while (~STR2U16[*(u16*)data.p]) (n_ *= 100) += STR2U16[*(u16*)data.p], data.p += 2; if (is_digit(peek())) (n_ *= 10) += get_unchk() & 15;}
      if ((usz)data.p & 1) { if (is_digit(peek())) [[likely]] { (n_ *= 10) += get_unchk() & 15; _ } } else _;
#undef _
      // clang-format on
#else
      while (is_digit(peek())) (n_ *= 10) += get_unchk() & 15;
#endif
      if CEXP (sint_c<T>)
        if (is_neg) n_ = -n_;
      n = (T)n_;
    }
    return *this;
  }
  fastin& operator>>(std::floating_point auto& n) NE {
    static strn s;
    (*this >> s), std::from_chars(begin(s).base(), end(s).base(), n);
    return *this;
  }
  //! ignore cntrl and space
  fastin& operator>>(char_c auto& n) NE {
    n = skip_cntrls().get();
    return *this;
  }
  fastin& operator>>(strn& n) NE {
    read_str<true>(n);
    return *this;
  }
  fastin& getline(strn& n) NE {
    read_str<false>(n);
    return *this;
  }
  //! NOT ignore cntrl and space
  fastin& strict_read(char_c auto& n) NE {
    n = get();
    return *this;
  }
  fastin& operator>>(fastin& (*func)(fastin&)) NE { return func(*this); }
  auto flags() CNE { return std::ios_base::dec; }
};
inline fastin_data fid_stdin;
inline fastin<FS_NEWLINE | FS_SPACE | FS_NEG | FS_NUM | FS_ALPHA | FS_OTHERS> fin(fid_stdin);
inline fastin<FS_NEWLINE | FS_SPACE | FS_NEG | FS_NUM> fin_int(fid_stdin);
inline fastin<FS_NEWLINE | FS_SPACE | FS_NUM> fin_uint(fid_stdin);
template <u32 w>
inline fastin<w>& ws(fastin<w>& f) NE { return f.skip_cntrls(); }

}  // namespace tifa_libs

#endif