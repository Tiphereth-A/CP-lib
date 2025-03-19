#ifndef TIFALIBS_MATH_BASIS_Z2
#define TIFALIBS_MATH_BASIS_Z2

#include "../util/alias_others.hpp"

namespace tifa_libs::math {

template <u32 N = 64>
struct basisZ2 {
  vec<std::bitset<N>> basis;

  CEXP basisZ2() NE : basis(N) {}

  CEXP bool insert(std::bitset<N> x) NE {
    bool status = 0;
    for (u32 i = N - 1; ~i; --i) {
      if (!(x[i])) continue;
      if (basis[i][i]) x ^= basis[i];
      else {
        flt_ (u32, j, 0, i)
          if (x[j]) x ^= basis[j];
        flt_ (u32, j, i + 1, (u32)basis.size())
          if (basis[j][i]) basis[j] ^= x;
        basis[i] = x, status = 1;
        break;
      }
    }
    return status;
  }
  CEXP bool test(std::bitset<N> x) CNE {
    for (u32 i = N - 1; ~i; --i) {
      if (!(x[i])) continue;
      if (basis[i][i]) x ^= basis[i];
      else return 0;
    }
    return 1;
  }
  CEXP u32 rank() CNE {
    u32 res = 0;
    flt_ (u32, i, 0, (u32)basis.size()) res += basis[i][i];
    return res;
  }
  CEXP std::bitset<N> max_spn() CNE {
    std::bitset<N> ret;
    for (auto &&i : basis) ret ^= i;
    return ret;
  }
  // @return std::nullopt if x is linear independent with current basis, else return the solution
  CEXP std::optional<std::bitset<N>> coord(std::bitset<N> x) NE {
    std::bitset<N> res;
    for (u32 i = basis.size() - 1; ~i; --i)
      if (x[i]) {
        if (!basis[i][i]) return {};
        res.set(i), x ^= basis[i];
      }
    return res;
  }
  CEXP basisZ2 meet(cT_(vec<std::bitset<N>>) r) CNE {
    auto cvt = [](cT_(std::bitset<N>) x) NE {
      if CEXP (N <= 32) return x.to_ulong();
      else if CEXP (N <= 64) return x.to_ullong();
      else return x.to_string();
    };
    auto f = [&, this](std::bitset<N> x) NE {
      for (auto i : basis)
        if (auto y = x ^ i; cvt(y) < cvt(x)) x = y;
      return x;
    };
    basisZ2<N> ans;
    for (vecpt<std::bitset<N>> ab; auto x : r) {
      auto y = f(x), xy = y ^ x;
      for (auto [a, b] : ab)
        if (auto _ = y ^ b; cvt(_) < cvt(y)) y = _, xy ^= a;
      if (y.any()) ab.emplace_back(xy, y);
      else ans.insert(xy);
    }
    return ans;
  }
};

}  // namespace tifa_libs::math

#endif