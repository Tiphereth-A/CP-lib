#ifndef TIFA_LIBS_MATH_XOR_BASIS
#define TIFA_LIBS_MATH_XOR_BASIS

#include "../util/util.hpp"

namespace tifa_libs::math {

template <usz N = 64>
class basis_Z2 {
  vec<std::bitset<N>> base;

 public:
  constexpr basis_Z2() {}

  constexpr std::bitset<N> &operator[](usz index) { return base[index]; }
  constexpr std::bitset<N> operator[](usz index) const { return base[index]; }
  constexpr vec<std::bitset<N>> &data() { return base; }
  constexpr vec<std::bitset<N>> data() const { return base; }

  constexpr usz rank() const {
    usz res = 0;
    for (usz i = 0; i < base.size(); ++i) res += base[i][i];
    return res;
  }

  constexpr bool insert(std::bitset<N> x) {
    bool status = false;
    for (usz i = base.size() - 1; ~i; --i) {
      if (!(x[i])) continue;
      if (base[i][i])
        x ^= base[i];
      else {
        for (usz j = 0; j < i; ++j)
          if (x[j]) x ^= base[j];
        for (usz j = i + 1; j < base.size(); ++j)
          if (base[j][i]) base[j] ^= x;
        base[i] = x;
        status = true;
        break;
      }
    }
    return status;
  }
  constexpr std::bitset<N> max_span() const {
    std::bitset<N> ret;
    for (auto &&i : base) ret ^= i;
    return ret;
  }

  // @return std::nullopt if x is linear independent with current basis, else return the solution
  constexpr std::optional<std::bitset<N>> coord(std::bitset<N> x) {
    std::bitset<N> res;
    for (usz i = base.size() - 1; ~i; --i)
      if (x[i]) {
        if (!base[i][i]) return {};
        res.set(i);
        x ^= base[i];
      }
    return res;
  }
};

}  // namespace tifa_libs::math

#endif