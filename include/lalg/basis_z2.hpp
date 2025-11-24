#ifndef TIFALIBS_LALG_BASIS_Z2
#define TIFALIBS_LALG_BASIS_Z2

#include "../util/alias_others.hpp"
#include "../util/bitset_getdata.hpp"

namespace tifa_libs::math {

template <u32 N = 64, bool greedy_insert = false>
struct basis_z2 {
  vec<std::bitset<N>> basis;

  CEXP basis_z2() NE : basis(N) {}

  CEXP bool insert(std::bitset<N> x) NE {
    bool status = 0;
    if CEXP (greedy_insert) {  // greedy
      for (u32 i = N - 1; ~i; --i)
        if (x[i]) {
          if (basis[i].none()) basis[i] = x;
          if ((x ^= basis[i]).none()) {
            status = 1;
            break;
          }
        }
    } else {  // GE
      for (u32 i = N - 1; ~i; --i)
        if (x[i]) {
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
    for (auto&& i : basis) ret ^= i;
    return ret;
  }
  // @return std::nullopt if x is linear independent with current basis, else return the solution
  CEXP auto coord(std::bitset<N> x) NE {
    std::optional res{std::bitset<N>{}};
    for (u32 i = basis.size() - 1; ~i; --i)
      if (x[i]) {
        if (!basis[i][i]) {
          res = std::nullopt;
          return res;
        }
        res->set(i), x ^= basis[i];
      }
    return res;
  }
  friend basis_z2 meet(basis_z2 CR l, vec<std::bitset<N>> CR r) NE {
    if CEXP (greedy_insert) {  // Zassenhaus, 2x slower with GE insertion
      using bslo = bitset_getdata<N>;
      using bshi = bitset_getdata<N * 2>;
      using word_t = TPN bslo::word_t;
      basis_z2<N * 2> tmp;
      CEXP auto Nw = bslo::Nw;
      for (auto CR i : l.basis) {
        std::bitset<N * 2> now;
        if CEXP (bshi::Nw > 1) {
          memcpy(bshi::getdata(now), bslo::getdata(i), Nw * sizeof(word_t));
          memcpy(bshi::getdata(now) + Nw, bslo::getdata(i), Nw * sizeof(word_t));
        } else bshi::getword(now, 0) = bslo::getword(i, 0) << N | bslo::getword(i, 0);
        tmp.insert(now);
      }
      for (auto CR i : r) {
        std::bitset<N * 2> now;
        if CEXP (bshi::Nw > 1) memcpy(bshi::getdata(now) + Nw, bslo::getdata(i), Nw * sizeof(word_t));
        else bshi::getword(now, 0) = bslo::getword(i, 0) << N;
        tmp.insert(now);
      }
      basis_z2 ans;
      flt_ (u32, i, 0, N) memcpy(bslo::getdata(ans.basis[i]), bshi::getdata(tmp.basis[i]), Nw * sizeof(word_t));
      return ans;
    } else {  //! will get wrong result with greedy insertion
      auto cvt = [](cT_(std::bitset<N>) x) NE {
        if CEXP (N <= 32) return x.to_ulong();
        else if CEXP (N <= 64) return x.to_ullong();
        else return x.to_string();
      };
      auto f = [&](std::bitset<N> x) NE {
        for (auto i : l.basis)
          if (auto y = x ^ i; cvt(y) < cvt(x)) x = y;
        return x;
      };
      basis_z2<N> ans;
      for (vecpt<std::bitset<N>> ab; auto x : r) {
        auto y = f(x), xy = y ^ x;
        for (auto [a, b] : ab)
          if (auto _ = y ^ b; cvt(_) < cvt(y)) y = _, xy ^= a;
        if (y.any()) ab.emplace_back(xy, y);
        else ans.insert(xy);
      }
      return ans;
    }
  }
};

}  // namespace tifa_libs::math

#endif