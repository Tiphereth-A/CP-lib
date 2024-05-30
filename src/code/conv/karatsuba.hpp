#ifndef TIFALIBS_CONV_KARATSUBA
#define TIFALIBS_CONV_KARATSUBA

#include "../util/vec_op.hpp"
#include "conv_naive.hpp"

namespace tifa_libs::math {

template <class T>
CEXP vec<T> karatsuba(vec<T> CR a, vec<T> CR b) {
  if (a.empty() && b.empty()) return {};
  if (a.size() < b.size()) return karatsuba(b, a);
  if (a.size() < 32) return conv_naive(a, b);
  const u32 d = (u32)a.size() / 2;
  const vec<T> al(a.begin(), a.begin() + d), au(a.begin() + d, a.end());
  if (b.size() < d + 10) {
    const auto cl = karatsuba(al, b), cu = karatsuba(au, b);
    vec<T> c(a.size() + b.size() - 1);
    flt_ (u32, i, 0, (u32)cl.size()) c[i] = cl[i];
    flt_ (u32, i, 0, (u32)cu.size()) c[i + d] += cu[i];
    return c;
  }
  const vec<T> bl(b.begin(), b.begin() + d), bu(b.begin() + d, b.end());
  vec<T> alu{al}, blu{bl};
  alu += au, blu += bu;
  vec<T> cll = karatsuba(al, bl), cuu = karatsuba(au, bu), clu = karatsuba(alu, blu);
  (clu -= cll) -= cuu;
  vec<T> c(d);
  std::ranges::copy(clu, std::back_inserter(c));
  c.resize(a.size() + b.size() - 1), c += cll;
  flt_ (u32, i, 0, (u32)cuu.size()) c[i + 2 * d] += cuu[i];
  c.resize(a.size() + b.size() - 1);
  return c;
}

}  // namespace tifa_libs::math

#endif