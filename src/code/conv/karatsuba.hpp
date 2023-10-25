#ifndef TIFALIBS_CONV_KARATSUBA
#define TIFALIBS_CONV_KARATSUBA

#include "../util/vec_op.hpp"
#include "conv_naive.hpp"

namespace tifa_libs::math {

template <class T>
inline vec<T> karatsuba(vec<T> const &a, vec<T> const &b) {
  if (a.empty() && b.empty()) return {};
  if (a.size() < b.size()) return karatsuba(b, a);
  if (a.size() < 32) return conv_naive(a, b);
  usz d = a.size() / 2;
  vec<T> al(a.begin(), std::next(a.begin(), (isz)d)), au(std::next(a.begin(), (isz)d), a.end());
  if (b.size() < d + 10) {
    auto cl = karatsuba(al, b), cu = karatsuba(au, b);
    vec<T> c(a.size() + b.size() - 1);
    for (usz i = 0; i < cl.size(); ++i) c[i] = cl[i];
    for (usz i = 0; i < cu.size(); ++i) c[i + d] += cu[i];
    return c;
  }
  vec<T> bl(b.begin(), std::next(b.begin(), (isz)d)), bu(std::next(b.begin(), (isz)d), b.end());
  vec<T> alu{al}, blu{bl};
  alu += au;
  blu += bu;
  vec<T> cll = karatsuba(al, bl), cuu = karatsuba(au, bu), clu = karatsuba(alu, blu);
  (clu -= cll) -= cuu;
  vec<T> c(d);
  std::copy(clu.begin(), clu.end(), std::back_inserter(c));
  c.resize(a.size() + b.size() - 1);
  c += cll;
  for (usz i = 0; i < cuu.size(); ++i) c[i + 2 * d] += cuu[i];
  c.resize(a.size() + b.size() - 1);
  return c;
}

}  // namespace tifa_libs::math

#endif